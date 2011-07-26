/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */

#include <string.h>
#include "ast_type.h"
#include "ast_decl.h"
 
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

Type::Type(const char *n) 
{
  Assert(n);
  typeName = strdup(n);
}

void Type::PrintChildren(int indentLevel) 
{
  printf("%s", typeName);
}

/* Class: NamedType
 * ----------------
 * Implementation of NamedType class
 */

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) 
{
  Assert(i != NULL);
  (id = i)->SetParent(this);
} 

void NamedType::PrintChildren(int indentLevel) 
{
  id->Print(indentLevel+1);
}

bool NamedType::Check(SymTable *env)
{
  if (!env->find(id->getName()))
    return false;

  return true;
}

/* Class: ArrayType
 * ----------------
 * Implementation of ArrayType class
 */

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) 
{
  Assert(et != NULL);
  (elemType = et)->SetParent(this);
}

void ArrayType::PrintChildren(int indentLevel) 
{
  elemType->Print(indentLevel+1);
}

bool ArrayType::Check(SymTable *env)
{
  return elemType->Check(env);
}
