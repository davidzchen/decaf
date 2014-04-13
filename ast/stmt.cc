/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */

#include "ast/stmt.h"
#include "ast/type.h"
#include "ast/decl.h"
#include "ast/expr.h"

SymTable *globalEnv = NULL;

/* Class: Program
 * --------------
 * Implementation of Program class
 */

Program::Program(List<Decl*> *d) {
  Assert(d != NULL);
  (decls_=d)->SetParentAll(this);
  env_ = NULL;
}

void Program::PrintChildren(int indent_level) {
  decls_->PrintAll(indent_level+1);
  fprintf(kOutputFile, "\n");
}

/* pp3: here is where the semantic analyzer is kicked off.
 *      The general idea is perform a tree traversal of the
 *      entire program, examining all constructs for compliance
 *      with the semantic rules.  Each node can have its own way of
 *      checking itself, which makes for a great use of inheritance
 *      and polymorphism in the node classes.
 */
void Program::Check() {
  ClassDecl *d;

  env_ = new SymTable;

  // Pass 1: Build symbol table
  for (int i = 0; i < decls_->NumElements(); i++) {
    decls_->Nth(i)->CheckDecls(env_);
  }

  // Pass 2: Set up class inheritance hierarchy
  for (int i = 0; i < decls_->NumElements(); i++) {
    d = dynamic_cast<ClassDecl*>(decls_->Nth(i));
    if (d == 0) {
      continue;
    }
    d->Inherit(env_);
  }

  globalEnv = env_;

  // Pass 2: Scope check and type check
  for (int i = 0; i < decls_->NumElements(); i++) {
    decls_->Nth(i)->Check(env_);
  }
}

/* pp4: here is where the code generation is kicked off.
 *      The general idea is perform a tree traversal of the
 *      entire program, generating instructions as you go.
 *      Each node can have its own way of translating itself,
 *      which makes for a great use of inheritance and
 *      polymorphism in the node classes.
 */
void Program::Emit() {
  codegen_ = new CodeGenerator;
  falloc_  = new FrameAllocator(gpRelative, FRAME_UP);
  for (int i = 0; i < decls_->NumElements(); i++) {
    VarDecl *varDecl = dynamic_cast<VarDecl*>(decls_->Nth(i));
    if (varDecl != 0) {
      varDecl->Emit(falloc_, codegen_, env_);
    }
  }

  for (int i = 0; i < decls_->NumElements(); i++) {
    ClassDecl *classDecl = dynamic_cast<ClassDecl*>(decls_->Nth(i));
    if (classDecl != 0) {
      classDecl->EmitSetup(falloc_, codegen_, env_);
    }
  }

  for (int i = 0; i < decls_->NumElements(); i++) {
    ClassDecl *classDecl = dynamic_cast<ClassDecl*>(decls_->Nth(i));
    if (classDecl != 0) {
      classDecl->Emit(falloc_, codegen_, env_);
    }
  }

  for (int i = 0; i < decls_->NumElements(); i++) {
    FnDecl *fnDecl = dynamic_cast<FnDecl*>(decls_->Nth(i));
    if (fnDecl != 0) {
      fnDecl->Emit(falloc_, codegen_, env_);
    }
  }

  codegen_->DoFinalCodeGen();
}

/* Class: StmtBlock
 * ----------------
 * Implementation of StmtBlock class
 */

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
  Assert(d != NULL && s != NULL);
  (decls_ = d)->SetParentAll(this);
  (stmts_ = s)->SetParentAll(this);
  block_env_ = NULL;
}

void StmtBlock::PrintChildren(int indent_level) {
  decls_->PrintAll(indent_level + 1);
  stmts_->PrintAll(indent_level + 1);
}

bool StmtBlock::CheckDecls(SymTable *env) {
  if ((block_env_ = env->addScope()) == false) {
    return false;
  }

  for (int i = 0; i < decls_->NumElements(); i++) {
    decls_->Nth(i)->CheckDecls(block_env_);
  }

  for (int i = 0; i < stmts_->NumElements(); i++) {
    stmts_->Nth(i)->CheckDecls(block_env_);
  }

  return true;
}

bool StmtBlock::CheckDecls(SymTable *env, bool inheritEnv) {
  if (!inheritEnv) {
    if ((block_env_ = env->addScope()) == false) {
      return false;
    }
  }

  for (int i = 0; i < decls_->NumElements(); i++) {
    decls_->Nth(i)->CheckDecls(block_env_);
  }

  for (int i = 0; i < stmts_->NumElements(); i++) {
    stmts_->Nth(i)->CheckDecls(block_env_);
  }

  return true;
}

