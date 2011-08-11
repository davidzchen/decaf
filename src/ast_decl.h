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

#include "ast.h"
#include "ast_decl.h"
#include "ast_stmt.h"
#include "ast_type.h"

class Type;
class NamedType;
class Identifier;
class Stmt;
class VFunction;
class FnDecl;

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
    virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                      SymTable *env) { }
    virtual Type *GetType() { return NULL; }
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
    void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
    Type *GetType() { return type; }
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;                 // Fields and methods
    NamedType *extends;                   // Parent class, if any
    List<NamedType*> *implements;         // List of interfaces implemented

    // Set and used for semantic checking
    SymTable *classEnv;                   // Symbol table for class
    Hashtable<VFunction*> *vFunctions;    // Hash table of interface methods

    // Pointer to ClassDecl for parent class, NULL if no parent class
    // Set during semantic checking, used during IR generation
    ClassDecl *parent;

    // Set and used for IR Generation
    FrameAllocator *classFalloc;          // Frame allocator for class variables
    List<FnDecl*> *vTable;                 // List of methods for vtable gen
    List<VarDecl*> *fields;                // List of fields
    int numFields;
    char *classLabel;

  private:
    bool CheckAgainstParents(SymTable *env);
    bool CheckAgainstInterfaces(SymTable *env);

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    const char *GetPrintNameForNode()
    {
      return "ClassDecl";
    }
    Identifier *GetIdent() { return id; }
    List<FnDecl*> *GetVTable() { return vTable; }
    List<VarDecl*> *GetFields() { return fields; }
    FrameAllocator *GetFalloc() { return classFalloc; }

    void PrintChildren(int indentLevel);
    bool CheckDecls(SymTable *env);
    bool Inherit(SymTable *env);
    bool ImplementsInterface(char *name);
    void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
    bool Check(SymTable *env);
    int NumFields() { return numFields; }
    char *GetClassLabel() { return classLabel; }
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
    void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
    List<Decl*> *getMembers() { return members; }
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    SymTable *fnEnv;

    FrameAllocator *paramFalloc;
    FrameAllocator *bodyFalloc;
    char *methodLabel;
    char *functionLabel;
    int methodOffset;
    
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
    void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
    void EmitMethod(ClassDecl *classDecl, FrameAllocator *falloc,
                    CodeGenerator *codegen, SymTable *env);
    Type *GetReturnType() { return returnType; }
    Type *GetType() { return returnType; }
    List<VarDecl*> *GetFormals() { return formals; }
    bool PrototypeEqual(FnDecl *fn);
    bool TypeEqual(FnDecl *fn);

    const char *GetMethodLabel() { return methodLabel; }
    void SetMethodLabel(char *classLabel);
    const char *GetFunctionLabel() { return functionLabel; }
    bool IsMethod() { return (methodLabel != NULL); }
    int GetMethodOffset() { return methodOffset; }
    void SetMethodOffset(int off) { methodOffset = off; }
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
