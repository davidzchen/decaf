/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <config.h>
#include <string.h>

#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"

/* Class: IntConstant
 * ------------------
 * Implementation for IntConstant class
 */

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
  value = val;
  retType = Type::intType;
}

void IntConstant::PrintChildren(int indentLevel) { 
  printf("%d", value);
}

/* Class: DoubleConstant
 * ------------------
 * Implementation for DoubleConstant class
 */

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
  value = val;
  retType = Type::doubleType;
}

void DoubleConstant::PrintChildren(int indentLevel) { 
  printf("%g", value);
}

/* Class: BoolConstant
 * ------------------
 * Implementation for BoolConstant class
 */

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
  value = val;
  retType = Type::boolType;
}

void BoolConstant::PrintChildren(int indentLevel) { 
  printf("%s", value ? "true" : "false");
}

/* Class: StringConstant
 * ------------------
 * Implementation for StringConstant class
 */

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
  Assert(val != NULL);
  value = strdup(val);
  retType = Type::stringType;
}

void StringConstant::PrintChildren(int indentLevel) { 
  printf("%s",value);
}

/* Class: Operator
 * ------------------
 * Implementation for Operator class
 */

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
  Assert(tok != NULL);
  strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
  printf("%s",tokenString);
}

/* Class: CompoundExpr
 * ------------------
 * Implementation for CompoundExpr class
 */

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
    : Expr(Join(l->location(), r->location())) {
  Assert(l != NULL && o != NULL && r != NULL);
  (op = o)->set_parent(this);
  (left = l)->set_parent(this);
  (right = r)->set_parent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
    : Expr(Join(o->location(), r->location())) {
  Assert(o != NULL && r != NULL);
  left = NULL; 
  (op = o)->set_parent(this);
  (right = r)->set_parent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o)
    : Expr(Join(l->location(), o->location())) {
  Assert(l != NULL && o != NULL);
  right = NULL;
  (left = l)->set_parent(this);
  (op = o)->set_parent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
  if (left) {
    left->Print(indentLevel+1);
  }
  op->Print(indentLevel+1);
  if (right) {
    right->Print(indentLevel+1);
  }
}

/* Class: ArithmeticExpr
 * ------------------
 * Implementation for ArithmeticExpr class
 */

bool ArithmeticExpr::Check(SymTable *env) {
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  if (left) {
    ret &= left->Check(env);
    leftType = left->GetRetType();
  }

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (left) {
    if (leftType->IsConvertableTo(Type::intType) && 
        rightType->IsConvertableTo(Type::intType)) {
      SetRetType(Type::intType);
    } else if (leftType->IsConvertableTo(Type::doubleType) && 
        rightType->IsConvertableTo(Type::doubleType)) {
      SetRetType(Type::doubleType);
    } else {
      ReportError::IncompatibleOperands(op, leftType, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }
  } else {
    // XXX: Are we allowing negative doubles?
    if (!rightType->IsConvertableTo(Type::intType) && 
        !rightType->IsConvertableTo(Type::doubleType)) {
      ReportError::IncompatibleOperand(op, rightType);
      SetRetType(Type::errorType);
    } else {
      SetRetType(rightType);
    }
  }

  return ret;
}

void ArithmeticExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                          SymTable *env) {
  Location *loc = NULL;
  if (left) {
    left->Emit(falloc, codegen, env);
  }
  right->Emit(falloc, codegen, env);

  // Negation?
  if (!left) {
    loc = codegen->GenUnaryOp(falloc, op->GetTokenString(),
                              right->GetFrameLocation());
  } else {
    loc = codegen->GenBinaryOp(falloc, op->GetTokenString(),
                               left->GetFrameLocation(),
                               right->GetFrameLocation());
  }

  frameLocation = loc;
}

/* Class: RelationalExpr
 * ------------------
 * Implementation for RelationalExpr class
 */

bool RelationalExpr::Check(SymTable *env) {
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  ret &= left->Check(env);
  leftType = left->GetRetType();

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if ((leftType->IsConvertableTo(Type::intType) &&
       rightType->IsConvertableTo(Type::intType)) ||
      (leftType->IsConvertableTo(Type::doubleType) &&
       rightType->IsConvertableTo(Type::doubleType))) {
    SetRetType(Type::boolType);
  } else {
    ReportError::IncompatibleOperands(op, leftType, rightType);
    SetRetType(Type::errorType);
    ret = false;
  }

  return ret;
}

void RelationalExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                          SymTable *env) {
  Location *loc = NULL;
  left->Emit(falloc, codegen, env);
  right->Emit(falloc, codegen, env);
  loc = codegen->GenBinaryOp(falloc, op->GetTokenString(),
                             left->GetFrameLocation(),
                             right->GetFrameLocation());

  frameLocation = loc;
}