bool StmtBlock::Check(SymTable *env) {
  /*
   * Note: don't use env passed as argument. Use block_env_
   */
  bool ret = true;

  for (int i = 0; i < decls_->NumElements(); i++) {
    ret &= decls_->Nth(i)->Check(block_env_);
  }

  for (int i = 0; i < stmts_->NumElements(); i++) {
    ret &= stmts_->Nth(i)->Check(block_env_);
  }

  return true;
}

void StmtBlock::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env) {
  for (int i = 0; i < decls_->NumElements(); i++) {
    decls_->Nth(i)->Emit(falloc, codegen, block_env_);
  }

  for (int i = 0; i < stmts_->NumElements(); i++) {
    stmts_->Nth(i)->Emit(falloc, codegen, block_env_);
  }
}

/* Class: ConditionalStmt
 * ----------------------
 * Implementation of ConditionalStmt class
 */

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
  Assert(t != NULL && b != NULL);
  (test_ = t)->set_parent(this);
  (body_ = b)->set_parent(this);
}

/* Class: CaseStmt
 * ---------------
 * Implementation of CaseStmt class
 */

CaseStmt::CaseStmt(Expr *intConst, List<Stmt*> *stmtList) {
  Assert(intConst != NULL && stmtList != NULL);
  (ic_ = intConst)->set_parent(this);
  (stmts_ = stmtList)->SetParentAll(this);
  case_env_ = NULL;
}

void CaseStmt::PrintChildren(int indent_level) {
  ic_->Print(indent_level+1);
  stmts_->PrintAll(indent_level+1);
}

bool CaseStmt::CheckDecls(SymTable *env) {
  bool ret = true;
  if ((case_env_ = env->addScope()) == false) {
    return false;
  }

  case_env_->setBreakNode(this);
  for (int i = 0; i < stmts_->NumElements(); i++) {
    ret &= stmts_->Nth(i)->CheckDecls(env);
  }

  return ret;
}

bool CaseStmt::Check(SymTable *env) {
  bool ret = true;
  ret &= ic_->Check(env);
  for (int i = 0; i < stmts_->NumElements(); i++) {
    ret &= stmts_->Nth(i)->Check(env);
  }
  return ret;
}

void CaseStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                         SymTable *env) {
  // FIXME: Implement CaseStmt IR Generation
  Failure("Switch not implemented");
}

/* Class: DefaultStmt
 * ---------------
 * Implementation of DefaultStmt class
 */

DefaultStmt::DefaultStmt(List<Stmt*> *stmtList) {
  Assert(stmtList != NULL);
  (stmts_ = stmtList)->SetParentAll(this);
}

void DefaultStmt::PrintChildren(int indent_level) {
  stmts_->PrintAll(indent_level+1);
}

bool DefaultStmt::CheckDecls(SymTable *env) {
  bool ret = true;
  if ((case_env_ = env->addScope()) == false) {
    return false;
  }

  case_env_->setBreakNode(this);
  for (int i = 0; i < stmts_->NumElements(); i++) {
    ret &= stmts_->Nth(i)->CheckDecls(env);
  }

  return ret;
}

bool DefaultStmt::Check(SymTable *env) {
  bool ret = true;
  for (int i = 0; i < stmts_->NumElements(); i++) {
    ret &= stmts_->Nth(i)->Check(env);
  }
  return ret;
}


void DefaultStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env) {
  // FIXME: Implement DefaultStmt IR Generation
  Failure("Switch not implemented");
}

/* Class: SwitchStmt
 * ---------------
 * Implementation of SwitchStmt class
 */

SwitchStmt::SwitchStmt(Expr *testExpr, List<CaseStmt*> *caseStmts, 
		                   DefaultStmt *defaultStmt) {
  Assert(testExpr != NULL && caseStmts != NULL && defaultStmt != NULL);
  (test_ = testExpr)->set_parent(this);
  (cases_ = caseStmts)->SetParentAll(this);
  (default_case_ = defaultStmt)->set_parent(this);
}

void SwitchStmt::PrintChildren(int indent_level) {
  test_->Print(indent_level + 1);
  cases_->PrintAll(indent_level + 1);
  default_case_->Print(indent_level + 1);
}

