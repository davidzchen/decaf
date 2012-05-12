/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */

#include <config.h>
#include "errors.h"
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
        

/* Class: Decl 
 * -----------
 * Implementation of Decl class
 */

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) 
{
  Assert(n != NULL);
  (id = n)->SetParent(this); 
}

/* Class: VarDecl 
 * -------------- 
 * Implementation of VarDecl class
 */

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) 
{
  Assert(n != NULL && t != NULL);
  (type = t)->SetParent(this);
}
  
void VarDecl::PrintChildren(int indentLevel) 
{ 
  type->Print(indentLevel+1);
  id->Print(indentLevel+1);
}

bool VarDecl::CheckDecls(SymTable *env)
{
  Symbol *sym = NULL;

  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
      return false;
    }

  if (!env->add(id->getName(), this))
    {
      return false;
    }

  return true;
}

bool VarDecl::Check(SymTable *env)
{
  bool ret = type->Check(env);
  Symbol *sym;

  // If type is invalid, set type as error
  if (!ret)
    {
      ReportError::IdentifierNotDeclared(type->GetIdent(), LookingForType);
      type = Type::errorType;
    }

  return ret;
}

void VarDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env)
{
  Location *loc = NULL;
  Symbol *sym = NULL;

  loc = falloc->Alloc(id->getName(), 4);

  sym = env->find(id->getName(), S_VARIABLE);
  sym->setLocation(loc);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "Var Decl\t%s @ %d:%d\n", id->getName(), loc->GetSegment(), loc->GetOffset());
#endif
}

/* Class: ClosureDecl
 * ----------------
 * Implementation of ClosureDecl class
 */

ClosureDecl::ClosureDecl(Identifier *n, Type *t, List<VarDecl*> *d)
  : Decl(n)
{
  Assert(n != NULL && t != NULL && d != NULL);
  (type = t)->SetParent(this);
  (formals = d)->SetParentAll(this);
}

void ClosureDecl::PrintChildren(int indentLevel)
{
  returnType->Print(indentLevel + 1, "(return type) ");
  id->Print(indentLevel + 1);
  formals->PrintAll(indentLevel + 1, "(formals) ");
}

bool ClosureDecl::CheckDecls(SymTable *env)
{
  return true;
}

bool ClosureDecl::Check(SymTable *env)
{
  return true;
}

void ClosureDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                       SymTable *env)
{

}

/* Class: ClassDecl
 * ----------------
 * Implementation of ClassDecl class
 */

ClassDecl::ClassDecl(Identifier *n, 
		     NamedType *ex, 
		     List<NamedType*> *imp, 
		     List<Decl*> *m)
  : Decl(n)
{
  // extends can be NULL, impl & mem may be empty lists but cannot be NULL
  Assert(n != NULL && imp != NULL && m != NULL);     
  extends = ex;
  if (extends) 
    { 
      extends->SetParent(this);
    }
  (implements = imp)->SetParentAll(this);
  (members = m)->SetParentAll(this);
  classEnv = NULL;
  vFunctions = NULL;

  parent = NULL;
  classFalloc = NULL;
  vTable = NULL;
  fields = NULL;
  numFields = 0;
}

void ClassDecl::PrintChildren(int indentLevel) 
{
  id->Print(indentLevel+1);
  if (extends) 
    {
      extends->Print(indentLevel + 1, "(extends) ");
    }
  implements->PrintAll(indentLevel + 1, "(implements) ");
  members->PrintAll(indentLevel + 1);
}

bool ClassDecl::CheckDecls(SymTable *env)
{
  Symbol *sym = NULL;
  
  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
    }

  if ((classEnv = env->addWithScope(id->getName(), this, S_CLASS)) == NULL)
    return false;

  classEnv->setThis(classEnv);

  for (int i = 0; i < members->NumElements(); i++)
    {
      members->Nth(i)->CheckDecls(classEnv);
    }
 
  return true;
}

bool ClassDecl::ImplementsInterface(char *name)
{
  for (int i = 0; i < implements->NumElements(); i++)
    {
      if (strcmp(name, implements->Nth(i)->GetName()) == 0)
        return true;
    }

  return false;
}

