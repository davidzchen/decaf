/* File: ast_expr.h
 * ----------------
 * The Expr class and its subclasses are used to represent
 * expressions in the parse tree.  For each expression in the
 * language (add, call, New, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Expr classes to implement
 * semantic analysis for rules pertaining to expressions.
 */


#ifndef DCC_AST_EXPR_H__
#define DCC_AST_EXPR_H__

#include "ast.h"
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"

class NamedType; // for new
class Type; // for NewArray

class Expr : public Stmt {
 public:
  Expr(yyltype loc) : Stmt(loc) {
    needsDereference = false;
    reference = NULL;
  }
  Expr() : Stmt() {}
  void SetRetType(Type *t) { ret_type_ = t; }
  Type *GetRetType() { return ret_type_; }
  virtual bool Check(SymTable *env) { return true; }
  Location *GetFrameLocation() { return frameLocation; }
  bool NeedsDereference() { return needsDereference; }
  Location *GetReference() { return reference; }
 
 protected:
  Type* ret_type_;
  Location* frame_location_;
  Location* reference_;
  bool needs_dereference_;
};

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */

class EmptyExpr : public Expr {
 public:
  EmptyExpr() { ret_type_ = Type::voidType; }
  const char *GetPrintNameForNode() { return "Empty"; }
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
    frameLocation = NULL;
  }
};

class IntConstant : public Expr {
 public:
  IntConstant(yyltype loc, int val);
  const char *GetPrintNameForNode() { return "IntConstant"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
    frameLocation = codegen->GenLoadConstant(falloc, value);
  }
 
 protected:
  int value_;
};

class DoubleConstant : public Expr {
 public:
  DoubleConstant(yyltype loc, double val);
  const char *GetPrintNameForNode() { return "DoubleConstant"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) { }
 
 protected:
  double value_;
};

class BoolConstant : public Expr { 
 public:
  BoolConstant(yyltype loc, bool val);
  const char *GetPrintNameForNode() { return "BoolConstant"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
    frameLocation = codegen->GenLoadConstant(falloc, (int) value);
  }
 
 protected:
  bool value_;
};

class StringConstant : public Expr {  
 public:
  StringConstant(yyltype loc, const char *val);
  const char *GetPrintNameForNode() { return "StringConstant"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
    frameLocation = codegen->GenLoadConstant(falloc, value);
  }
 
 protected:
  char* value_;
};

class NullConstant: public Expr {
 public: 
  NullConstant(yyltype loc) : Expr(loc) { ret_type_ = Type::nullType; }
  const char *GetPrintNameForNode() { return "NullConstant"; }
  bool Check(SymTable *env) { return true; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
    frameLocation = codegen->GenLoadConstant(falloc, 0);
  }
};

class Operator : public Node { 
 public:
  Operator(yyltype loc, const char *tok);
  const char *GetPrintNameForNode() { return "Operator"; }
  void PrintChildren(int indentLevel);
  friend ostream& operator<<(ostream& out, Operator *o) {
    return out << o->tokenString;
  }
  bool Check(SymTable *env) { return true; }
  char *GetTokenString() { return tokenString; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) { }
 
 protected:
  char token_string_[4];
};
 
class CompoundExpr : public Expr { 
 public:
  CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
  CompoundExpr(Operator *op, Expr *rhs);            // for unary
  CompoundExpr(Expr *lhs, Operator *op);            // for postfix
  void PrintChildren(int indentLevel);
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen, 
                    SymTable *env) { 
  }
 
 protected:
  Operator* op_;
  // left will be NULL if unary
  Expr* left_;
  Expr* right_; 
};

class ArithmeticExpr : public CompoundExpr {
 public:
  ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs)
      : CompoundExpr(lhs, op, rhs) {}
  ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op, rhs) {}
  const char *GetPrintNameForNode() { return "ArithmeticExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class RelationalExpr : public CompoundExpr {
 public:
  RelationalExpr(Expr *lhs, Operator *op, Expr *rhs)
      : CompoundExpr(lhs, op, rhs) {}
  const char *GetPrintNameForNode() { return "RelationalExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class EqualityExpr : public CompoundExpr {
 public:
  EqualityExpr(Expr *lhs, Operator *op, Expr *rhs)
      : CompoundExpr(lhs, op, rhs) {}
  const char *GetPrintNameForNode() { return "EqualityExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class LogicalExpr : public CompoundExpr {
 public:
  LogicalExpr(Expr *lhs, Operator *op, Expr *rhs)
    : CompoundExpr(lhs, op, rhs) {}
  LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
  const char *GetPrintNameForNode() { return "LogicalExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class PostfixExpr : public CompoundExpr {
 public:
  PostfixExpr(Expr *lhs, Operator *op) : CompoundExpr(lhs, op) {}
  const char *GetPrintNameForNode() { return "PostfixExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class AssignExpr : public CompoundExpr {
 public:
  AssignExpr(Expr *lhs, Operator *op, Expr *rhs)
    : CompoundExpr(lhs, op, rhs) {}
  const char *GetPrintNameForNode() { return "AssignExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class LValue : public Expr {
 public:
  LValue(yyltype loc) : Expr(loc) { }
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) { }
};

class This : public Expr {
 public:
  This(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() { return "This"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class ArrayAccess : public LValue { 
 public:
  ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
  const char *GetPrintNameForNode() { return "ArrayAccess"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);

 protected:
  Expr* base_;
  Expr* subscript_;
};

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */

class FieldAccess : public LValue { 
 public:
  FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
  const char *GetPrintNameForNode() { return "FieldAccess"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  Expr *GetBase() { return base; }
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr* base_;	// will be NULL if no explicit base
  Identifier* field_;
};

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */

class Call : public Expr { 
 public:
  Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
  const char *GetPrintNameForNode() { return "Call"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  int EmitActuals(FrameAllocator *falloc, CodeGenerator *codegen,
                  SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 private:
  bool CheckCall(FnDecl *prototype, SymTable *env);
  bool CheckActuals(SymTable *env);
 
 protected:
  Expr* base_;  // will be NULL if no explicit base
  Identifier* field_;
  List<Expr*>* actuals_;
};

class NewExpr : public Expr { 
 public:
  NewExpr(yyltype loc, NamedType *clsType);
  const char *GetPrintNameForNode() { return "NewExpr"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  NamedType* c_type_;
};

class NewArrayExpr : public Expr { 
 public:
  NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
  const char *GetPrintNameForNode() { return "NewArrayExpr"; }
  void PrintChildren(int indentLevel);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
 
 protected:
  Expr* size_;
  Type* elem_type_;
};

class ReadIntegerExpr : public Expr {
 public:
  ReadIntegerExpr(yyltype loc) : Expr(loc) {}
  const char *GetPrintNameForNode() { return "ReadIntegerExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

class ReadLineExpr : public Expr {
 public:
  ReadLineExpr(yyltype loc) : Expr (loc) {}
  const char *GetPrintNameForNode() { return "ReadLineExpr"; }
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
};

/* vim: set ai ts=2 sts=2 sw=2 et: */    
#endif