/* Class: EqualityExpr
 * ------------------
 * Implementation for EqualityExpr class
 */

bool EqualityExpr::Check(SymTable *env) {
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  ret &= left->Check(env);
  leftType = left->GetRetType();

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (!(leftType->IsConvertableTo(rightType) || 
        rightType->IsConvertableTo(leftType))) {
    ReportError::IncompatibleOperands(op, leftType, rightType);
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(Type::boolType);
  }

  return ret;
}

void EqualityExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                        SymTable *env) {
  Location *loc = NULL;
  left->Emit(falloc, codegen, env);
  right->Emit(falloc, codegen, env);
  if (left->GetRetType()->IsConvertableTo(Type::stringType) &&
      right->GetRetType()->IsConvertableTo(Type::stringType)) {
    loc = codegen->GenBuiltInCall(falloc, StringEqual,
                                  left->GetFrameLocation(),
                                  right->GetFrameLocation());
    if (strcmp(op->GetTokenString(), "!=") == 0) {
      loc = codegen->GenUnaryOp(falloc, strdup("!"), loc);
    }
  } else {
    loc = codegen->GenBinaryOp(falloc, op->GetTokenString(),
                               left->GetFrameLocation(),
                               right->GetFrameLocation());
  }

  frameLocation = loc;
}

/* Class: LogicalExpr
 * ------------------
 * Implementation for LogicalExpr class
 */

bool LogicalExpr::Check(SymTable *env) {
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  if (left) {
    ret &= left->Check(env);
    leftType = left->GetRetType();
  }

  ret &= right->Check(env);
  rightType = right->GetRetType();
  SetRetType(Type::boolType);
  if (left) {
    if (!leftType->IsConvertableTo(Type::boolType) || 
        !rightType->IsConvertableTo(Type::boolType)) {
      ReportError::IncompatibleOperands(op, leftType, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }
  } else {
    if (!rightType->IsConvertableTo(Type::boolType)) {
      ReportError::IncompatibleOperand(op, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }
  }

  return ret;
}

void LogicalExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  Location *loc = NULL;
  if (left) {
    left->Emit(falloc, codegen, env);
  }
  right->Emit(falloc, codegen, env);

  // Logical Negation?
  if (!left) {
    loc = codegen->GenUnaryOp(falloc, op->GetTokenString(),
                              right->GetFrameLocation());
  } else {
    loc = codegen->GenBinaryOp(falloc, op->GetTokenString(),
                               left->GetFrameLocation(),
                               right->GetFrameLocation());
  }

  frameLocation = loc;
}

/* Class: PostfixExpr
 * ------------------
 * Implementation for PostfixExpr class
 */

bool PostfixExpr::Check(SymTable *env) {
  bool ret = true;

  ret &= left->Check(env);

  if (!left->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::IncompatibleOperand(op, left->GetRetType());
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(Type::intType);
  }

  return ret;
}

void PostfixExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  left->Emit(falloc, codegen, env);
  Location* loc = codegen->GenUnaryOp(falloc, op->GetTokenString(),
                                      left->GetFrameLocation());

  frameLocation = loc;
}

/* Class: AssignExpr
 * ------------------
 * Implementation for AssignExpr class
 */

