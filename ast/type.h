/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */

#ifndef _H_ast_type
#define _H_ast_type

#include "ast/ast.h"
#include "ast/stmt.h"

extern SymTable *globalEnv;

class Type : public Node {
 public:
  static Type *intType, *doubleType, *boolType, *voidType,
              *nullType, *stringType, *errorType;

  Type(yyltype loc) : Node(loc) {}
  Type(const char *str);

  const char *GetPrintNameForNode() { return "Type"; }
  friend std::ostream& operator<<(std::ostream& out, Type *t) {
    t->PrintToStream(out); return out;
  }
  void PrintChildren(int indentLevel);
  virtual bool IsBuiltin() { return true; }
  virtual bool IsEquivalentTo(Type *other) { return this == other; }
  virtual bool IsConvertableTo(Type *other) {
    if (this == other || this == errorType) {
      return true;
    }
    if (!other->IsBuiltin() && this == nullType) {
      return true;
    }
    return false;
  }
  virtual void PrintToStream(std::ostream& out) { out << typeName; }
  virtual bool Check(SymTable *env) { return true; }
  virtual char *GetName() { return typeName; }
  virtual int GetQualifier() { return 0; }
  virtual Identifier *GetIdent() { return NULL; }

 protected:
  char *typeName;
};

class NamedType : public Type {
 public:
  NamedType(Identifier *i);

  const char *GetPrintNameForNode() { return "NamedType"; }
  void PrintChildren(int indentLevel);
  void PrintToStream(std::ostream& out) { out << id; }
  char *GetName() { return id->name(); }
  Identifier *GetIdent() { return id; }

  bool Check(SymTable *env);

  bool IsBuiltin() { return false; }
  bool IsEquivalentTo(Type *other);
  bool IsConvertableTo(Type *other);

 protected:
  Identifier *id;
};

class ArrayType : public Type {
 public:
  ArrayType(yyltype loc, Type *elemType);

  const char *GetPrintNameForNode() { return "ArrayType"; }
  void PrintChildren(int indentLevel);
  void PrintToStream(std::ostream& out) { out << elemType << "[]"; }
  bool Check(SymTable *env);
  Type *getElemType() { return elemType; }

  Identifier *GetIdent() { return elemType->GetIdent(); }
  bool IsBuiltin() { return false; }
  bool IsEquivalentTo(Type *other);
  bool IsConvertableTo(Type *other);

 protected:
  Type *elemType;
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