/* Checks if the class extends another class. If it does, then set the class's
 * symbol table's super pointer to the symbol table of the super class. Then,
 * for each interface the class implements, iterate through each of the
 * interface's member functions and add them to the virtual function hash
 * table. If a vfunction in the table has the same name, then check whether
 * the type signatures are the same. If they are the same, then skip. Otherwise,
 * print error and return.
 */
bool ClassDecl::Inherit(SymTable *env)
{
  bool ret = true;

  if (extends)
    {
      Symbol *baseClass = NULL;
      if ((baseClass = env->find(extends->GetName(), S_CLASS)) != NULL)
        {
          classEnv->setSuper(baseClass->getEnv());
          parent = dynamic_cast<ClassDecl*>(baseClass->getNode());
          Assert(parent != 0);
        }
    }

  vFunctions = new Hashtable<VFunction*>;
  for (int i = 0; i < implements->NumElements(); i++)
    {
      NamedType *interface = implements->Nth(i);
      Symbol *intfSym = NULL;

      if ((intfSym = env->find(interface->GetName(), S_INTERFACE)) == NULL)
        continue;

      InterfaceDecl *intfDecl = dynamic_cast<InterfaceDecl*>(intfSym->getNode());
      Assert(intfDecl != 0);

      List<Decl*> *intfMembers = intfDecl->getMembers();
      for (int j = 0; j < intfMembers->NumElements(); j++)
        {
          FnDecl *fn = dynamic_cast<FnDecl*>(intfMembers->Nth(j));
          Assert(fn != 0);

          VFunction *vf = NULL;
          if ((vf = vFunctions->Lookup(fn->GetName())) == NULL)
            {
              vFunctions->Enter(fn->GetName(), new VFunction(fn, implements->Nth(i)));
              continue;
            }

          if (!fn->TypeEqual(vf->getPrototype()))
            {
              // XXX: what if two interfaces have the same function with
              //      different type signatures?
              ret = false;
              ReportError::OverrideMismatch(fn);
            }
        }
    }

  return ret;
}

bool ClassDecl::CheckAgainstParents(SymTable *env)
{
  bool ret = true;
  Symbol *sym = NULL;

  // Check that parent exists
  if (extends)
    {
      if ((sym = env->find(extends->GetName())) == NULL)
        {
          ReportError::IdentifierNotDeclared(extends->GetIdent(), LookingForClass);
          ret = false;
        }
    }

  // Check each method and variable against parent fields for override
  // errors
  for (int i = 0; i < members->NumElements(); i++)
    {
      FnDecl *method = dynamic_cast<FnDecl*>(members->Nth(i));
      VarDecl *field = NULL;

      if (method != 0)
        {
          if ((sym = classEnv->findSuper(method->GetName(), S_FUNCTION)) != NULL)
            {
              FnDecl *otherMethod = dynamic_cast<FnDecl*>(sym->getNode());
              Assert(otherMethod != 0);
              if (!method->TypeEqual(otherMethod))
                {
                  ReportError::OverrideMismatch(method);
                  ret = false;
                }
            }
        }
      else
        {
          field = dynamic_cast<VarDecl*>(members->Nth(i));
          Assert(field != 0);
          if ((sym = classEnv->findSuper(field->GetName(), S_VARIABLE)) != NULL)
            {
              ReportError::DeclConflict(field, dynamic_cast<Decl*>(sym->getNode()));
              ret = false;
            }
        }
    }

  return ret;
}

