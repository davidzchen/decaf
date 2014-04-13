/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct.
 *
 * pp2: You will need to add new expression and statement node c
 * classes for the additional grammar elements (Switch/Postfix)
 *
 * pp3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */

#ifndef DCC_AST_STMT_H__
#define DCC_AST_STMT_H__

#include "ast/ast.h"

class Decl;
class VarDecl;
class Expr;

class Program : public Node {
 public:
  Program(List<Decl*> *declList);
  const char *GetPrintNameForNode() { return "Program"; }
  void PrintChildren(int indent_level);
  void Check();
  void Emit();

 protected:
  List<Decl*> *decls_;
  SymTable *env_;
  CodeGenerator *codegen_;
  FrameAllocator *falloc_;
};

class Stmt : public Node {
 public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
  virtual bool CheckDecls(SymTable *env) { return true; }
  virtual bool CheckDecls(SymTable *env, bool inheritEnv) { return true; }
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                    SymTable *env) {}
};

class StmtBlock : public Stmt {
 public:
  StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
  const char *GetPrintNameForNode() { return "StmtBlock"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool CheckDecls(SymTable *env, bool inheritEnv);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  List<VarDecl*> *decls_;
  List<Stmt*> *stmts_;
  SymTable *block_env_;
};

class ConditionalStmt : public Stmt {
 public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                    SymTable *env) { }

 protected:
  Expr *test_;
  Stmt *body_;
};

class CaseStmt : public Stmt {
 public:
  CaseStmt(Expr *intConst, List<Stmt*> *stmtList);
  const char *GetPrintNameForNode() { return "Case"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Expr *ic_;
  List<Stmt*> *stmts_;
  SymTable *case_env_;
};

class DefaultStmt : public Stmt {
 public:
  DefaultStmt(List<Stmt*> *stmts);
  const char *GetPrintNameForNode() { return "Default"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  List<Stmt*> *stmts_;
  SymTable *case_env_;
};

class SwitchStmt : public Stmt {
 public:
  SwitchStmt(Expr *testExpr, List<CaseStmt*> *caseStmts,
             DefaultStmt *defaultStmt);
  const char *GetPrintNameForNode() { return "SwitchStmt"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Expr *test_;
  List<CaseStmt*> *cases_;
  DefaultStmt *default_case_;
};

class LoopStmt : public ConditionalStmt {
 public:
  LoopStmt(Expr *testExpr, Stmt *body)
          : ConditionalStmt(testExpr, body) {
    after_label_ = NULL;
  }
  virtual bool CheckDecls(SymTable *env) { return true; }
  virtual bool Check(SymTable *env) { return true; }
  char *GetAfterLabel() { return after_label_; }

 protected:
  char *after_label_;
};

class ForStmt : public LoopStmt {
 public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() { return "ForStmt"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Expr *init_;
  Expr *step_;
  SymTable *block_env_;
};

class WhileStmt : public LoopStmt {
 public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() { return "WhileStmt"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  SymTable *block_env_;
};

class IfStmt : public ConditionalStmt {
 public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() { return "IfStmt"; }
  void PrintChildren(int indent_level);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Stmt *else_body_;
};

class BreakStmt : public Stmt {
 public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
  const char *GetPrintNameForNode() { return "BreakStmt"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class ReturnStmt : public Stmt {
 public:
  ReturnStmt(yyltype loc, Expr *expr);
  const char *GetPrintNameForNode() { return "ReturnStmt"; }
  void PrintChildren(int indent_level);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Expr *expr_;
};

class PrintStmt : public Stmt {
 public:
  PrintStmt(List<Expr*> *arguments);
  const char *GetPrintNameForNode() { return "PrintStmt"; }
  void PrintChildren(int indent_level);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 private:
  bool PrintableType(Type *t);

 protected:
  List<Expr*> *args_;
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
