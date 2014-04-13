/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>

#include "ast/expr.h"
#include "ast/type.h"
#include "ast/decl.h"

/* Class: IntConstant
 * ------------------
 * Implementation for IntConstant class
 */

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
  value_ = val;
  ret_type_ = Type::intType;
}

void IntConstant::PrintChildren(int indent_level) {
  fprintf(kOutputFile, "%d", value_);
}

/* Class: DoubleConstant
 * ------------------
 * Implementation for DoubleConstant class
 */

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
  value_ = val;
  ret_type_ = Type::doubleType;
}

void DoubleConstant::PrintChildren(int indent_level) {
  fprintf(kOutputFile, "%g", value_);
}

/* Class: BoolConstant
 * ------------------
 * Implementation for BoolConstant class
 */

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
  value_ = val;
  ret_type_ = Type::boolType;
}

void BoolConstant::PrintChildren(int indent_level) {
  fprintf(kOutputFile, "%s", value_ ? "true" : "false");
}

/* Class: StringConstant
 * ------------------
 * Implementation for StringConstant class
 */

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
  Assert(val != NULL);
  value_ = strdup(val);
  ret_type_ = Type::stringType;
}

void StringConstant::PrintChildren(int indent_level) {
  fprintf(kOutputFile, "%s",value_);
}

/* Class: Operator
 * ------------------
 * Implementation for Operator class
 */

Operator::Operator(yyltype loc, const char* tok) : Node(loc) {
  Assert(tok != NULL);
  strncpy(token_string_, tok, sizeof(token_string_));
}

void Operator::PrintChildren(int indent_level) {
  fprintf(kOutputFile, "%s",token_string_);
}

/* Class: CompoundExpr
 * ------------------
 * Implementation for CompoundExpr class
 */

CompoundExpr::CompoundExpr(Expr* l, Operator* o, Expr* r)
    : Expr(Join(l->location(), r->location())) {
  Assert(l != NULL && o != NULL && r != NULL);
  (op_ = o)->set_parent(this);
  (left_ = l)->set_parent(this);
  (right_ = r)->set_parent(this);
}

CompoundExpr::CompoundExpr(Operator* o, Expr* r)
    : Expr(Join(o->location(), r->location())) {
  Assert(o != NULL && r != NULL);
  left_ = NULL;
  (op_ = o)->set_parent(this);
  (right_ = r)->set_parent(this);
}

CompoundExpr::CompoundExpr(Expr* l, Operator* o)
    : Expr(Join(l->location(), o->location())) {
  Assert(l != NULL && o != NULL);
  right_ = NULL;
  (left_ = l)->set_parent(this);
  (op_ = o)->set_parent(this);
}

void CompoundExpr::PrintChildren(int indent_level) {
  if (left_) {
    left_->Print(indent_level+1);
  }
  op_->Print(indent_level+1);
  if (right_) {
    right_->Print(indent_level+1);
  }
}

/* Class: ArithmeticExpr
 * ------------------
 * Implementation for ArithmeticExpr class
 */

bool ArithmeticExpr::Check(SymTable* env) {
  bool ret = true;
  Type* left_type = NULL;
  Type* right_type = NULL;

  if (left_) {
    ret &= left_->Check(env);
    left_type = left_->GetRetType();
  }

  ret &= right_->Check(env);
  right_type = right_->GetRetType();

  if (left_) {
    if (left_type->IsConvertableTo(Type::intType) &&
        right_type->IsConvertableTo(Type::intType)) {
      SetRetType(Type::intType);
    } else if (left_type->IsConvertableTo(Type::doubleType) &&
        right_type->IsConvertableTo(Type::doubleType)) {
      SetRetType(Type::doubleType);
    } else {
      ReportError::IncompatibleOperands(op_, left_type, right_type);
      SetRetType(Type::errorType);
      ret = false;
    }
  } else {
    // XXX: Are we allowing negative doubles?
    if (!right_type->IsConvertableTo(Type::intType) &&
        !right_type->IsConvertableTo(Type::doubleType)) {
      ReportError::IncompatibleOperand(op_, right_type);
      SetRetType(Type::errorType);
    } else {
      SetRetType(right_type);
    }
  }

  return ret;
}

void ArithmeticExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                          SymTable* env) {
  Location* loc = NULL;
  if (left_) {
    left_->Emit(falloc, codegen, env);
  }
  right_->Emit(falloc, codegen, env);

  // Negation?
  if (!left_) {
    loc = codegen->GenUnaryOp(falloc, op_->GetTokenString(),
                              right_->GetFrameLocation());
  } else {
    loc = codegen->GenBinaryOp(falloc, op_->GetTokenString(),
                               left_->GetFrameLocation(),
                               right_->GetFrameLocation());
  }

  frame_location_ = loc;
}

/* Class: RelationalExpr
 * ------------------
 * Implementation for RelationalExpr class
 */

bool RelationalExpr::Check(SymTable *env) {
  bool ret = true;
  Type* left_type = NULL;
  Type* right_type = NULL;

  ret &= left_->Check(env);
  left_type = left_->GetRetType();

  ret &= right_->Check(env);
  right_type = right_->GetRetType();

  if ((left_type->IsConvertableTo(Type::intType) &&
       right_type->IsConvertableTo(Type::intType)) ||
      (left_type->IsConvertableTo(Type::doubleType) &&
       right_type->IsConvertableTo(Type::doubleType))) {
    SetRetType(Type::boolType);
  } else {
    ReportError::IncompatibleOperands(op_, left_type, right_type);
    SetRetType(Type::errorType);
    ret = false;
  }

  return ret;
}

void RelationalExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                          SymTable* env) {
  left_->Emit(falloc, codegen, env);
  right_->Emit(falloc, codegen, env);
  Location* loc = codegen->GenBinaryOp(falloc, op_->GetTokenString(),
                                       left_->GetFrameLocation(),
                                       right_->GetFrameLocation());

  frame_location_ = loc;
}

/* Class: EqualityExpr
 * ------------------
 * Implementation for EqualityExpr class
 */

bool EqualityExpr::Check(SymTable *env) {
  bool ret = true;
  Type *left_type = NULL;
  Type *right_type = NULL;

  ret &= left_->Check(env);
  left_type = left_->GetRetType();

  ret &= right_->Check(env);
  right_type = right_->GetRetType();

  if (!(left_type->IsConvertableTo(right_type) ||
        right_type->IsConvertableTo(left_type))) {
    ReportError::IncompatibleOperands(op_, left_type, right_type);
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(Type::boolType);
  }

  return ret;
}

void EqualityExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                        SymTable* env) {
  Location* loc = NULL;
  left_->Emit(falloc, codegen, env);
  right_->Emit(falloc, codegen, env);
  if (left_->GetRetType()->IsConvertableTo(Type::stringType) &&
      right_->GetRetType()->IsConvertableTo(Type::stringType)) {
    loc = codegen->GenBuiltInCall(falloc, StringEqual,
                                  left_->GetFrameLocation(),
                                  right_->GetFrameLocation());
    if (strcmp(op_->GetTokenString(), "!=") == 0) {
      loc = codegen->GenUnaryOp(falloc, strdup("!"), loc);
    }
  } else {
    loc = codegen->GenBinaryOp(falloc, op_->GetTokenString(),
                               left_->GetFrameLocation(),
                               right_->GetFrameLocation());
  }

  frame_location_ = loc;
}

/* Class: LogicalExpr
 * ------------------
 * Implementation for LogicalExpr class
 */

bool LogicalExpr::Check(SymTable* env) {
  bool ret = true;
  Type* left_type = NULL;
  Type* right_type = NULL;

  if (left_) {
    ret &= left_->Check(env);
    left_type = left_->GetRetType();
  }

  ret &= right_->Check(env);
  right_type = right_->GetRetType();
  SetRetType(Type::boolType);
  if (left_) {
    if (!left_type->IsConvertableTo(Type::boolType) ||
        !right_type->IsConvertableTo(Type::boolType)) {
      ReportError::IncompatibleOperands(op_, left_type, right_type);
      SetRetType(Type::errorType);
      ret = false;
    }
  } else {
    if (!right_type->IsConvertableTo(Type::boolType)) {
      ReportError::IncompatibleOperand(op_, right_type);
      SetRetType(Type::errorType);
      ret = false;
    }
  }

  return ret;
}

void LogicalExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                       SymTable* env) {
  Location* loc = NULL;
  if (left_) {
    left_->Emit(falloc, codegen, env);
  }
  right_->Emit(falloc, codegen, env);

  // Logical Negation?
  if (!left_) {
    loc = codegen->GenUnaryOp(falloc, op_->GetTokenString(),
                              right_->GetFrameLocation());
  } else {
    loc = codegen->GenBinaryOp(falloc, op_->GetTokenString(),
                               left_->GetFrameLocation(),
                               right_->GetFrameLocation());
  }

  frame_location_ = loc;
}

bool BitwiseExpr::Check(SymTable* env) {
  bool ret = true;
  Type* left_type = NULL;
  Type* right_type = NULL;

  if (left_ != NULL) {
    ret &= left_->Check(env);
    left_type = left_->GetRetType();
  }

  ret &= right_->Check(env);
  right_type = right_->GetRetType();
  SetRetType(Type::intType);
  if (left_ != NULL) {
    if (!left_type->IsConvertableTo(Type::intType) ||
        !right_type->IsConvertableTo(Type::intType)) {
      ReportError::IncompatibleOperands(op_, left_type, right_type);
      SetRetType(Type::errorType);
      ret = false;
    }
  } else {
    if (!right_type->IsConvertableTo(Type::intType)) {
      ReportError::IncompatibleOperand(op_, right_type);
      SetRetType(Type::errorType);
      ret = false;
    }
  }

  return ret;
}

void BitwiseExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                       SymTable* env) {
  Location* loc = NULL;
  if (left_ != NULL) {
    left_->Emit(falloc, codegen, env);
  }
  right_->Emit(falloc, codegen, env);

  if (left_ == NULL) {
    loc = codegen->GenUnaryOp(falloc, op_->GetTokenString(),
                              right_->GetFrameLocation());
  } else {
    loc = codegen->GenBinaryOp(falloc, op_->GetTokenString(),
                               left_->GetFrameLocation(),
                               right_->GetFrameLocation());
  }
  frame_location_ = loc;
}

/* Class: PostfixExpr
 * ------------------
 * Implementation for PostfixExpr class
 */

bool PostfixExpr::Check(SymTable* env) {
  bool ret = true;
  ret &= left_->Check(env);
  if (!left_->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::IncompatibleOperand(op_, left_->GetRetType());
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(Type::intType);
  }
  return ret;
}

void PostfixExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                       SymTable* env) {
  left_->Emit(falloc, codegen, env);
  Location* loc = codegen->GenUnaryOp(falloc, op_->GetTokenString(),
                                      left_->GetFrameLocation());

  frame_location_ = loc;
}

/* Class: AssignExpr
 * ------------------
 * Implementation for AssignExpr class
 */

bool AssignExpr::Check(SymTable* env) {
  bool ret = true;
  ret &= left_->Check(env);
  Type *left_type = left_->GetRetType();

  ret &= right_->Check(env);
  Type *right_type = right_->GetRetType();

  if (!right_type->IsConvertableTo(left_type) &&
      !left_type->IsEquivalentTo(Type::errorType)) {
    ReportError::IncompatibleOperands(op_, left_type, right_type);
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(left_type);
  }

  return ret;
}

void AssignExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                      SymTable* env) {
  left_->Emit(falloc, codegen, env);
  right_->Emit(falloc, codegen, env);

  Assert(left_->GetFrameLocation() != NULL);
  Assert(right_->GetFrameLocation() != NULL);

  if (left_->NeedsDereference()) {
    codegen->GenStore(left_->GetReference(), right_->GetFrameLocation(), 0);
  } else {
    codegen->GenAssign(left_->GetFrameLocation(), right_->GetFrameLocation());
  }
  frame_location_ = left_->GetFrameLocation();
}