bool ClassDecl::CheckAgainstInterfaces(SymTable *env)
{
  bool ret = true;
  VFunction *vf = NULL;
  Iterator<VFunction*> iter = vFunctions->GetIterator();
  Hashtable<NamedType*> *incompleteIntfs = new Hashtable<NamedType*>;
  Symbol *sym = NULL;

  // Check that all interfaces implemented exists
  for (int i = 0; i < implements->NumElements(); i++)
    {
      NamedType *intf = implements->Nth(i);
      if ((sym = env->find(intf->GetName())) == NULL)
        {
          ReportError::IdentifierNotDeclared(intf->GetIdent(), LookingForInterface);
          ret = false;
        }
    }

  // Check each interface's methods have been implemented with correct type
  // signature. Otherwise, give OverrideMismatch error
  while ((vf = iter.GetNextValue()) != NULL)
    {
      sym = classEnv->findInClass(vf->getPrototype()->GetName(), S_FUNCTION);
      if (sym == NULL)
        {
          incompleteIntfs->Enter(vf->getIntfType()->GetName(), vf->getIntfType(), false);
          ret = false;
          continue;
        }
      FnDecl *method = dynamic_cast<FnDecl*>(sym->getNode());
      Assert(method != 0);

      if (!method->TypeEqual(vf->getPrototype()))
        {
          ReportError::OverrideMismatch(method);
          ret = false;
        }
    }

  // Report interfaces that have not been implemented
  Iterator<NamedType*> iter2 = incompleteIntfs->GetIterator();
  NamedType *intfType = NULL;
  while ((intfType = iter2.GetNextValue()) != NULL)
    ReportError::InterfaceNotImplemented(this, intfType);

  delete incompleteIntfs;

  return ret;
}

/* Preconditions:
 *   1. Class hierarchy is set up.
 *   2. There are no conflicts among interfaces being implemented
 *   3. All the functions from interfaces being implemented have been added to
 *      the vFunctions table.
 *
 * pp3-checkpoint: for scope checking,
 */
bool ClassDecl::Check(SymTable *env)
{
  bool ret = true;

  Assert(env != NULL && classEnv != NULL);

  ret &= CheckAgainstParents(env);
  ret &= CheckAgainstInterfaces(env);

  // Check all members
  for (int i = 0; i < members->NumElements(); i++)
    ret &= members->Nth(i)->Check(env);

  return ret;
}

void ClassDecl::EmitSetup(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env)
{
  // Because we're doing recursive walks up the class hierarchy tree, this
  // method for this object may be called by a child. If Emit has already been
  // called, just return.

  if (classFalloc != NULL)
    return;


#ifdef __DEBUG_TAC
  PrintDebug("tac", "ClassDecl %s\n", id->getName());
#endif

  // Recursively call Emit on the parent class to make sure that the vTable and
  // fields list we are inheriting are properly set up in case the parent's
  // ClassDecl comes after this one. If we are inheriting, copy the parent's
  // vtable, field list, and FrameAllocator. Because any new fields would be
  // placed after all inherited methods, we can begin at the offset set by
  // the parent's FrameAllocator

  classLabel = codegen->NewClassLabel(id->getName());

  vTable = new List<FnDecl*>;
  fields = new List<VarDecl*>;

  if (extends)
    {
      Assert(parent != NULL);

      // Note: parent will ignore falloc and env parameters and use its own
      parent->EmitSetup(falloc, codegen, env);

      List<FnDecl*> *parentVTable = parent->GetVTable();
      List<VarDecl*> *parentFields = parent->GetFields();

      for (int i = 0; i < parentVTable->NumElements(); i++)
        vTable->Append(parentVTable->Nth(i));

      for (int i = 0; i < parentFields->NumElements(); i++)
        fields->Append(parentFields->Nth(i));

#ifdef __DEBUG_TAC
      PrintDebug("tac", "Before: vtable %d fields %d\n", vTable->NumElements(), fields->NumElements());
#endif

      classFalloc = new FrameAllocator(parent->GetFalloc());
    }
  else
    {
      classFalloc = new FrameAllocator(classRelative, FRAME_UP);
    }

  // Merge class's methods and fields with vTable and fields inherited from
  // parent or empty vTable and field lists if class is a base class. For each
  // field or method, call the field or method's Emit method to set up the
  // field location (relative to base of class) and
  //
  // XXX Okay, this will be O(n^2), but right now we just need to get this to
  //     work. Optimize the algorithm later.

  FnDecl *method = NULL;
  VarDecl *field = NULL;

  methodsToEmit = new List<FnDecl*>;
  for (int i = 0; i < members->NumElements(); i++)
    {
      method = dynamic_cast<FnDecl*>(members->Nth(i));
      if (method != 0)
        {
          int j;
          for (j = 0; j < vTable->NumElements(); j++)
            {
              if (method->PrototypeEqual(vTable->Nth(j)))
                {
                  vTable->RemoveAt(j);
                  vTable->InsertAt(method, j);

                  method->SetMethodLabel(classLabel);
                  method->SetMethodOffset(j);
                  methodsToEmit->Append(method);

                  break;
                }
            }

          if (j >= vTable->NumElements())
            {
              // Method does not override any parent methods
              vTable->Append(method);

              method->SetMethodLabel(classLabel);
              method->SetMethodOffset(j);
              methodsToEmit->Append(method);

            }
        }
      else
        {
          field = dynamic_cast<VarDecl*>(members->Nth(i));
          Assert(field != 0);

          // We might not need the insertion for loop because semantically
          // correct code will not be overriding parent fields.
          fields->Append(field);

          field->Emit(classFalloc, codegen, classEnv);
        }
    }
}

void ClassDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env)
{
  for (int i = 0; i < methodsToEmit->NumElements(); i++)
    {
      methodsToEmit->Nth(i)->EmitMethod(this, classFalloc, codegen, classEnv);
    }

  // Emit vtable. We have already emitted fields and methods
#ifdef __DEBUG_TAC
  PrintDebug("tac", "After: vtable %d fields %d\n",
             vTable->NumElements(), fields->NumElements());
#endif

  numFields = fields->NumElements();

  List<const char*> *methodLabels = new List<const char*>;
  for (int i = 0; i < vTable->NumElements(); i++)
    methodLabels->Append(vTable->Nth(i)->GetMethodLabel());

  codegen->GenVTable(classLabel, methodLabels);
}


/* Class: InterfaceDecl
 * --------------------
 * Implementation of class InterfaceDecl
 */

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) 
{
  Assert(n != NULL && m != NULL);
  (members = m)->SetParentAll(this);
}

void InterfaceDecl::PrintChildren(int indentLevel) 
{
  id->Print(indentLevel + 1);
  members->PrintAll(indentLevel + 1);
}

bool InterfaceDecl::CheckDecls(SymTable *env)
{
  Symbol *sym = NULL;
  bool ret = true;

  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
      ret = false;
    }

  if ((interfaceEnv = env->addWithScope(id->getName(), this, S_INTERFACE)) == false)
    return false;

  for (int i = 0; i < members->NumElements(); i++)
    {
      ret &= members->Nth(i)->CheckDecls(interfaceEnv);
    }

  return ret;
}

/* pp3-checkpoint: Scope checking
 *   1. Check each FnDecl
 */
bool InterfaceDecl::Check(SymTable *env)
{
  bool ret = true;

  for (int i = 0; i < members->NumElements(); i++)
    {
      ret &= members->Nth(i)->Check(env);
    }

  return ret;
}

void InterfaceDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                         SymTable *env)
{
  // XXX: Interfaces not implemented
  Failure("Interfaces not implemented");
}

/* Class: FnDecl
 * -------------
 * Implementation of class FnDecl
 */
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) 
{
  Assert(n != NULL && r!= NULL && d != NULL);
  (returnType = r)->SetParent(this);
  (formals = d)->SetParentAll(this);
  body = NULL;
  fnEnv = NULL;

  paramFalloc = NULL;
  bodyFalloc = NULL;
  methodLabel = NULL;
  functionLabel = NULL;
  methodOffset = 0;
}

void FnDecl::SetFunctionBody(Stmt *b) 
{
  (body = b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) 
{
  returnType->Print(indentLevel + 1, "(return type) ");
  id->Print(indentLevel + 1);
  formals->PrintAll(indentLevel + 1, "(formals) ");

  if (body) 
    {
      body->Print(indentLevel + 1, "(body) ");
    }
}

bool FnDecl::CheckDecls(SymTable *env)
{
  Symbol *sym;
  bool ret = true;

  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ret = false;
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
    }

  if ((fnEnv = env->addWithScope(id->getName(), this, S_FUNCTION)) == false)
    return false;

  for (int i = 0; i < formals->NumElements(); i++)
    ret &= formals->Nth(i)->CheckDecls(fnEnv);

  if (body)
    if (!body->CheckDecls(fnEnv))
      return false;

  return ret;
}

