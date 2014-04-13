/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */

#include <string.h>

#include "ast/type.h"
#include "ast/decl.h"

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error");

/* Class: Type
 * -----------
 * Implementation of Type class
 */

Type::Type(const char *n) {
  Assert(n);
  typeName = strdup(n);
}

void Type::PrintChildren(int indentLevel) {
  fprintf(kOutputFile, "%s", typeName);
}

/* Class: NamedType
 * ----------------
 * Implementation of NamedType class
 */

NamedType::NamedType(Identifier *i) : Type(*i->location()) {
  Assert(i != NULL);
  (id = i)->set_parent(this);
}

void NamedType::PrintChildren(int indentLevel) {
  id->Print(indentLevel + 1);
}

bool NamedType::Check(SymTable *env) {
  if (!env->find(id->name())) {
    return false;
  }
  return true;
}

bool NamedType::IsConvertableTo(Type *other) {
  Symbol *thisSym = NULL;
  ClassDecl *classDecl = NULL;
  char *otherName = other->GetName();

  if (other->IsBuiltin()) {
    return false;
  }

  if (IsEquivalentTo(other)) {
    return true;
  }

  if ((thisSym = globalEnv->find(id->name(), S_CLASS)) == NULL) {
    return false;
  }

  classDecl = dynamic_cast<ClassDecl*>(thisSym->getNode());
  Assert(classDecl != 0);

  if (classDecl->ImplementsInterface(otherName)) {
    return true;
  }

  if (thisSym->getEnv()->subclassOf(otherName)) {
    return true;
  }

  return false;
}

bool NamedType::IsEquivalentTo(Type *other) {
  NamedType *nOther = NULL;
  nOther = dynamic_cast<NamedType*>(other);
  if (nOther == 0) {
    return false;
  }
  return (strcmp(id->name(), nOther->GetName()) == 0);
}

/* Class: ArrayType
 * ----------------
 * Implementation of ArrayType class
 */

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
  Assert(et != NULL);
  (elemType = et)->set_parent(this);
}

void ArrayType::PrintChildren(int indentLevel) {
  elemType->Print(indentLevel + 1);
}

bool ArrayType::Check(SymTable *env) {
  return elemType->Check(env);
}

bool ArrayType::IsConvertableTo(Type *other) {
  if (other->IsEquivalentTo(Type::errorType)) {
    return true;
  }

  ArrayType *nOther = dynamic_cast<ArrayType*>(other);
  if (nOther == 0) {
    return false;
  }

  return elemType->IsEquivalentTo(nOther->getElemType());
}

bool ArrayType::IsEquivalentTo(Type *other) {
  ArrayType *nOther = dynamic_cast<ArrayType*>(other);
  if (nOther == 0) {
    return false;
  }
  return elemType->IsEquivalentTo(nOther->getElemType());
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