bool AssignExpr::Check(SymTable *env) {
  bool ret = true;
  ret &= left->Check(env);
  Type* leftType = left->GetRetType();

  ret &= right->Check(env);
  Type* rightType = right->GetRetType();

  if (!rightType->IsConvertableTo(leftType) &&
      !leftType->IsEquivalentTo(Type::errorType)) {
    ReportError::IncompatibleOperands(op, leftType, rightType);
    SetRetType(Type::errorType);
    ret = false;
  } else {
    SetRetType(leftType);
  }

  return ret;
}

void AssignExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                      SymTable *env) {
  left->Emit(falloc, codegen, env);
  right->Emit(falloc, codegen, env);

  Assert(left->GetFrameLocation() != NULL);
  Assert(right->GetFrameLocation() != NULL);

  if (left->NeedsDereference()) {
    codegen->GenStore(left->GetReference(), right->GetFrameLocation(), 0);
  } else {
    codegen->GenAssign(left->GetFrameLocation(), right->GetFrameLocation());
  }
  frameLocation = left->GetFrameLocation();
}

/* Class: This
 * ----------
 * Implementation of This class
 */

bool This::Check(SymTable *env) {
  if (!env->getThis()) {
    ReportError::ThisOutsideClassScope(this);
    SetRetType(Type::errorType);
    return false;
  }

  Node *node = env->getThisClass();
  Assert(node != NULL);

  ClassDecl *thisClass = dynamic_cast<ClassDecl*>(node);
  //printf("%s\n", sym->getNode()->GetPrintNameForNode());
  Assert(thisClass != 0);

  SetRetType(new NamedType(thisClass->GetIdent()));

  return true;
}

void This::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
  Symbol *sym = env->find(strdup("this"));
  Assert(sym != NULL);
  frameLocation = sym->getLocation();
}

/* Class: ArrayAccess
 * ------------------
 * Implementation for ArrayAccess class
 */
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
  (base=b)->set_parent(this); 
  (subscript=s)->set_parent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
  base->Print(indentLevel+1);
  subscript->Print(indentLevel+1, "(subscript) ");
}

bool ArrayAccess::Check(SymTable *env) {
  bool ret = false;

  ret &= base->Check(env);
  ArrayType *at = dynamic_cast<ArrayType*>(base->GetRetType());
  if (at == 0) {
    ReportError::BracketsOnNonArray(base);
    ret = false;
    SetRetType(Type::errorType);
  } else {
    SetRetType(at->getElemType());
  }

  ret &= subscript->Check(env);
  if (!subscript->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::SubscriptNotInteger(subscript);
    ret = false;
    SetRetType(Type::errorType);
  }

  return ret;
}

void ArrayAccess::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  char *afterLabel = codegen->NewLabel();
  base->Emit(falloc, codegen, env);
  subscript->Emit(falloc, codegen, env);

  Location *arraySize = codegen->GenLoad(falloc, base->GetFrameLocation(), 0);
  Location *zero      = codegen->GenLoadConstant(falloc, 0);
  Location *lowerTest = codegen->GenBinaryOp(falloc, strdup("<"), subscript->GetFrameLocation(), zero);
  Location *upperTest = codegen->GenBinaryOp(falloc, strdup(">="), subscript->GetFrameLocation(), arraySize);
  Location *boundTest = codegen->GenBinaryOp(falloc, strdup("||"), lowerTest, upperTest);
  codegen->GenIfZ(boundTest, afterLabel);
  codegen->GenPrintError(falloc, kErrorArrOutOfBounds);
  codegen->GenLabel(afterLabel);
  Location *one = codegen->GenLoadConstant(falloc, 1);
  Location *four = codegen->GenLoadConstant(falloc, 4);
  Location *trueOff = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenBinaryOp(falloc, strdup("+"), subscript->GetFrameLocation(), one),
      four);

  Location *addr = codegen->GenBinaryOp(falloc, strdup("+"), base->GetFrameLocation(), trueOff);
  Location *loc = codegen->GenLoad(falloc, addr, 0);

  frameLocation = loc;
  reference = addr;
  needsDereference = true;
}

