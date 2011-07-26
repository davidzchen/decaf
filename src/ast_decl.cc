/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */

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
  return type->Check(env);
}


/* Class: ClassDecl
 * ----------------
 * Implementation of ClassDecl class
 */

ClassDecl::ClassDecl(Identifier *n, 
		     NamedType *ex, 
		     List<NamedType*> *imp, 
		     List<Decl*> *m) : Decl(n) 
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
      return false;
    }

  if ((classEnv = env->addWithScope(id->getName(), this, S_CLASS)) == NULL)
    return false;

  for (int i = 0; i < members->NumElements(); i++)
    {
      if (!members->Nth(i)->CheckDecls(classEnv))
	return false;
    }
 
  return true;
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
  if (extends)
    {
      if (!extends->Check(env))
        return false;

      Symbol *baseClass = env->find(extends->GetName(), S_CLASS);
      Assert(baseClass != NULL);

      classEnv->setSuper(baseClass->getEnv());
    }

  vFunctions = new Hashtable<VFunction*>;

  for (int i = 0; i < implements->NumElements(); i++)
    {
      NamedType *interface = implements->Nth(i);
      if (!interface->Check(env))
        return false;

      Symbol *intfSym = env->find(interface->GetName(), S_INTERFACE);
      Assert(intfSym != NULL);

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
              ReportError::OverrideMismatch(fn);
              return false;
            }
        }
    }

  return true;
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

  /* FIXME: implement (2) */

  return true;
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

  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
      return false;
    }

  if ((interfaceEnv = env->addWithScope(id->getName(), this, S_INTERFACE)) == false)
    return false;

  for (int i = 0; i < members->NumElements(); i++)
    {
      if (!members->Nth(i)->CheckDecls(interfaceEnv))
	return false;
    }

  return true;
}

/* pp3-checkpoint: Scope checking
 *   1. Check each FnDecl
 */
bool InterfaceDecl::Check(SymTable *env)
{
  for (int i = 0; i < members->NumElements(); i++)
    {
      if (!members->Nth(i)->Check(env))
        return false;
    }

  return true;
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

  if ((sym = env->findLocal(id->getName())) != NULL)
    {
      ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
      return false;
    }

  for (int i = 0; i < formals->NumElements(); i++)
    {
      if (!formals->Nth(i)->CheckDecls(env))
	return false;
    }

  if (body)
    {
      if (!body->CheckDecls(env))
        return false;
    }

  return true;
}

bool FnDecl::Check(SymTable *env)
{
  /* pp3-checkpoint: scope checking
   *   1. Check return type
   *   2. Check formals
   *   3. If body, call body's check
   */

  if (!returnType->Check(env))
    return false;

  for (int i = 0; i < formals->NumElements(); i++)
    {
      if (!formals->Nth(i)->Check(env))
        return false;
    }

  if (body)
    {
      if (!body->Check(env))
        return false;
    }

  return true;
}

bool FnDecl::TypeEqual(FnDecl *fn)
{
  if (!returnType->IsEquivalentTo(fn->GetReturnType()))
    return false;

  List<VarDecl*> *otherFormals = fn->GetFormals();

  if (formals->NumElements() != otherFormals->NumElements())
    return false;

  for (int i = 0; i < otherFormals->NumElements(); i++)
    {
      if (!formals->Nth(i)->GetType()->IsEquivalentTo(otherFormals->Nth(i)->GetType()))
        return false;
    }

  return true;
}

/* Class: VFunction
 * ----------------
 * Implementation for VFunction class
 */

VFunction::VFunction(FnDecl *p, NamedType *type)
{
  prototype = p;
  intfType = type;
}