/* Class: This
 * ----------
 * Implementation of This class
 */

bool This::Check(SymTable* env) {
  if (!env->getThis()) {
    ReportError::ThisOutsideClassScope(this);
    SetRetType(Type::errorType);
    return false;
  }

  Node* node = env->getThisClass();
  Assert(node != NULL);

  ClassDecl* this_class = dynamic_cast<ClassDecl*>(node);
  //printf("%s\n", sym->getNode()->GetPrintNameForNode());
  Assert(this_class != 0);

  SetRetType(new NamedType(this_class->GetIdent()));

  return true;
}

void This::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                SymTable* env) {
  Symbol* sym = env->find(strdup("this"));
  Assert(sym != NULL);
  frame_location_ = sym->getLocation();
}

/* Class: ArrayAccess
 * ------------------
 * Implementation for ArrayAccess class
 */

ArrayAccess::ArrayAccess(yyltype loc, Expr* b, Expr* s) : LValue(loc) {
  (base_ = b)->set_parent(this);
  (subscript_ = s)->set_parent(this);
}

void ArrayAccess::PrintChildren(int indent_level) {
  base_->Print(indent_level + 1);
  subscript_->Print(indent_level + 1, "(subscript) ");
}

bool ArrayAccess::Check(SymTable* env) {
  bool ret = false;
  ret &= base_->Check(env);
  ArrayType* at = dynamic_cast<ArrayType*>(base_->GetRetType());
  if (at == 0) {
    ReportError::BracketsOnNonArray(base_);
    ret = false;
    SetRetType(Type::errorType);
  } else {
    SetRetType(at->getElemType());
  }

  ret &= subscript_->Check(env);
  if (!subscript_->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::SubscriptNotInteger(subscript_);
    ret = false;
    SetRetType(Type::errorType);
  }

  return ret;
}

void ArrayAccess::Emit(FrameAllocator* falloc, CodeGenerator * codegen,
                       SymTable* env) {
  char* after_label = codegen->NewLabel();
  base_->Emit(falloc, codegen, env);
  subscript_->Emit(falloc, codegen, env);

  Location* array_size = codegen->GenLoad(falloc, base_->GetFrameLocation(), 0);
  Location* zero = codegen->GenLoadConstant(falloc, 0);
  Location* lower_test = codegen->GenBinaryOp(falloc, strdup("<"),
                                              subscript_->GetFrameLocation(),
                                              zero);
  Location* upper_test = codegen->GenBinaryOp(falloc, strdup(">="),
                                              subscript_->GetFrameLocation(),
                                              array_size);
  Location* bound_test = codegen->GenBinaryOp(falloc, strdup("||"),
                                              lower_test, upper_test);
  codegen->GenIfZ(bound_test, after_label);
  codegen->GenPrintError(falloc, kErrorArrOutOfBounds);
  codegen->GenLabel(after_label);
  Location* one = codegen->GenLoadConstant(falloc, 1);
  Location* four = codegen->GenLoadConstant(falloc, 4);
  Location* true_off = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenBinaryOp(falloc, strdup("+"),
                           subscript_->GetFrameLocation(), one),
      four);

  Location* addr = codegen->GenBinaryOp(falloc, strdup("+"),
                                        base_->GetFrameLocation(), true_off);
  Location* loc = codegen->GenLoad(falloc, addr, 0);

  frame_location_ = loc;
  reference_ = addr;
  needs_dereference_ = true;
}

/* Class: FieldAccess
 * ------------------
 * Implementation for FieldAccess class
 */

FieldAccess::FieldAccess(Expr* b, Identifier* f)
    : LValue(b ? Join(b->location(), f->location()) : *f->location()) {
  Assert(f != NULL); // b can be be NULL (just means no explicit base)
  base_ = b;
  if (base_) {
    base_->set_parent(this);
  }
  (field_ = f)->set_parent(this);
}

void FieldAccess::PrintChildren(int indent_level) {
  if (base_) {
    base_->Print(indent_level + 1);
  }
  field_->Print(indent_level + 1);
}

