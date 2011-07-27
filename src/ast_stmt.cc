/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

/* Class: Program
 * --------------
 * Implementation of Program class
 */

Program::Program(List<Decl*> *d) 
{
  Assert(d != NULL);
  (decls=d)->SetParentAll(this);
  env = NULL;
}

void Program::PrintChildren(int indentLevel) 
{
  decls->PrintAll(indentLevel+1);
  printf("\n");
}

void Program::Check() 
{
  /* pp3: here is where the semantic analyzer is kicked off.
   *      The general idea is perform a tree traversal of the
   *      entire program, examining all constructs for compliance
   *      with the semantic rules.  Each node can have its own way of
   *      checking itself, which makes for a great use of inheritance
   *      and polymorphism in the node classes.
   */
  ClassDecl *d;

  env = new SymTable;

  // Pass 1: Build symbol table
  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->CheckDecls(env);
    }

  // Pass 2: Set up class inheritance hierarchy
  for (int i = 0; i < decls->NumElements(); i++)
    {
      try
        {
          d = dynamic_cast<ClassDecl*>(decls->Nth(i));
          if (d == 0)
            continue;

          d->Inherit(env);
        }
      catch (exception& e)
        {
          continue;
        }
    }

  // Pass 2: Scope check and type check
  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->Check(env);
    }
}

/* Class: StmtBlock
 * ----------------
 * Implementation of StmtBlock class
 */

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) 
{
  Assert(d != NULL && s != NULL);
  (decls = d)->SetParentAll(this);
  (stmts = s)->SetParentAll(this);
  blockEnv = NULL;
}

void StmtBlock::PrintChildren(int indentLevel) 
{
  decls->PrintAll(indentLevel + 1);
  stmts->PrintAll(indentLevel + 1);
}

bool StmtBlock::CheckDecls(SymTable *env)
{
  if ((blockEnv = env->addScope()) == false)
    return false;

  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->CheckDecls(blockEnv);
    }

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      stmts->Nth(i)->CheckDecls(blockEnv);
    }

  return true;
}

bool StmtBlock::Check(SymTable *env)
{
  /*
   * Note: don't use env passed as argument. Use blockEnv
   */

  for (int i = 0; i < decls->NumElements(); i++)
    {
      if (!decls->Nth(i)->Check(blockEnv))
        return false;
    }

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      if (!stmts->Nth(i)->Check(blockEnv))
        return false;
    }

  return true;
}

/* Class: ConditionalStmt
 * ----------------------
 * Implementation of ConditionalStmt class
 */

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) 
{
  Assert(t != NULL && b != NULL);
  (test = t)->SetParent(this);
  (body = b)->SetParent(this);
}

/* Class: CaseStmt
 * ---------------
 * Implementation of CaseStmt class
 */

CaseStmt::CaseStmt(Expr *intConst, List<Stmt*> *stmtList)
{
  Assert(intConst != NULL && stmtList != NULL);
  (i = intConst)->SetParent(this);
  (stmts = stmtList)->SetParentAll(this);
}

void CaseStmt::PrintChildren(int indentLevel)
{
  i->Print(indentLevel+1);
  stmts->PrintAll(indentLevel+1);
}

bool CaseStmt::Check(SymTable *env)
{
  return true;
}

/* Class: DefaultStmt
 * ---------------
 * Implementation of DefaultStmt class
 */

DefaultStmt::DefaultStmt(List<Stmt*> *stmtList)
{
  Assert(stmtList != NULL);
  (stmts = stmtList)->SetParentAll(this);
}

void DefaultStmt::PrintChildren(int indentLevel)
{
  stmts->PrintAll(indentLevel+1);
}

bool DefaultStmt::Check(SymTable *env)
{
  return true;
}

/* Class: SwitchStmt
 * ---------------
 * Implementation of SwitchStmt class
 */

SwitchStmt::SwitchStmt(Expr *testExpr, 
		       List<CaseStmt*> *caseStmts, 
		       DefaultStmt *defaultStmt)
{
  Assert(testExpr != NULL && caseStmts != NULL && defaultStmt != NULL);
  (test = testExpr)->SetParent(this);
  (cases = caseStmts)->SetParentAll(this);
  (defaultCase = defaultStmt)->SetParent(this);
}

void SwitchStmt::PrintChildren(int indentLevel)
{
  test->Print(indentLevel+1);
  cases->PrintAll(indentLevel+1);
  defaultCase->Print(indentLevel+1);
}

bool SwitchStmt::Check(SymTable *env)
{
  return true;
}

/* Class: ForStmt
 * ---------------
 * Implementation of ForStmt class
 */

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b) : LoopStmt(t, b) 
{ 
  Assert(i != NULL && t != NULL && s != NULL && b != NULL);
  (init = i)->SetParent(this);
  (step = s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) 
{
  init->Print(indentLevel+1, "(init) ");
  test->Print(indentLevel+1, "(test) ");
  step->Print(indentLevel+1, "(step) ");
  body->Print(indentLevel+1, "(body) ");
}

bool ForStmt::Check(SymTable *env)
{
  return true;
}

/* Class: WhileStmt
 * ---------------
 * Implementation of WhileStmt class
 */

void WhileStmt::PrintChildren(int indentLevel) 
{
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(body) ");
}

bool WhileStmt::Check(SymTable *env)
{
  return true;
}

/* Class: IfStmt
 * ---------------
 * Implementation of IfStmt class
 */

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) 
{ 
  Assert(t != NULL && tb != NULL); // else can be NULL
  elseBody = eb;
  if (elseBody) elseBody->SetParent(this);
}

void IfStmt::PrintChildren(int indentLevel) 
{
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(then) ");
  if (elseBody) 
    {
      elseBody->Print(indentLevel+1, "(else) ");
    }
}

bool IfStmt::Check(SymTable *env)
{
  return true;
}

/* Class: ReturnStmt
 * ---------------
 * Implementation of ReturnStmt class
 */

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) 
{ 
  Assert(e != NULL);
  (expr = e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) 
{
  expr->Print(indentLevel+1);
}

bool ReturnStmt::Check(SymTable *env)
{
  return true;
}

/* Class: PrintStmt
 * ---------------
 * Implementation of PrintStmt class
 */
  
PrintStmt::PrintStmt(List<Expr*> *a) 
{    
  Assert(a != NULL);
  (args = a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) 
{
  args->PrintAll(indentLevel+1, "(args) ");
}

bool PrintStmt::Check(SymTable *env)
{
  return true;
}
