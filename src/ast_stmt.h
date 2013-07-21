/* File: ast_stmt.h                          -*- C++ -*-
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

#ifndef AST_STMT_H__
#define AST_STMT_H__

#include "ast.h"

class Decl;
class VarDecl;
class Expr;
  
class Program : public Node {
 public:
  Program(List<Decl*> *declList);
  const char *GetPrintNameForNode() { return "Program"; }
  void PrintChildren(int indentLevel);
  void Check();
  void Emit();
 
 protected:
  List<Decl*> *decls;
  SymTable *env;
  CodeGenerator *codegen;
  FrameAllocator *falloc;
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
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool CheckDecls(SymTable *env, bool inheritEnv);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  List<VarDecl*> *decls;
  List<Stmt*> *stmts;
  SymTable *blockEnv;
};

class ConditionalStmt : public Stmt {
 public:
  ConditionalStmt(Expr *testExpr, Stmt *body);
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                    SymTable *env) { }
 
 protected:
  Expr *test;
  Stmt *body;
};

class CaseStmt : public Stmt {
 public:
  CaseStmt(Expr *intConst, List<Stmt*> *stmtList);
  const char *GetPrintNameForNode() { return "Case"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr *ic;
  List<Stmt*> *stmts;
  SymTable *caseEnv;
};

class DefaultStmt : public Stmt { 
 public:
  DefaultStmt(List<Stmt*> *stmts);
  const char *GetPrintNameForNode() { return "Default"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  List<Stmt*> *stmts;
  SymTable *caseEnv;
};

class SwitchStmt : public Stmt { 
 public:
  SwitchStmt(Expr *testExpr, List<CaseStmt*> *caseStmts,
             DefaultStmt *defaultStmt);
  const char *GetPrintNameForNode() { return "SwitchStmt"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr *test;
  List<CaseStmt*> *cases;
  DefaultStmt *defaultCase;
};

class LoopStmt : public ConditionalStmt {
 public:
  LoopStmt(Expr *testExpr, Stmt *body)
          : ConditionalStmt(testExpr, body) {
    afterLabel = NULL;
  }
  virtual bool CheckDecls(SymTable *env) { return true; }
  virtual bool Check(SymTable *env) { return true; }
  char *GetAfterLabel() { return afterLabel; }

 protected:
  char *afterLabel;
};

class ForStmt : public LoopStmt {
 public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
  const char *GetPrintNameForNode() { return "ForStmt"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr *init, *step;
  SymTable *blockEnv;
};

class WhileStmt : public LoopStmt {
 public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
  const char *GetPrintNameForNode() { return "WhileStmt"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  SymTable *blockEnv;
};

class IfStmt : public ConditionalStmt {
 public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
  const char *GetPrintNameForNode() { return "IfStmt"; }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Stmt *elseBody;
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
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr *expr;
};

class PrintStmt : public Stmt { 
 public:
  PrintStmt(List<Expr*> *arguments);
  const char *GetPrintNameForNode() { return "PrintStmt"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  List<Expr*> *args;

 private:
  bool PrintableType(Type *t);
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