bool SwitchStmt::CheckDecls(SymTable *env) {
  bool ret = true;
  for (int i = 0; i < cases_->NumElements(); i++) {
    ret &= cases_->Nth(i)->CheckDecls(env);
  }
  ret &= default_case_->CheckDecls(env);
  return ret;
}

bool SwitchStmt::Check(SymTable *env) {
  bool ret = true;
  ret &= test_->Check(env);
  if (!test_->GetRetType()->IsEquivalentTo(Type::intType)) {
    ReportError::SwitchTestNotInt(test_);
    ret = false;
  }
  for (int i = 0; i < cases_->NumElements(); i++) {
    ret &= cases_->Nth(i)->Check(env);
  }
  ret &= default_case_->Check(env);
  return ret;
}


void SwitchStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                      SymTable *env) {
  // FIXME: Implement SwitchStmt IR Generation
  Failure("Switch not implemented");
}

/* Class: ForStmt
 * ---------------
 * Implementation of ForStmt class
 */

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b) : LoopStmt(t, b) { 
  Assert(i != NULL && t != NULL && s != NULL && b != NULL);
  (init_ = i)->set_parent(this);
  (step_ = s)->set_parent(this);
}

void ForStmt::PrintChildren(int indent_level) {
  init_->Print(indent_level + 1, "(init) ");
  test_->Print(indent_level + 1, "(test) ");
  step_->Print(indent_level + 1, "(step) ");
  body_->Print(indent_level + 1, "(body) ");
}

bool ForStmt::CheckDecls(SymTable *env) {
  if ((block_env_ = env->addScope()) == false) {
    return false;
  }

  block_env_->setBreakNode(this);
  return body_->CheckDecls(block_env_);
}

bool ForStmt::Check(SymTable *env) {
  bool ret = true;
  ret &= test_->Check(env);
  if (!test_->GetRetType()->IsEquivalentTo(Type::boolType)) {
    ReportError::TestNotBoolean(test_);
    ret = false;
  }
  ret &= init_->Check(env);
  ret &= step_->Check(env);
  ret &= body_->Check(block_env_);
  return ret;
}

void ForStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                   SymTable *env) {
  char *loopLabel = codegen->NewLabel();
  after_label_ = codegen->NewLabel();
  init_->Emit(falloc, codegen, block_env_);
  codegen->GenLabel(loopLabel);
  test_->Emit(falloc, codegen, block_env_);
  codegen->GenIfZ(test_->GetFrameLocation(), after_label_);
  body_->Emit(falloc, codegen, block_env_);
  step_->Emit(falloc, codegen, block_env_);
  codegen->GenGoto(loopLabel);
  codegen->GenLabel(after_label_);
}

/* Class: WhileStmt
 * ---------------
 * Implementation of WhileStmt class
 */

void WhileStmt::PrintChildren(int indent_level) {
  test_->Print(indent_level+1, "(test) ");
  body_->Print(indent_level+1, "(body) ");
}

bool WhileStmt::CheckDecls(SymTable *env) {
  if ((block_env_ = env->addScope()) == false) {
    return false;
  }

  block_env_->setBreakNode(this);
  return body_->CheckDecls(block_env_);
}

bool WhileStmt::Check(SymTable *env) {
  bool ret = true;
  ret &= test_->Check(env);
  if (!test_->GetRetType()->IsEquivalentTo(Type::boolType)) {
    ReportError::TestNotBoolean(test_);
    ret = false;
  }
  ret &= body_->Check(block_env_);
  return ret;
}

void WhileStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen, 
                     SymTable *env) {
  char *loopLabel = codegen->NewLabel();
  after_label_ = codegen->NewLabel();
  codegen->GenLabel(loopLabel);
  test_->Emit(falloc, codegen, block_env_);
  codegen->GenIfZ(test_->GetFrameLocation(), after_label_);
  body_->Emit(falloc, codegen, block_env_);
  codegen->GenGoto(loopLabel);
  codegen->GenLabel(after_label_);
}

/* Class: IfStmt
 * ---------------
 * Implementation of IfStmt class
 */

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
  Assert(t != NULL && tb != NULL); // else can be NULL
  else_body_ = eb;
  if (else_body_) {
    else_body_->set_parent(this);
  }
}

void IfStmt::PrintChildren(int indent_level) {
  test_->Print(indent_level+1, "(test) ");
  body_->Print(indent_level+1, "(then) ");
  if (else_body_) {
    else_body_->Print(indent_level+1, "(else) ");
  }
}

