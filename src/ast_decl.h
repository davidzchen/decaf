/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement
 * semantic processing including detection of declaration conflicts
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "list.h"
#include "symtable.h"
#include "ast.h"
#include "ast_decl.h"
#include "ast_stmt.h"
#include "ast_type.h"

class Type;
class NamedType;
class Identifier;
class Stmt;
class VFunction;

class Decl : public Node 
{
  protected:
    Identifier *id;

  public:
    Decl(Identifier *name);
    friend ostream& operator<<(ostream& out, Decl *d)
    {
      return out << d->id;
    }
    void PrintToStream(ostream& out) { out << id; }
    virtual bool CheckDecls(SymTable *env) { return true; }
    virtual bool Check(SymTable *env) { return true; }
    char *GetName() { return id->getName(); }
};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    const char *GetPrintNameForNode()
    {
      return "VarDecl";
    }
    void PrintChildren(int indentLevel);
    bool CheckDecls(SymTable *env);
    bool Check(SymTable *env);
    Type *GetType() { return type; }
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;
    SymTable *classEnv;
    Hashtable<VFunction*> *vFunctions;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    const char *GetPrintNameForNode()
    {
      return "ClassDecl";
    }
    void PrintChildren(int indentLevel);
    bool CheckDecls(SymTable *env);
    bool Inherit(SymTable *env);
    bool Check(SymTable *env);
};



class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    SymTable *interfaceEnv;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    const char *GetPrintNameForNode()
    {
      return "InterfaceDecl";
    }
    void PrintChildren(int indentLevel);
    bool CheckDecls(SymTable *env);
    bool Check(SymTable *env);
    List<Decl*> *getMembers() { return members; }
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    SymTable *fnEnv;
    
  public:
    FnDecl(Identifier *name, Type *returnType,
           List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    const char *GetPrintNameForNode()
    {
      return "FnDecl";
    }
    void PrintChildren(int indentLevel);
    bool CheckDecls(SymTable *env);
    bool Check(SymTable *env);
    Type *GetReturnType() { return returnType; }
    List<VarDecl*> *GetFormals() { return formals; }
    bool TypeEqual(FnDecl *fn);
};

class VFunction
{
  protected:
    FnDecl *prototype;
    NamedType *intfType;
    bool implemented;

  public:
    VFunction(FnDecl *p, NamedType *type);
    FnDecl *getPrototype() { return prototype; }
    NamedType *getIntfType() { return intfType; }
    bool isImplemented() { return implemented; }
    void setImplemented(bool im) { implemented = im; }
};

#endif