bool FieldAccess::Check(SymTable* env) {
  bool ret = true;
  if (!base_) {
    Symbol* sym = env->find(field_->name(), S_VARIABLE);
    if (sym == NULL) {
      ReportError::IdentifierNotDeclared(field_, kLookingForVariable);
      SetRetType(Type::errorType);
      return false;
    }

    VarDecl* decl = dynamic_cast<VarDecl*>(sym->getNode());
    SetRetType(decl->GetType());
  } else {
    ret &= base_->Check(env);

    // Error if base_ is not of a class's type
    NamedType* base_type = dynamic_cast<NamedType*>(base_->GetRetType());
    if (base_type == 0) {
      ReportError::FieldNotFoundInBase(field_, base_->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    // Check whether field_ is indeed a field of base
    Symbol *sym = NULL;
    if ((sym = env->findClassField(base_type->GetName(), field_->name(), S_VARIABLE)) == NULL) {
      ReportError::FieldNotFoundInBase(field_, base_type);
      SetRetType(Type::errorType);
      return false;
    }

    if (env->getThisClass() == NULL) {
      ReportError::InaccessibleField(field_, base_->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    ClassDecl *class_decl = dynamic_cast<ClassDecl*>(env->getThisClass());
    Assert(class_decl != 0);

    if (strcmp(base_->GetPrintNameForNode(), "This") != 0) {
      FieldAccess *baseFieldAccess = dynamic_cast<FieldAccess*>(base_);
      Assert(baseFieldAccess != 0);

      if (strcmp(class_decl->GetIdent()->name(),
                 base_->GetRetType()->GetName()) != 0) {
        ReportError::InaccessibleField(field_, base_->GetRetType());
        SetRetType(Type::errorType);
        return false;
      }
      /*if (baseFieldAccess->GetBase() != NULL) {
        ReportError::InaccessibleField(field_, base_->GetRetType());
        SetRetType(Type::errorType);
        return false;
      }*/
    }

    Decl *field_decl = dynamic_cast<Decl*>(sym->getNode());
    Assert(field_decl != 0);
    SetRetType(field_decl->GetType());
  }

  return ret;
}

void FieldAccess::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  if (!base_) {
    Symbol *sym = env->find(field_->name(), S_VARIABLE);
    Location *loc = sym->getLocation();

#ifdef __DEBUG_TAC
    PrintDebug("tac", "Var Access\t%s @ %d:%d\n", field_->name(),
               loc->GetSegment(), loc->GetOffset());
#endif

    Assert(loc != NULL);

    if (loc->GetSegment() != classRelative) {
      frame_location_ = loc;
      return;
    }

    // We have an implicit "this."
    Symbol *this_sym = env->find(strdup("this"), S_VARIABLE);
    Assert(this_sym != NULL);
    Location *this_loc = this_sym->getLocation();

    needs_dereference_ = true;
    Location *field_offset = codegen->GenLoadConstant(falloc, loc->GetOffset());
    reference_ = codegen->GenBinaryOp(falloc, strdup("+"), this_loc, field_offset);

    frame_location_ = codegen->GenLoad(falloc, reference_, 0);
  } else {
    // Now, the frame_location_ of the base contains the location of base, which
    // is a pointer to an object.
    //   Given: - field_ is a field of base
    //          - base's type is a NamedType
    //          - We are in class scope and can access field_
    // Approach:
    //   off = offset of field in class of base
    //   loc = *(base + off)
    //   frame_location_ = loc

    base_->Emit(falloc, codegen, env);
    Symbol *class_sym = env->find(base_->GetRetType()->GetName(), S_CLASS);
    Assert(class_sym != NULL);

    Symbol *field_sym = class_sym->getEnv()->find(field_->name(), S_VARIABLE);
    Location *fieldLoc = field_sym->getLocation();
    Assert(fieldLoc->GetSegment() == classRelative);

#ifdef __DEBUG_TAC
    PrintDebug("tac", "Var access with base\t%s::%s @ %d:%d\n",
        base_->GetRetType()->GetName(), field_->name(),
        fieldLoc->GetSegment(), fieldLoc->GetOffset());
#endif

    needs_dereference_ = true;
    Location *field_offset = codegen->GenLoadConstant(falloc, fieldLoc->GetOffset());
    reference_ = codegen->GenBinaryOp(falloc, strdup("+"),
        base_->GetFrameLocation(), field_offset);

    frame_location_ = codegen->GenLoad(falloc, reference_, 0);
  }
}

/* Class: Call
 * ------------------
 * Implementation for Call class
 */

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc) {
  Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
  base_ = b;
  if (base_) {
    base_->set_parent(this);
  }
  (field_ = f)->set_parent(this);
  (actuals_ = a)->SetParentAll(this);
}

void Call::PrintChildren(int indent_level) {
  if (base_) {
    base_->Print(indent_level+1);
  }
  field_->Print(indent_level+1);
  actuals_->PrintAll(indent_level+1, "(actuals) ");
}

bool Call::CheckCall(FnDecl *prototype, SymTable *env) {
  List<VarDecl*> *formals = prototype->GetFormals();
  bool ret = true;

  if (formals->NumElements() != actuals_->NumElements()) {
    ReportError::NumArgsMismatch(field_, formals->NumElements(), actuals_->NumElements());
    return false;
  }

  Type *formalType, *actualType;
  for (int i = 0; i < formals->NumElements(); ++i) {
    formalType = formals->Nth(i)->GetType();
    actualType = actuals_->Nth(i)->GetRetType();
    if (!actualType->IsConvertableTo(formalType)) {
      ReportError::ArgMismatch(actuals_->Nth(i), i+1, actualType, formalType);
      ret = false;
    }
  }

  return ret;
}

bool Call::CheckActuals(SymTable *env) {
  bool ret = true;

  for (int i = 0; i < actuals_->NumElements(); ++i) {
    ret &= actuals_->Nth(i)->Check(env);
  }

  return ret;
}

bool Call::Check(SymTable *env) {
  bool ret = true;
  FnDecl *prototype = NULL;

  ret &= CheckActuals(env);

  if (!base_) {
    Symbol *sym = env->find(field_->name(), S_FUNCTION);
    if (sym == NULL) {
      ReportError::IdentifierNotDeclared(field_, kLookingForFunction);
      SetRetType(Type::errorType);
      return false;
    }

    prototype = dynamic_cast<FnDecl*>(sym->getNode());
    Assert(prototype != 0);
    ret &= CheckCall(prototype, env);
  } else {
    ret &= base_->Check(env);
    if (strcmp(base_->GetRetType()->GetPrintNameForNode(), "ArrayType") == 0 &&
        strcmp(field_->name(), "length") == 0) {
      SetRetType(Type::intType);
      return ret;
    }

    // Error if base_ is not of a class's type
    Type* base_type = base_->GetRetType();
    if (base_type == Type::errorType) {
      SetRetType(Type::errorType);
      return false;
    }

    if (base_type->IsBuiltin()) {
      ReportError::FieldNotFoundInBase(field_, base_->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    // Check whether field_ is indeed a field of base
    Symbol* sym = NULL;
    if ((sym = env->findClassField(base_type->GetName(), field_->name(), S_FUNCTION)) == NULL) {
      ReportError::FieldNotFoundInBase(field_, base_type);
      SetRetType(Type::errorType);
      return false;
    }

    prototype = dynamic_cast<FnDecl*>(sym->getNode());
    Assert(prototype != 0);
    ret &= CheckCall(prototype, env);
  }
  SetRetType(prototype->GetReturnType());
  return ret;
}

int Call::EmitActuals(FrameAllocator* falloc, CodeGenerator* codegen,
                      SymTable* env) {
  int num_params = 0;
  for (int i = 0; i < actuals_->NumElements(); ++i) {
    actuals_->Nth(i)->Emit(falloc, codegen, env);
    ++num_params;
  }

  // Push params in reverse order
  for (int i = actuals_->NumElements() - 1; i >= 0; --i) {
    codegen->GenPushParam(actuals_->Nth(i)->GetFrameLocation());
  }

  return num_params;
}

void Call::Emit(FrameAllocator* falloc, CodeGenerator* codegen, SymTable* env) {
  Symbol* fn_sym = NULL;
  FnDecl* fn_decl = NULL;
  int num_params = 0;
  bool has_return_val = true;

  // Used if we're doing a method call
  int method_offset = 0;
  Location* object_location = NULL;
  Location* method_addr = NULL;

  if (!base_) {
#ifdef __DEBUG_TAC
    PrintDebug("tac", "Call %s\n", field_->name());
#endif

    fn_sym = env->find(field_->name(), S_FUNCTION);
    Assert(fn_sym != NULL);
    fn_decl = dynamic_cast<FnDecl*>(fn_sym->getNode());
    Assert(fn_decl != 0);

    if (fn_decl->GetReturnType()->IsEquivalentTo(Type::voidType)) {
      has_return_val = false;
    }

    if (!fn_decl->IsMethod()) {
      num_params += EmitActuals(falloc, codegen, env);
      char* function_label = codegen->NewFunctionLabel(fn_decl->GetName());
      frame_location_ = codegen->GenLCall(falloc, function_label, has_return_val);
      codegen->GenPopParams(num_params * 4);
      return;
    }

    // Implicit this
    // Get location of this and

    Symbol* this_sym = env->find(strdup("this"), S_VARIABLE);
    Assert(this_sym != NULL);
    object_location = this_sym->getLocation();

    method_offset = fn_decl->GetMethodOffset();
    method_addr = codegen->GenLoad(falloc,
        codegen->GenLoad(falloc, this_sym->getLocation(), 0), method_offset * 4);
  } else {
    base_->Emit(falloc, codegen, env);
    if (strcmp(base_->GetRetType()->GetPrintNameForNode(), "ArrayType") == 0 &&
        strcmp(field_->name(), "length") == 0) {
      frame_location_ = codegen->GenLoad(falloc, base_->GetFrameLocation(), 0);
      return;
    }

    Symbol* class_sym = env->find(base_->GetRetType()->GetName(), S_CLASS);
    Assert(class_sym != NULL);
    fn_sym = class_sym->getEnv()->find(field_->name(), S_FUNCTION);
    Assert(fn_sym != NULL);
    fn_decl = dynamic_cast<FnDecl*>(fn_sym->getNode());
    Assert(fn_decl != 0);

    if (fn_decl->GetReturnType()->IsEquivalentTo(Type::voidType)) {
      has_return_val = false;
    }

    object_location = base_->GetFrameLocation();
    method_offset = fn_decl->GetMethodOffset();
    method_addr = codegen->GenLoad(falloc,
        codegen->GenLoad(falloc, base_->GetFrameLocation(), 0),
                         method_offset * 4);
  }

  num_params += EmitActuals(falloc, codegen, env);
  ++num_params;
  codegen->GenPushParam(object_location);

  frame_location_ = codegen->GenACall(falloc, method_addr, has_return_val);
  codegen->GenPopParams(num_params * 4);
}

/* Class: NewExpr
 * ------------------
 * Implementation for NewExpr class
 */

NewExpr::NewExpr(yyltype loc, NamedType* c) : Expr(loc) {
  Assert(c != NULL);
  (c_type_ = c)->set_parent(this);
}

void NewExpr::PrintChildren(int indent_level) {
  c_type_->Print(indent_level + 1);
}

bool NewExpr::Check(SymTable* env) {
  bool ret = true;
  ret &= c_type_->Check(env);
  if (!ret) {
    ReportError::IdentifierNotDeclared(c_type_->GetIdent(), kLookingForClass);
    SetRetType(Type::errorType);
  } else {
    SetRetType(c_type_);
  }
  return ret;
}

void NewExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                   SymTable* env) {
  Location* loc = NULL;
  Symbol* class_sym = env->find(c_type_->GetName(), S_CLASS);
  ClassDecl* class_decl = dynamic_cast<ClassDecl*>(class_sym->getNode());
  Assert(class_decl != 0);

  Location* four = codegen->GenLoadConstant(falloc, 4);
  Location* class_size = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenLoadConstant(falloc, class_decl->NumFields() + 1), four);
  loc = codegen->GenBuiltInCall(falloc, Alloc, class_size, NULL);
  Location* vtable_label = codegen->GenLoadLabel(falloc, class_decl->GetClassLabel());
  codegen->GenStore(loc, vtable_label, 0);
  frame_location_ = loc;
}

/* Class: NewArrayExpr
 * ------------------
 * Implementation for NewArrayExpr class
 */

NewArrayExpr::NewArrayExpr(yyltype loc, Expr* sz, Type* et) : Expr(loc) {
  Assert(sz != NULL && et != NULL);
  (size_ = sz)->set_parent(this);
  (elem_type_ = et)->set_parent(this);
}

void NewArrayExpr::PrintChildren(int indent_level) {
  size_->Print(indent_level + 1);
  elem_type_->Print(indent_level + 1);
}

bool NewArrayExpr::Check(SymTable* env) {
  bool ret = true;
  ret &= size_->Check(env);
  if (!size_->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::NewArraySizeNotInteger(size_);
    SetRetType(Type::errorType);
    ret = false;
  }

  ret &= elem_type_->Check(env);
  if (!ret) {
    if (elem_type_->GetIdent() != NULL) {
      ReportError::IdentifierNotDeclared(elem_type_->GetIdent(), kLookingForType);
    }
    SetRetType(Type::errorType);
  } else {
    SetRetType(new ArrayType(*location_, elem_type_));
  }

  return ret;
}

void NewArrayExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                        SymTable* env) {
  size_->Emit(falloc, codegen, env);
  char *after_label = codegen->NewLabel();

  /* _t0 = 0;
   * _t1 = size <= 0
   * IfZ _t1 Goto AfterLabel
   * _t2 = "Decaf runtime error: Array size is <= 0"
   * PrintString(_t2)
   * Halt()
   */
  Location* zero = codegen->GenLoadConstant(falloc, 0);
  Location* size_test = codegen->GenBinaryOp(falloc, strdup("<="),
      size_->GetFrameLocation(), zero);
  codegen->GenIfZ(size_test, after_label);
  codegen->GenPrintError(falloc, kErrorArrBadSize);

  /* AfterLabel:
   * _t3 = 1;
   * _t4 = 4;
   * _t5 = size + 1
   * _t6 = _t5 * _t4
   * _t7 = Alloc(_t6)
   * *(_t7) = size
   */
  codegen->GenLabel(after_label);
  Location* one = codegen->GenLoadConstant(falloc, 1);
  Location* elt_size = codegen->GenLoadConstant(falloc, 4);
  Location* array_size = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenBinaryOp(falloc, strdup("+"), size_->GetFrameLocation(), one),
      elt_size);

  Location* loc = codegen->GenBuiltInCall(falloc, Alloc, array_size, NULL);
  codegen->GenStore(loc, size_->GetFrameLocation(), 0);

  frame_location_ = loc;
}

/* Class: ReadIntegerExpr
 * ----------------------
 * Implementation for ReadIntegerExpr
 */

bool ReadIntegerExpr::Check(SymTable* env) {
  SetRetType(Type::intType);
  return true;
}

void ReadIntegerExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                           SymTable* env) {
  Location* loc = codegen->GenBuiltInCall(falloc, ReadInteger, NULL, NULL);
  frame_location_ = loc;
}

/* Class: ReadLineExpr
 * -------------------
 * Implementation for ReadLineExpr
 */

bool ReadLineExpr::Check(SymTable* env) {
  SetRetType(Type::stringType);
  return true;
}

void ReadLineExpr::Emit(FrameAllocator* falloc, CodeGenerator* codegen,
                        SymTable* env) {
  Location* loc = codegen->GenBuiltInCall(falloc, ReadLine, NULL, NULL);
  frame_location_ = loc;
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
