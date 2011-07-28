/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"

/* Class: IntConstant
 * ------------------
 * Implementation for IntConstant class
 */

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) 
{
  value = val;
  retType = Type::intType;
}

void IntConstant::PrintChildren(int indentLevel) 
{ 
  printf("%d", value);
}

/* Class: DoubleConstant
 * ------------------
 * Implementation for DoubleConstant class
 */

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) 
{
  value = val;
  retType = Type::doubleType;
}

void DoubleConstant::PrintChildren(int indentLevel) 
{ 
  printf("%g", value);
}

/* Class: BoolConstant
 * ------------------
 * Implementation for BoolConstant class
 */

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) 
{
  value = val;
  retType = Type::boolType;
}

void BoolConstant::PrintChildren(int indentLevel) 
{ 
  printf("%s", value ? "true" : "false");
}

/* Class: StringConstant
 * ------------------
 * Implementation for StringConstant class
 */

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) 
{
  Assert(val != NULL);
  value = strdup(val);
  retType = Type::stringType;
}

void StringConstant::PrintChildren(int indentLevel) 
{ 
  printf("%s",value);
}

/* Class: Operator
 * ------------------
 * Implementation for Operator class
 */

Operator::Operator(yyltype loc, const char *tok) : Node(loc) 
{
  Assert(tok != NULL);
  strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) 
{
  printf("%s",tokenString);
}