/* Class: FieldAccess
 * ------------------
 * Implementation for FieldAccess class
 */
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
    : LValue(b? Join(b->location(), f->location()) : *f->location()) {
  Assert(f != NULL); // b can be be NULL (just means no explicit base)
  base = b; 
  if (base) {
    base->set_parent(this); 
  }
  (field = f)->set_parent(this);
}

void FieldAccess::PrintChildren(int indentLevel) {
  if (base) {
    base->Print(indentLevel+1);
  }
  field->Print(indentLevel+1);
}

bool FieldAccess::Check(SymTable *env) {
  bool ret = true;
  if (!base) {
    Symbol *sym = env->find(field->name(), S_VARIABLE);
    if (sym == NULL) {
      ReportError::IdentifierNotDeclared(field, kLookingForVariable);
      SetRetType(Type::errorType);
      return false;
    }

      VarDecl *decl = dynamic_cast<VarDecl*>(sym->getNode());
      SetRetType(decl->GetType());
  } else {
    ret &= base->Check(env);

    // Error if base is not of a class's type
    NamedType *baseType = dynamic_cast<NamedType*>(base->GetRetType());
    if (baseType == 0) {
      ReportError::FieldNotFoundInBase(field, base->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    // Check whether field is indeed a field of base
    Symbol *sym = NULL;
    if ((sym = env->findClassField(baseType->GetName(), field->name(), S_VARIABLE)) == NULL) {
      ReportError::FieldNotFoundInBase(field, baseType);
      SetRetType(Type::errorType);
      return false;
    }

    if (env->getThisClass() == NULL) {
      ReportError::InaccessibleField(field, base->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    ClassDecl *classDecl = dynamic_cast<ClassDecl*>(env->getThisClass());
    Assert(classDecl != 0);

    if (strcmp(base->GetPrintNameForNode(), "This") != 0) {
      FieldAccess *baseFieldAccess = dynamic_cast<FieldAccess*>(base);
      Assert(baseFieldAccess != 0);

      if (strcmp(classDecl->GetIdent()->name(),
                 base->GetRetType()->GetName()) != 0) {
        ReportError::InaccessibleField(field, base->GetRetType());
        SetRetType(Type::errorType);
        return false;
      }
      /*if (baseFieldAccess->GetBase() != NULL) {
        ReportError::InaccessibleField(field, base->GetRetType());
        SetRetType(Type::errorType);
        return false;
      }*/
    }

    Decl *fieldDecl = dynamic_cast<Decl*>(sym->getNode());
    Assert(fieldDecl != 0);
    SetRetType(fieldDecl->GetType());
  }

  return ret;
}

void FieldAccess::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  if (!base) {
    Symbol *sym = env->find(field->name(), S_VARIABLE);
    Location *loc = sym->getLocation();

#ifdef __DEBUG_TAC
    PrintDebug("tac", "Var Access\t%s @ %d:%d\n", field->name(),
               loc->GetSegment(), loc->GetOffset());
#endif

    Assert(loc != NULL);

    if (loc->GetSegment() != classRelative) {
      frameLocation = loc;
      return;
    }

    // We have an implicit "this."
    Symbol *thisSym = env->find(strdup("this"), S_VARIABLE);
    Assert(thisSym != NULL);
    Location *thisLoc = thisSym->getLocation();

    needsDereference = true;
    Location *fieldOffset = codegen->GenLoadConstant(falloc, loc->GetOffset());
    reference = codegen->GenBinaryOp(falloc, strdup("+"), thisLoc, fieldOffset);

    frameLocation = codegen->GenLoad(falloc, reference, 0);
  } else {
    // Now, the frameLocation of the base contains the location of base, which
    // is a pointer to an object.
    //   Given: - field is a field of base
    //          - base's type is a NamedType
    //          - We are in class scope and can access field
    // Approach:
    //   off = offset of field in class of base
    //   loc = *(base + off)
    //   frameLocation = loc



    base->Emit(falloc, codegen, env);
    Symbol *classSym = env->find(base->GetRetType()->GetName(), S_CLASS);
    Assert(classSym != NULL);

    Symbol *fieldSym = classSym->getEnv()->find(field->name(), S_VARIABLE);
    Location *fieldLoc = fieldSym->getLocation();
    Assert(fieldLoc->GetSegment() == classRelative);

#ifdef __DEBUG_TAC
    PrintDebug("tac", "Var access with base\t%s::%s @ %d:%d\n",
        base->GetRetType()->GetName(), field->name(),
        fieldLoc->GetSegment(), fieldLoc->GetOffset());
#endif

    needsDereference = true;
    Location *fieldOffset = codegen->GenLoadConstant(falloc, fieldLoc->GetOffset());
    reference = codegen->GenBinaryOp(falloc, strdup("+"),
        base->GetFrameLocation(), fieldOffset);

    frameLocation = codegen->GenLoad(falloc, reference, 0);
  }
}

/* Class: Call
 * ------------------
 * Implementation for Call class
 */

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc) {
  Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
  base = b;
  if (base) {
    base->set_parent(this);
  }
  (field = f)->set_parent(this);
  (actuals = a)->SetParentAll(this);
}

void Call::PrintChildren(int indentLevel) {
  if (base) {
    base->Print(indentLevel+1);
  }
  field->Print(indentLevel+1);
  actuals->PrintAll(indentLevel+1, "(actuals) ");
}

bool Call::CheckCall(FnDecl *prototype, SymTable *env) {
  List<VarDecl*> *formals = prototype->GetFormals();
  bool ret = true;

  if (formals->NumElements() != actuals->NumElements()) {
    ReportError::NumArgsMismatch(field, formals->NumElements(), actuals->NumElements());
    return false;
  }

  Type *formalType, *actualType;
  for (int i = 0; i < formals->NumElements(); i++) {
    formalType = formals->Nth(i)->GetType();
    actualType = actuals->Nth(i)->GetRetType();
    if (!actualType->IsConvertableTo(formalType)) {
      ReportError::ArgMismatch(actuals->Nth(i), i+1, actualType, formalType);
      ret = false;
    }
  }

  return ret;
}

bool Call::CheckActuals(SymTable *env) {
  bool ret = true;

  for (int i = 0; i < actuals->NumElements(); i++) {
    ret &= actuals->Nth(i)->Check(env);
  }

  return ret;
}

bool Call::Check(SymTable *env) {
  bool ret = true;
  FnDecl *prototype = NULL;

  ret &= CheckActuals(env);

  if (!base) {
    Symbol *sym = env->find(field->name(), S_FUNCTION);
    if (sym == NULL) {
      ReportError::IdentifierNotDeclared(field, kLookingForFunction);
      SetRetType(Type::errorType);
      return false;
    }

    prototype = dynamic_cast<FnDecl*>(sym->getNode());
    Assert(prototype != 0);
    ret &= CheckCall(prototype, env);
  } else {
    ret &= base->Check(env);
    if (strcmp(base->GetRetType()->GetPrintNameForNode(), "ArrayType") == 0 &&
        strcmp(field->name(), "length") == 0) {
      SetRetType(Type::intType);
      return ret;
    }

    // Error if base is not of a class's type
    Type *baseType = base->GetRetType();
    if (baseType == Type::errorType) {
      SetRetType(Type::errorType);
      return false;
    }

    if (baseType->IsBuiltin()) {
      ReportError::FieldNotFoundInBase(field, base->GetRetType());
      SetRetType(Type::errorType);
      return false;
    }

    // Check whether field is indeed a field of base
    Symbol *sym = NULL;
    if ((sym = env->findClassField(baseType->GetName(), field->name(), S_FUNCTION)) == NULL) {
      ReportError::FieldNotFoundInBase(field, baseType);
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

int Call::EmitActuals(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  int numParams = 0;

  for (int i = 0; i < actuals->NumElements(); i++) {
    actuals->Nth(i)->Emit(falloc, codegen, env);
    numParams++;
  }

  // Push params in reverse order
  for (int i = actuals->NumElements() - 1; i >= 0; i--) {
    codegen->GenPushParam(actuals->Nth(i)->GetFrameLocation());
  }

  return numParams;
}


void Call::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
  Symbol *fnSym = NULL;
  FnDecl *fnDecl = NULL;
  int numParams = 0;
  bool hasReturnVal = true;

  // Used if we're doing a method call
  int methodOffset = 0;
  Location *objectLocation = NULL;
  Location *methodAddr = NULL;

  if (!base)
  {
#ifdef __DEBUG_TAC
    PrintDebug("tac", "Call %s\n", field->name());
#endif

    fnSym = env->find(field->name(), S_FUNCTION);
    Assert(fnSym != NULL);
    fnDecl = dynamic_cast<FnDecl*>(fnSym->getNode());
    Assert(fnDecl != 0);

    if (fnDecl->GetReturnType()->IsEquivalentTo(Type::voidType)) {
      hasReturnVal = false;
    }

    if (!fnDecl->IsMethod()) {
      numParams += EmitActuals(falloc, codegen, env);
      char *functionLabel = codegen->NewFunctionLabel(fnDecl->GetName());
      frameLocation = codegen->GenLCall(falloc, functionLabel, hasReturnVal);
      codegen->GenPopParams(numParams * 4);
      return;
    }

    // Implicit this
    // Get location of this and

    Symbol *thisSym = env->find(strdup("this"), S_VARIABLE);
    Assert(thisSym != NULL);
    objectLocation = thisSym->getLocation();

    methodOffset = fnDecl->GetMethodOffset();
    methodAddr = codegen->GenLoad(falloc,
        codegen->GenLoad(falloc, thisSym->getLocation(), 0), methodOffset * 4);
  } else {
    base->Emit(falloc, codegen, env);

    if (strcmp(base->GetRetType()->GetPrintNameForNode(), "ArrayType") == 0 &&
        strcmp(field->name(), "length") == 0) {
      frameLocation = codegen->GenLoad(falloc, base->GetFrameLocation(), 0);
      return;
    }

    Symbol *classSym = env->find(base->GetRetType()->GetName(), S_CLASS);
    Assert(classSym != NULL);
    fnSym = classSym->getEnv()->find(field->name(), S_FUNCTION);
    Assert(fnSym != NULL);
    fnDecl = dynamic_cast<FnDecl*>(fnSym->getNode());
    Assert(fnDecl != 0);

    if (fnDecl->GetReturnType()->IsEquivalentTo(Type::voidType)) {
      hasReturnVal = false;
    }

    objectLocation = base->GetFrameLocation();

    methodOffset = fnDecl->GetMethodOffset();
    methodAddr = codegen->GenLoad(falloc,
        codegen->GenLoad(falloc, base->GetFrameLocation(), 0), methodOffset * 4);
  }

  numParams += EmitActuals(falloc, codegen, env);
  numParams++;
  codegen->GenPushParam(objectLocation);

  frameLocation = codegen->GenACall(falloc, methodAddr, hasReturnVal);
  codegen->GenPopParams(numParams * 4);
}


/* Class: NewExpr
 * ------------------
 * Implementation for NewExpr class
 */

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType=c)->set_parent(this);
}

void NewExpr::PrintChildren(int indentLevel) {	
  cType->Print(indentLevel+1);
}

bool NewExpr::Check(SymTable *env) {
  bool ret = true;
  ret &= cType->Check(env);
  if (!ret) {
    ReportError::IdentifierNotDeclared(cType->GetIdent(), kLookingForClass);
    SetRetType(Type::errorType);
  } else {
    SetRetType(cType);
  }
  return ret;
}

void NewExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                   SymTable *env) {
  Location *loc = NULL;

  Symbol *classSym = env->find(cType->GetName(), S_CLASS);
  ClassDecl *classDecl = dynamic_cast<ClassDecl*>(classSym->getNode());
  Assert(classDecl != 0);

  Location *four = codegen->GenLoadConstant(falloc, 4);
  Location *classSize = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenLoadConstant(falloc, classDecl->NumFields() + 1), four);
  loc = codegen->GenBuiltInCall(falloc, Alloc, classSize, NULL);
  Location *vtableLabel = codegen->GenLoadLabel(falloc, classDecl->GetClassLabel());
  codegen->GenStore(loc, vtableLabel, 0);

  frameLocation = loc;
}