bool IfStmt::CheckDecls(SymTable *env) {
  bool ret = true;
  ret &= body_->CheckDecls(env);
  if (else_body_) {
    ret &= else_body_->CheckDecls(env);
  }
  return ret;
}

bool IfStmt::Check(SymTable *env) {
  bool ret = true;
  ret &= test_->Check(env);
  if (!test_->GetRetType()->IsConvertableTo(Type::boolType)) {
    ReportError::TestNotBoolean(test_);
    ret = false;
  }
  ret &= body_->Check(env);
  if (else_body_) {
    ret &= else_body_->Check(env);
  }
  return ret;
}

void IfStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                  SymTable *env) {
  char *ifLabel = codegen->NewLabel();
  char *elseLabel = NULL;

  test_->Emit(falloc, codegen, env);
  codegen->GenIfZ(test_->GetFrameLocation(), ifLabel);
  body_->Emit(falloc, codegen, env);
  if (else_body_) {
    elseLabel = codegen->NewLabel();
    codegen->GenGoto(elseLabel);
    codegen->GenLabel(ifLabel);
    else_body_->Emit(falloc, codegen, env);
    codegen->GenLabel(elseLabel);
  } else {
    codegen->GenLabel(ifLabel);
  }
}

/* Class: BreakStmt
 * ----------------
 * Implementation of BreakStmt class
 */

bool BreakStmt::Check(SymTable *env) {
  if (env->getBreakNode() == NULL) {
    ReportError::BreakOutsideLoop(this);
    return false;
  }
  return true;
}

void BreakStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env) {
  LoopStmt *loopNode = dynamic_cast<LoopStmt*>(env->getBreakNode());
  Assert(loopNode != 0);
  codegen->GenGoto(loopNode->GetAfterLabel());
}

/* Class: ReturnStmt
 * ---------------
 * Implementation of ReturnStmt class
 */

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
  Assert(e != NULL);
  (expr_ = e)->set_parent(this);
}

void ReturnStmt::PrintChildren(int indent_level) {
  expr_->Print(indent_level+1);
}

bool ReturnStmt::Check(SymTable *env) {
  FnDecl *fn = NULL;
  bool ret = true;
  fn = dynamic_cast<FnDecl*>(env->getRefNode());
  Assert(fn != 0);
  ret &= expr_->Check(env);
  if (!expr_->GetRetType()->IsConvertableTo(fn->GetReturnType())) {
    ReportError::ReturnMismatch(this, expr_->GetRetType(), fn->GetReturnType());
    ret = false;
  }
  return ret;
}

void ReturnStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                      SymTable *env) {
  expr_->Emit(falloc, codegen, env);
  codegen->GenReturn(expr_->GetFrameLocation());
}

/* Class: PrintStmt
 * ---------------
 * Implementation of PrintStmt class
 */
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
  Assert(a != NULL);
  (args_ = a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indent_level) {
  args_->PrintAll(indent_level+1, "(args) ");
}

bool PrintStmt::PrintableType(Type *type) {
  return (type->IsConvertableTo(Type::intType)
       || type->IsConvertableTo(Type::boolType)
       || type->IsConvertableTo(Type::stringType));
}

bool PrintStmt::Check(SymTable *env) {
  bool ret = true;
  for (int i = 0; i < args_->NumElements(); i++) {
    ret &= args_->Nth(i)->Check(env);
    Type *argType = args_->Nth(i)->GetRetType();
    if (!PrintableType(argType)) {
      ReportError::PrintArgMismatch(args_->Nth(i), i+1, argType);
      ret = false;
    }
  }
  return ret;
}

void PrintStmt::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env) {
  Expr *arg = NULL;
  Location *argloc = NULL;
  Type *argtype = NULL;

  for (int i = 0; i < args_->NumElements(); i++) {
    arg = args_->Nth(i);
    arg->Emit(falloc, codegen, env);
    argloc = arg->GetFrameLocation();
    argtype = arg->GetRetType();
    if (argtype->IsConvertableTo(Type::intType)) {
      codegen->GenBuiltInCall(falloc, PrintInt, argloc, NULL);
    } else if (argtype->IsConvertableTo(Type::boolType)) {
      codegen->GenBuiltInCall(falloc, PrintBool, argloc, NULL);
    } else if (argtype->IsConvertableTo(Type::stringType)) {
      codegen->GenBuiltInCall(falloc, PrintString, argloc, NULL);
    }
  }
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