/* pp3-checkpoint: scope checking
 *   1. Check return type
 *   2. Check formals
 *   3. If body, call body's check
 */
bool FnDecl::Check(SymTable *env)
{
  bool ret = true;

  ret &= returnType->Check(env);

  for (int i = 0; i < formals->NumElements(); i++)
    ret &= formals->Nth(i)->Check(env);


  if (body)
    ret &= body->Check(env);

  return ret;
}

bool FnDecl::TypeEqual(FnDecl *fn)
{
  if (!returnType->IsEquivalentTo(fn->GetReturnType()))
    return false;

  List<VarDecl*> *otherFormals = fn->GetFormals();

  if (formals->NumElements() != otherFormals->NumElements())
    return false;

  for (int i = 0; i < otherFormals->NumElements(); i++)
    if (!formals->Nth(i)->GetType()->IsEquivalentTo(otherFormals->Nth(i)->GetType()))
      return false;

  return true;
}

bool FnDecl::PrototypeEqual(FnDecl *fn)
{
  if (!TypeEqual(fn))
    return false;

  if (strcmp(id->getName(), fn->GetName()) == 0)
    return true;
  else
    return false;
}

void FnDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env)
{
  BeginFunc *beginFn;
  Symbol *sym = NULL;

  paramFalloc = new FrameAllocator(fpRelative, FRAME_UP);
  bodyFalloc  = new FrameAllocator(fpRelative, FRAME_DOWN);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "FnDecl %s\n", id->getName());
#endif

  functionLabel = codegen->NewFunctionLabel(id->getName());
  codegen->GenLabel(functionLabel);

  beginFn = codegen->GenBeginFunc();

  for (int i = 0; i < formals->NumElements(); i++)
    {
      formals->Nth(i)->Emit(paramFalloc, codegen, fnEnv);
    }

  body->Emit(bodyFalloc, codegen, fnEnv);

  beginFn->SetFrameSize(bodyFalloc->GetSize());
  codegen->GenEndFunc();
}

void FnDecl::EmitMethod(ClassDecl *classDecl, FrameAllocator *falloc,
                        CodeGenerator *codegen, SymTable *env)
{
  BeginFunc *beginFn;

  paramFalloc = new FrameAllocator(fpRelative, FRAME_UP);
  bodyFalloc  = new FrameAllocator(fpRelative, FRAME_DOWN);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "FnDecl Method %s::%s\n", classDecl->GetName(), id->getName());
#endif

  codegen->GenLabel(methodLabel);

  beginFn = codegen->GenBeginFunc();

  // Simulate an implicit first "this" parameter
  char *thisName = strdup("this");
  Location *thisParam = paramFalloc->Alloc(thisName, 4);
  fnEnv->add(thisName, NULL, thisParam);

  for (int i = 0; i < formals->NumElements(); i++)
    {
      formals->Nth(i)->Emit(paramFalloc, codegen, fnEnv);
    }

  body->Emit(bodyFalloc, codegen, fnEnv);

  beginFn->SetFrameSize(bodyFalloc->GetSize());
  codegen->GenEndFunc();
}

void FnDecl::SetMethodLabel(char *classLabel)
{
  int len = strlen(classLabel) + strlen(id->getName()) + 2;

  methodLabel = (char *) malloc(len);
  if (methodLabel == NULL)
    Failure("FnDecl::SetMethodLabel(): Malloc out of memory");

  sprintf(methodLabel, "%s.%s", classLabel, id->getName());
  methodLabel[len - 1] = '\0';
}


/* Class: VFunction
 * ----------------
 * Implementation for VFunction class
 */

VFunction::VFunction(FnDecl *p, NamedType *type)
{
  prototype = p;
  intfType = type;
  implemented = false;
}