/* Class: CompoundExpr
 * ------------------
 * Implementation for CompoundExpr class
 */

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) 
{
  Assert(l != NULL && o != NULL && r != NULL);
  (op = o)->SetParent(this);
  (left = l)->SetParent(this);
  (right = r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) 
{
  Assert(o != NULL && r != NULL);
  left = NULL; 
  (op = o)->SetParent(this);
  (right = r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o)
  : Expr(Join(l->GetLocation(), o->GetLocation()))
{
  Assert(l != NULL && o != NULL);
  right = NULL;
  (left = l)->SetParent(this);
  (op = o)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) 
{
  if (left)
    {
      left->Print(indentLevel+1);
    }
  op->Print(indentLevel+1);
  if (right)
    {
      right->Print(indentLevel+1);
    }
}

/* Class: ArithmeticExpr
 * ------------------
 * Implementation for ArithmeticExpr class
 */

bool ArithmeticExpr::Check(SymTable *env)
{
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  if (left)
    {
      ret &= left->Check(env);
      leftType = left->GetRetType();
    }

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (left)
    {

      if (leftType->IsConvertableTo(Type::intType)
          && rightType->IsConvertableTo(Type::intType))
        {
          SetRetType(Type::intType);
        }
      else if (leftType->IsConvertableTo(Type::doubleType)
          && rightType->IsConvertableTo(Type::doubleType))
        {
          SetRetType(Type::doubleType);
        }
      else
        {
          ReportError::IncompatibleOperands(op, leftType, rightType);
          SetRetType(Type::errorType);
          ret = false;
        }
    }
  else
    {
      // XXX: Are we allowing negative doubles?
      if (!rightType->IsConvertableTo(Type::intType)
          && !rightType->IsConvertableTo(Type::doubleType))
        {
          ReportError::IncompatibleOperand(op, rightType);
          SetRetType(Type::errorType);
        }
      else
        {
          SetRetType(rightType);
        }
    }

  return ret;
}

/* Class: RelationalExpr
 * ------------------
 * Implementation for RelationalExpr class
 */

bool RelationalExpr::Check(SymTable *env)
{
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  ret &= left->Check(env);
  leftType = left->GetRetType();

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (leftType->IsConvertableTo(Type::intType)
      && rightType->IsConvertableTo(Type::intType))
    {
      SetRetType(Type::boolType);
    }
  else if (leftType->IsConvertableTo(Type::doubleType)
      && rightType->IsConvertableTo(Type::doubleType))
    {
      SetRetType(Type::boolType);
    }
  else
    {
      ReportError::IncompatibleOperands(op, leftType, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }

  return ret;
}

/* Class: EqualityExpr
 * ------------------
 * Implementation for EqualityExpr class
 */

bool EqualityExpr::Check(SymTable *env)
{
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  ret &= left->Check(env);
  leftType = left->GetRetType();

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (!(leftType->IsConvertableTo(rightType)
      || rightType->IsConvertableTo(leftType)))
    {
      ReportError::IncompatibleOperands(op, leftType, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }
  else
    {
      SetRetType(Type::boolType);
    }

  return ret;
}

/* Class: LogicalExpr
 * ------------------
 * Implementation for LogicalExpr class
 */

bool LogicalExpr::Check(SymTable *env)
{
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  if (left)
    {
      ret &= left->Check(env);
      leftType = left->GetRetType();
    }

  ret &= right->Check(env);
  rightType = right->GetRetType();

  SetRetType(Type::boolType);

  if (left)
    {
      if (!leftType->IsConvertableTo(Type::boolType)
          || !rightType->IsConvertableTo(Type::boolType))
        {
          ReportError::IncompatibleOperands(op, leftType, rightType);
          SetRetType(Type::errorType);
          ret = false;
        }
    }
  else
    {
      if (!rightType->IsConvertableTo(Type::boolType))
        {
          ReportError::IncompatibleOperand(op, rightType);
          SetRetType(Type::errorType);
          ret = false;
        }
    }

  return ret;
}

/* Class: PostfixExpr
 * ------------------
 * Implementation for PostfixExpr class
 */

bool PostfixExpr::Check(SymTable *env)
{
  bool ret = true;

  ret &= left->Check(env);

  if (!left->GetRetType()->IsConvertableTo(Type::intType))
    {
      ReportError::IncompatibleOperand(op, left->GetRetType());
      SetRetType(Type::errorType);
      ret = false;
    }
  else
    {
      SetRetType(Type::intType);
    }

  return ret;
}

/* Class: AssignExpr
 * ------------------
 * Implementation for AssignExpr class
 */

bool AssignExpr::Check(SymTable *env)
{
  bool ret = true;
  Type *leftType = NULL;
  Type *rightType = NULL;

  ret &= left->Check(env);
  leftType = left->GetRetType();

  ret &= right->Check(env);
  rightType = right->GetRetType();

  if (!rightType->IsConvertableTo(leftType) && !leftType->IsEquivalentTo(Type::errorType))
    {
      ReportError::IncompatibleOperands(op, leftType, rightType);
      SetRetType(Type::errorType);
      ret = false;
    }
  else
    {
      SetRetType(leftType);
    }

  return ret;
}

/* Class: This
 * ----------
 * Implementation of This class
 */

bool This::Check(SymTable *env)
{
  if (!env->getThis())
    {
      ReportError::ThisOutsideClassScope(this);
      SetRetType(Type::errorType);
      return false;
    }

  Symbol *sym = env->getThisClass();
  Assert(sym != NULL);

  ClassDecl *thisClass = dynamic_cast<ClassDecl*>(sym->getNode());
  //printf("%s\n", sym->getNode()->GetPrintNameForNode());
  Assert(thisClass != 0);

  SetRetType(new NamedType(thisClass->GetIdent()));

  return true;
}

/* Class: ArrayAccess
 * ------------------
 * Implementation for ArrayAccess class
 */
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) 
{
  (base=b)->SetParent(this); 
  (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) 
{
  base->Print(indentLevel+1);
  subscript->Print(indentLevel+1, "(subscript) ");
}

bool ArrayAccess::Check(SymTable *env)
{
  bool ret = false;

  ret &= base->Check(env);
  ArrayType *at = dynamic_cast<ArrayType*>(base->GetRetType());
  if (at == 0)
    {
      ReportError::BracketsOnNonArray(base);
      ret = false;
      SetRetType(Type::errorType);
    }
  else
    {
      SetRetType(at->getElemType());
    }

  ret &= subscript->Check(env);

  if (!subscript->GetRetType()->IsConvertableTo(Type::intType))
    {
      ReportError::SubscriptNotInteger(subscript);
      ret = false;
      SetRetType(Type::errorType);
    }

  return ret;
}

/* Class: FieldAccess
 * ------------------
 * Implementation for FieldAccess class
 */
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) 
{
  Assert(f != NULL); // b can be be NULL (just means no explicit base)
  base = b; 
  if (base) 
    {
      base->SetParent(this); 
    }
  (field=f)->SetParent(this);
}


void FieldAccess::PrintChildren(int indentLevel)
{
  if (base)
    {
      base->Print(indentLevel+1);
    }
  field->Print(indentLevel+1);
}

bool FieldAccess::Check(SymTable *env)
{
  bool ret = true;

  if (!base)
    {
      Symbol *sym = env->find(field->getName(), S_VARIABLE);
      if (sym == NULL)
        {
          ReportError::IdentifierNotDeclared(field, LookingForVariable);
          SetRetType(Type::errorType);
          return false;
        }

        VarDecl *decl = dynamic_cast<VarDecl*>(sym->getNode());
        SetRetType(decl->GetType());
    }
  else
    {
      ret &= base->Check(env);

      // Error if base is not of a class's type
      NamedType *baseType = dynamic_cast<NamedType*>(base->GetRetType());
      if (baseType == 0)
        {
          ReportError::FieldNotFoundInBase(field, base->GetRetType());
          SetRetType(Type::errorType);
          return false;
        }

      // Check whether field is indeed a field of base
      Symbol *sym = NULL;
      if ((sym = env->findClassField(baseType->GetName(), field->getName(), S_VARIABLE)) == NULL)
        {
          ReportError::FieldNotFoundInBase(field, baseType);
          SetRetType(Type::errorType);
          return false;
        }

      if (strcmp(base->GetPrintNameForNode(), "This") != 0)
        {
          FieldAccess *baseFieldAccess = dynamic_cast<FieldAccess*>(base);
          Assert(baseFieldAccess != 0);
          if (baseFieldAccess->GetBase() != NULL);
            {
              ReportError::InaccessibleField(field, base->GetRetType());
              SetRetType(Type::errorType);
              return false;
            }
        }

      Decl *fieldDecl = dynamic_cast<Decl*>(sym->getNode());
      Assert(fieldDecl != 0);
      SetRetType(fieldDecl->GetType());
    }

  return ret;
}

/* Class: Call
 * ------------------
 * Implementation for Call class
 */

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  
{
  Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
  base = b;
  if (base) 
    {
      base->SetParent(this);
    }
  (field=f)->SetParent(this);
  (actuals=a)->SetParentAll(this);
}

void Call::PrintChildren(int indentLevel) 
{
  if (base) 
    {
      base->Print(indentLevel+1);
    }
  field->Print(indentLevel+1);
  actuals->PrintAll(indentLevel+1, "(actuals) ");
}

bool Call::CheckCall(FnDecl *prototype, SymTable *env)
{
  List<VarDecl*> *formals = prototype->GetFormals();
  bool ret = true;

  if (formals->NumElements() != actuals->NumElements())
    {
      ReportError::NumArgsMismatch(field, formals->NumElements(), actuals->NumElements());
      return false;
    }

  Type *formalType, *actualType;
  for (int i = 0; i < formals->NumElements(); i++)
    {
      ret &= actuals->Nth(i)->Check(env);
      formalType = formals->Nth(i)->GetType();
      actualType = actuals->Nth(i)->GetRetType();

      if (!actualType->IsConvertableTo(formalType))
        {
          ReportError::ArgMismatch(actuals->Nth(i), i+1, actualType, formalType);
          ret = false;
        }
    }

  return ret;
}


bool Call::Check(SymTable *env)
{
  bool ret = true;

  if (!base)
    {
      Symbol *sym = env->find(field->getName(), S_FUNCTION);
      if (sym == NULL)
        {
          ReportError::IdentifierNotDeclared(field, LookingForVariable);
          SetRetType(Type::errorType);
          return false;
        }

      FnDecl *decl = dynamic_cast<FnDecl*>(sym->getNode());
      Assert(decl != 0);
      ret &= CheckCall(decl, env);

      SetRetType(decl->GetReturnType());
      return true;
    }
  else
    {
      ret &= base->Check(env);

      //printf("%s %s\n", base->GetRetType()->GetName(), field->getName());
      if (strcmp(base->GetRetType()->GetPrintNameForNode(), "ArrayType") == 0 &&
          strcmp(field->getName(), "length") == 0)
        {
          SetRetType(Type::intType);
          return ret;
        }

      // Error if base is not of a class's type
      NamedType *baseType = dynamic_cast<NamedType*>(base->GetRetType());
      if (baseType == 0)
        {
          ReportError::FieldNotFoundInBase(field, base->GetRetType());
          SetRetType(Type::errorType);
          return false;
        }

      // Check whether field is indeed a field of base
      Symbol *sym = NULL;
      if ((sym = env->findClassField(baseType->GetName(), field->getName(), S_FUNCTION)) == NULL)
        {
          ReportError::FieldNotFoundInBase(field, baseType);
          SetRetType(Type::errorType);
          return false;
        }

      FnDecl *prototype = dynamic_cast<FnDecl*>(sym->getNode());
      Assert(prototype != 0);

      ret &= CheckCall(prototype, env);

      SetRetType(prototype->GetReturnType());
    }

  return ret;
}

/* Class: NewExpr
 * ------------------
 * Implementation for NewExpr class
 */

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) 
{
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) 
{	
  cType->Print(indentLevel+1);
}

bool NewExpr::Check(SymTable *env)
{
  bool ret = true;

  ret &= cType->Check(env);
  if (!ret)
    {
      SetRetType(Type::errorType);
    }
  else
    {
      SetRetType(cType);
    }

  return ret;
}

/* Class: NewArrayExpr
 * ------------------
 * Implementation for NewArrayExpr class
 */

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) 
{
  Assert(sz != NULL && et != NULL);
  (size=sz)->SetParent(this); 
  (elemType=et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) 
{
  size->Print(indentLevel+1);
  elemType->Print(indentLevel+1);
}

bool NewArrayExpr::Check(SymTable *env)
{
  bool ret = true;

  ret &= size->Check(env);
  if (!size->GetRetType()->IsConvertableTo(Type::intType))
    {
      ReportError::NewArraySizeNotInteger(size);
      SetRetType(Type::errorType);
      ret = false;
    }

  ret &= elemType->Check(env);
  if (!ret)
    {
      SetRetType(Type::errorType);
    }
  else
    {
      SetRetType(new ArrayType(*location, elemType));
    }

  return ret;
}

/* Class: ReadIntegerExpr
 * ----------------------
 * Implementation for ReadIntegerExpr
 */

bool ReadIntegerExpr::Check(SymTable *env)
{
  SetRetType(Type::intType);
  return true;
}

/* Class: ReadLineExpr
 * -------------------
 * Implementation for ReadLineExpr
 *
 */

bool ReadLineExpr::Check(SymTable *env)
{
  SetRetType(Type::stringType);
  return true;
}
