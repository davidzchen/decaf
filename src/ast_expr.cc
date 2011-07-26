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

bool CompoundExpr::Check(SymTable *env)
{
  if (left && !left->Check(env))
    return false;

  if (right && !right->Check(env))
    return false;
}

/* Class: ArithmeticExpr
 * ------------------
 * Implementation for ArithmeticExpr class
 */

bool ArithmeticExpr::Check(SymTable *env)
{
  if (left && !left->Check(env))
    return false;

  if (!right->Check(env))
    return false;
}

/* Class: RelationalExpr
 * ------------------
 * Implementation for RelationalExpr class
 */

bool RelationalExpr::Check(SymTable *env)
{
  if (!left->Check(env))
    return false;

  if (!right->Check(env))
    return false;
}

/* Class: EqualityExpr
 * ------------------
 * Implementation for EqualityExpr class
 */

bool EqualityExpr::Check(SymTable *env)
{
  if (!left->Check(env))
    return false;

  if (!right->Check(env))
    return false;
}

/* Class: LogicalExpr
 * ------------------
 * Implementation for LogicalExpr class
 */

bool LogicalExpr::Check(SymTable *env)
{
  if (left && !left->Check(env))
    return false;

  if (!right->Check(env))
    return false;
}

/* Class: PostfixExpr
 * ------------------
 * Implementation for PostfixExpr class
 */

bool PostfixExpr::Check(SymTable *env)
{
  if (!left->Check(env))
    return false;
}

/* Class: AssignExpr
 * ------------------
 * Implementation for AssignExpr class
 */

bool AssignExpr::Check(SymTable *env)
{
  if (!left->Check(env))
    return false;

  if (!right->Check(env))
      return false;
}

/* Class: This
 * ----------
 * Implementation of This class
 */

bool This::Check(SymTable *env)
{
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
  return true;
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
  return true;
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

bool Call::Check(SymTable *env)
{
  return true;
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
  return true;
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
  return true;
}
