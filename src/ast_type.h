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

#include "ast.h"
#include "list.h"


class Type : public Node 
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    
    const char *GetPrintNameForNode() { return "Type"; }
    friend ostream& operator<<(ostream& out, Type *t)
    {
      t->PrintToStream(out); return out;
    }
    void PrintChildren(int indentLevel);
    virtual bool IsEquivalentTo(Type *other) { return this == other; }
    virtual void PrintToStream(ostream& out) { out << typeName; }
    virtual bool Check(SymTable *env) { return true; }
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);
    
    const char *GetPrintNameForNode() { return "NamedType"; }
    void PrintChildren(int indentLevel);
    void PrintToStream(ostream& out) { out << id; }
    char *GetName() { return id->getName(); }
    bool Check(SymTable *env);
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    
    const char *GetPrintNameForNode() { return "ArrayType"; }
    void PrintChildren(int indentLevel);
    void PrintToStream(ostream& out) { out << elemType << "[]"; }
    bool Check(SymTable *env);
};

 
#endif