/* Class: NewArrayExpr
 * ------------------
 * Implementation for NewArrayExpr class
 */

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
  Assert(sz != NULL && et != NULL);
  (size=sz)->set_parent(this); 
  (elemType=et)->set_parent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
  size->Print(indentLevel+1);
  elemType->Print(indentLevel+1);
}

bool NewArrayExpr::Check(SymTable *env)
{
  bool ret = true;

  ret &= size->Check(env);
  if (!size->GetRetType()->IsConvertableTo(Type::intType)) {
    ReportError::NewArraySizeNotInteger(size);
    SetRetType(Type::errorType);
    ret = false;
  }

  ret &= elemType->Check(env);
  if (!ret) {
    if (elemType->GetIdent() != NULL) {
      ReportError::IdentifierNotDeclared(elemType->GetIdent(), kLookingForType);
    }
    SetRetType(Type::errorType);
  } else {
    SetRetType(new ArrayType(*location_, elemType));
  }

  return ret;
}

void NewArrayExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                        SymTable *env) {
  size->Emit(falloc, codegen, env);
  char *afterLabel = codegen->NewLabel();

  /* _t0 = 0;
   * _t1 = size <= 0
   * IfZ _t1 Goto AfterLabel
   * _t2 = "Decaf runtime error: Array size is <= 0"
   * PrintString(_t2)
   * Halt()
   */
  Location *zero = codegen->GenLoadConstant(falloc, 0);
  Location *sizeTest = codegen->GenBinaryOp(falloc, strdup("<="),
      size->GetFrameLocation(), zero);
  codegen->GenIfZ(sizeTest, afterLabel);
  codegen->GenPrintError(falloc, kErrorArrBadSize);

  /* AfterLabel:
   * _t3 = 1;
   * _t4 = 4;
   * _t5 = size + 1
   * _t6 = _t5 * _t4
   * _t7 = Alloc(_t6)
   * *(_t7) = size
   */
  codegen->GenLabel(afterLabel);
  Location *one = codegen->GenLoadConstant(falloc, 1);
  Location *eltSize = codegen->GenLoadConstant(falloc, 4);
  Location *arraySize = codegen->GenBinaryOp(falloc, strdup("*"),
      codegen->GenBinaryOp(falloc, strdup("+"), size->GetFrameLocation(), one),
      eltSize);

  Location *loc = codegen->GenBuiltInCall(falloc, Alloc, arraySize, NULL);
  codegen->GenStore(loc, size->GetFrameLocation(), 0);

  frameLocation = loc;
}

/* Class: ReadIntegerExpr
 * ----------------------
 * Implementation for ReadIntegerExpr
 */

bool ReadIntegerExpr::Check(SymTable *env) {
  SetRetType(Type::intType);
  return true;
}

void ReadIntegerExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                           SymTable *env) {
  Location *loc = codegen->GenBuiltInCall(falloc, ReadInteger, NULL, NULL);
  frameLocation = loc;
}

/* Class: ReadLineExpr
 * -------------------
 * Implementation for ReadLineExpr
 */

bool ReadLineExpr::Check(SymTable *env) {
  SetRetType(Type::stringType);
  return true;
}

void ReadLineExpr::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                        SymTable *env) {
  Location *loc = codegen->GenBuiltInCall(falloc, ReadLine, NULL, NULL);
  frameLocation = loc;
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
