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

#ifndef DCC_AST_DECL_H__
#define DCC_AST_DECL_H__

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

class Decl : public Node {
 public:
  Decl(Identifier *name);
  friend ostream& operator<<(ostream& out, Decl *d) {
    return out << d->id_;
  }
  void PrintToStream(ostream& out) { out << id_; }
  virtual bool CheckDecls(SymTable *env) { return true; }
  virtual bool Check(SymTable *env) { return true; }
  virtual void Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                    SymTable *env) { }
  virtual Type* GetType() { return NULL; }
  char *GetName() { return id_->name(); }

 protected:
  Identifier* id_;
};

class VarDecl : public Decl { 
 public:
  VarDecl(Identifier* name, Type* type);
  const char* GetPrintNameForNode() {
    return "VarDecl";
  }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable* env);
  bool Check(SymTable* env);
  void Emit(FrameAllocator* falloc, CodeGenerator* codegen, SymTable* env);
  Type* GetType() { return type_; }
 
 protected:
  Type* type_;
};

class ClassDecl : public Decl {
 public:
  ClassDecl(Identifier* name, NamedType* extends, 
            List<NamedType*>* implements, List<Decl*>* members);
  const char* GetPrintNameForNode() {
    return "ClassDecl";
  }
  Identifier* GetIdent() { return id_; }
  List<FnDecl*>* GetVTable() { return v_table_; }
  List<VarDecl*>* GetFields() { return fields_; }
  FrameAllocator* GetFalloc() { return class_falloc_; }

  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable* env);
  bool Inherit(SymTable* env);
  bool ImplementsInterface(char* name);
  bool Check(SymTable* env);

  void EmitSetup(FrameAllocator* falloc, CodeGenerator* codegen,
                 SymTable* env);
  void Emit(FrameAllocator* falloc, CodeGenerator* codegen, SymTable* env);

  int NumFields() { return num_fields_; }
  char* GetClassLabel() { return class_label_; }
 
 private:
  bool CheckAgainstParents(SymTable* env);
  bool CheckAgainstInterfaces(SymTable* env);
 
 protected:
  // Fields and methods
  List<Decl*>* members_;
  // Parent class, if any
  NamedType* extends_;
  // List of interfaces implemented
  List<NamedType*>* implements_;

  // Set and used for semantic checking
  
  // Symbol table for class
  SymTable* class_env_;
  // Hash table of interface methods
  Hashtable<VFunction*>* v_functions_;

  // Pointer to ClassDecl for parent class, NULL if no parent class
  // Set during semantic checking, used during IR generation
  ClassDecl* parent_;

  // Set and used for IR Generation
  
  // Frame allocator for class variables
  FrameAllocator* class_falloc_;
  // List of methods for vtable gen
  List<FnDecl*>* v_table_;
  // List of fields
  List<VarDecl*>* fields_;
  int num_fields_;
  char *class_label_;
  List<FnDecl*> *methods_to_emit_;
};

class InterfaceDecl : public Decl { 
 public:
  InterfaceDecl(Identifier *name, List<Decl*> *members);
  const char *GetPrintNameForNode() {
    return "InterfaceDecl";
  }
  void PrintChildren(int indentLevel);
  bool CheckDecls(SymTable *env);
  bool Check(SymTable *env);
  void Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env);
  List<Decl*> *getMembers() { return members_; }
 
 protected:
  List<Decl*> *members_;
  SymTable *interfaceEnv;
};

class FnDecl : public Decl { 
 public:
  FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
  void SetFunctionBody(Stmt *b);
  const char *GetPrintNameForNode() {
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
};

class VFunction {
 public:
  VFunction(FnDecl *p, NamedType *type);
  FnDecl *getPrototype() { return prototype; }
  NamedType *getIntfType() { return intfType; }
  bool isImplemented() { return implemented; }
  void setImplemented(bool im) { implemented = im; }

 protected:
  FnDecl *prototype;
  NamedType *intfType;
  bool implemented;
};

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif /* DCC_AST_DECL_H__ */
