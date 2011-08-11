/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */

#include <config.h>
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

SymTable *globalEnv = NULL;

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

/* pp3: here is where the semantic analyzer is kicked off.
 *      The general idea is perform a tree traversal of the
 *      entire program, examining all constructs for compliance
 *      with the semantic rules.  Each node can have its own way of
 *      checking itself, which makes for a great use of inheritance
 *      and polymorphism in the node classes.
 */
void Program::Check() 
{
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
      d = dynamic_cast<ClassDecl*>(decls->Nth(i));
      if (d == 0)
        continue;

      d->Inherit(env);
    }

  globalEnv = env;

  // Pass 2: Scope check and type check
  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->Check(env);
    }
}

/* pp4: here is where the code generation is kicked off.
 *      The general idea is perform a tree traversal of the
 *      entire program, generating instructions as you go.
 *      Each node can have its own way of translating itself,
 *      which makes for a great use of inheritance and
 *      polymorphism in the node classes.
 */
void Program::Emit()
{
  codegen = new CodeGenerator;
  falloc  = new FrameAllocator(gpRelative, FRAME_UP);

  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->Emit(falloc, codegen, env);
    }

  codegen->DoFinalCodeGen();
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

bool StmtBlock::CheckDecls(SymTable *env, bool inheritEnv)
{
  if (!inheritEnv)
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
  bool ret = true;

  for (int i = 0; i < decls->NumElements(); i++)
    {
      ret &= decls->Nth(i)->Check(blockEnv);
    }

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      ret &= stmts->Nth(i)->Check(blockEnv);
    }

  return true;
}

void StmtBlock::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env)
{
  for (int i = 0; i < decls->NumElements(); i++)
    {
      decls->Nth(i)->Emit(falloc, codegen, blockEnv);
    }

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      stmts->Nth(i)->Emit(falloc, codegen, blockEnv);
    }
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
  (ic = intConst)->SetParent(this);
  (stmts = stmtList)->SetParentAll(this);
  caseEnv = NULL;
}

void CaseStmt::PrintChildren(int indentLevel)
{
  ic->Print(indentLevel+1);
  stmts->PrintAll(indentLevel+1);
}

bool CaseStmt::CheckDecls(SymTable *env)
{
  bool ret = true;

  if ((caseEnv = env->addScope()) == false)
    return false;

  caseEnv->setBreakNode(this);

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      ret &= stmts->Nth(i)->CheckDecls(env);
    }

  return ret;
}

bool CaseStmt::Check(SymTable *env)
{
  bool ret = true;

  ret &= ic->Check(env);

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      ret &= stmts->Nth(i)->Check(env);
    }

  return ret;
}

void CaseStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                         SymTable *env)
{
  // FIXME: Implement CaseStmt IR Generation
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

bool DefaultStmt::CheckDecls(SymTable *env)
{
  bool ret = true;

  if ((caseEnv = env->addScope()) == false)
    return false;

  caseEnv->setBreakNode(this);

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      ret &= stmts->Nth(i)->CheckDecls(env);
    }

  return ret;
}

bool DefaultStmt::Check(SymTable *env)
{
  bool ret = true;

  for (int i = 0; i < stmts->NumElements(); i++)
    {
      ret &= stmts->Nth(i)->Check(env);
    }

  return ret;
}


void DefaultStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env)
{
  // FIXME: Implement DefaultStmt IR Generation
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

bool SwitchStmt::CheckDecls(SymTable *env)
{
  bool ret = true;

  for (int i = 0; i < cases->NumElements(); i++)
    {
      ret &= cases->Nth(i)->CheckDecls(env);
    }

  ret &= defaultCase->CheckDecls(env);

  return ret;
}

bool SwitchStmt::Check(SymTable *env)
{
  bool ret = true;

  ret &= test->Check(env);
  if (!test->GetRetType()->IsEquivalentTo(Type::intType))
    {
      ReportError::SwitchTestNotInt(test);
      ret = false;
    }

  for (int i = 0; i < cases->NumElements(); i++)
    {
      ret &= cases->Nth(i)->Check(env);
    }

  ret &= defaultCase->Check(env);

  return ret;
}


void SwitchStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env)
{
  // FIXME: Implement SwitchStmt IR Generation
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

bool ForStmt::CheckDecls(SymTable *env)
{
  if ((blockEnv = env->addScope()) == false)
    return false;

  blockEnv->setBreakNode(this);

  return body->CheckDecls(blockEnv);
}

bool ForStmt::Check(SymTable *env)
{
  bool ret = true;

  ret &= test->Check(env);
  if (!test->GetRetType()->IsEquivalentTo(Type::boolType))
    {
      ReportError::TestNotBoolean(test);
      ret = false;
    }

  ret &= init->Check(env);
  ret &= step->Check(env);
  ret &= body->Check(blockEnv);

  return ret;
}


void ForStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                   SymTable *env)
{
  char *loopLabel = codegen->NewLabel();
  afterLabel = codegen->NewLabel();

  init->Emit(falloc, codegen, blockEnv);
  codegen->GenLabel(loopLabel);
  test->Emit(falloc, codegen, blockEnv);
  codegen->GenIfZ(test->GetFrameLocation(), afterLabel);
  body->Emit(falloc, codegen, blockEnv);
  step->Emit(falloc, codegen, blockEnv);
  codegen->GenGoto(loopLabel);
  codegen->GenLabel(afterLabel);
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

bool WhileStmt::CheckDecls(SymTable *env)
{
  if ((blockEnv = env->addScope()) == false)
    return false;

  blockEnv->setBreakNode(this);

  return body->CheckDecls(blockEnv);
}

bool WhileStmt::Check(SymTable *env)
{
  bool ret = true;

  ret &= test->Check(env);

  if (!test->GetRetType()->IsEquivalentTo(Type::boolType))
    {
      ReportError::TestNotBoolean(test);
      ret = false;
    }

  ret &= body->Check(blockEnv);

  return ret;
}


void WhileStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env)
{
  char *loopLabel = codegen->NewLabel();

  afterLabel = codegen->NewLabel();

  codegen->GenLabel(loopLabel);
  test->Emit(falloc, codegen, blockEnv);
  codegen->GenIfZ(test->GetFrameLocation(), afterLabel);
  body->Emit(falloc, codegen, blockEnv);
  codegen->GenGoto(loopLabel);
  codegen->GenLabel(afterLabel);

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

bool IfStmt::CheckDecls(SymTable *env)
{
  bool ret = true;

  ret &= body->CheckDecls(env);

  if (elseBody)
    {
      ret &= elseBody->CheckDecls(env);
    }

  return ret;
}

bool IfStmt::Check(SymTable *env)
{
  bool ret = true;

  ret &= test->Check(env);
  if (!test->GetRetType()->IsConvertableTo(Type::boolType))
    {
      ReportError::TestNotBoolean(test);
      ret = false;
    }

  ret &= body->Check(env);

  if (elseBody)
    ret &= elseBody->Check(env);

  return ret;
}


void IfStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                  SymTable *env)
{
  char *ifLabel = codegen->NewLabel();
  char *elseLabel = NULL;

  test->Emit(falloc, codegen, env);
  codegen->GenIfZ(test->GetFrameLocation(), ifLabel);
  body->Emit(falloc, codegen, env);

  if (elseBody)
    {
      elseLabel = codegen->NewLabel();
      codegen->GenGoto(elseLabel);
      codegen->GenLabel(ifLabel);
      elseBody->Emit(falloc, codegen, env);
      codegen->GenLabel(elseLabel);
    }
  else
    {
      codegen->GenLabel(ifLabel);
    }
}

/* Class: BreakStmt
 * ----------------
 * Implementation of BreakStmt class
 */

bool BreakStmt::Check(SymTable *env)
{
  if (env->getBreakNode() == NULL)
    {
      ReportError::BreakOutsideLoop(this);
      return false;
    }
  return true;
}


void BreakStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env)
{
  LoopStmt *loopNode = dynamic_cast<LoopStmt*>(env->getBreakNode());
  Assert(loopNode != 0);

  codegen->GenGoto(loopNode->GetAfterLabel());
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
  FnDecl *fn = NULL;
  bool ret = true;

  fn = dynamic_cast<FnDecl*>(env->getRefNode());
  Assert(fn != 0);

  ret &= expr->Check(env);

  if (!expr->GetRetType()->IsConvertableTo(fn->GetReturnType()))
    {
      ReportError::ReturnMismatch(this, expr->GetRetType(), fn->GetReturnType());
      ret = false;
    }

  return ret;
}


void ReturnStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                      SymTable *env)
{
  expr->Emit(falloc, codegen, env);
  codegen->GenReturn(expr->GetFrameLocation());
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

bool PrintStmt::PrintableType(Type *type)
{
  return (type->IsConvertableTo(Type::intType)
       || type->IsConvertableTo(Type::boolType)
       || type->IsConvertableTo(Type::stringType));
}

bool PrintStmt::Check(SymTable *env)
{
  bool ret = true;
  Type *argType;

  for (int i = 0; i < args->NumElements(); i++)
    {
      ret &= args->Nth(i)->Check(env);
      argType = args->Nth(i)->GetRetType();
      if (!PrintableType(argType))
        {
          ReportError::PrintArgMismatch(args->Nth(i), i+1, argType);
          ret = false;
        }
    }

  return ret;
}


void PrintStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env)
{
  Expr *arg = NULL;
  Location *argloc = NULL;
  Type *argtype = NULL;

  for (int i = 0; i < args->NumElements(); i++)
    {
      arg = args->Nth(i);
      arg->Emit(falloc, codegen, env);
      argloc = arg->GetFrameLocation();
      argtype = arg->GetRetType();

      if (argtype->IsConvertableTo(Type::intType))
        {
          codegen->GenBuiltInCall(falloc, PrintInt, argloc, NULL);
        }
      else if (argtype->IsConvertableTo(Type::boolType))
        {
          codegen->GenBuiltInCall(falloc, PrintBool, argloc, NULL);
        }
      else if (argtype->IsConvertableTo(Type::stringType))
        {
          codegen->GenBuiltInCall(falloc, PrintString, argloc, NULL);
        }
    }
}
