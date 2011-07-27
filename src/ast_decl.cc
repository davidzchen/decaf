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
    }

  if ((classEnv = env->addWithScope(id->getName(), this, S_CLASS)) == NULL)
    return false;

  for (int i = 0; i < members->NumElements(); i++)
    {
      members->Nth(i)->CheckDecls(classEnv);
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
  bool ret = true;

  if (extends)
    {
      if (!extends->Check(env))
        {
          ret = false;
        }
      else
        {
          Symbol *baseClass = env->find(extends->GetName(), S_CLASS);
          Assert(baseClass != NULL);

          classEnv->setSuper(baseClass->getEnv());
        }
    }

  vFunctions = new Hashtable<VFunction*>;

  for (int i = 0; i < implements->NumElements(); i++)
    {
      NamedType *interface = implements->Nth(i);
      if (!interface->Check(env))
        {
          ret = false;
          continue;
        }

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
              ret = false;
              ReportError::OverrideMismatch(fn);
            }
        }
    }

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
  Symbol *sym = NULL;
  VFunction *vf = NULL;

  Assert(env != NULL && classEnv != NULL);

  for (int i = 0; i < members->NumElements(); i++)
    {
      //printf("%d ", i);
      FnDecl *method = dynamic_cast<FnDecl*>(members->Nth(i));
      VarDecl *field = NULL;
      if (method != 0)
        {
          //printf("method %s\n", method->GetName());
          if ((sym = classEnv->findSuper(method->GetName(), S_FUNCTION)) != NULL)
            {
              FnDecl *otherMethod = dynamic_cast<FnDecl*>(sym->getNode());
              if (!method->TypeEqual(otherMethod))
                {
                  ReportError::OverrideMismatch(method);
                  ret = false;
                }
            }

          ret &= method->Check(classEnv);
        }
      else
        {
          field = dynamic_cast<VarDecl*>(members->Nth(i));
          Assert(field != 0);
          //printf("field %s\n", field->GetName());
          if ((sym = classEnv->findSuper(field->GetName(), S_VARIABLE)) != NULL)
            {
              ReportError::DeclConflict(field, dynamic_cast<Decl*>(sym->getNode()));
              ret = false;
            }
          ret &= field->Check(classEnv);
        }
    }

  Iterator<VFunction*> iter = vFunctions->GetIterator();
  Hashtable<NamedType*> *incompleteIntfs = new Hashtable<NamedType*>;
  while ((vf = iter.GetNextValue()) != NULL)
    {
      sym = classEnv->findInClass(vf->getPrototype()->GetName(), S_FUNCTION);
      if (sym == NULL)
        {
          incompleteIntfs->Enter(vf->getIntfType()->GetName(), vf->getIntfType(), false);
          continue;
        }
      FnDecl *method = dynamic_cast<FnDecl*>(sym->getNode());
      Assert(method != 0);

      if (method->TypeEqual(vf->getPrototype()))
        {
          vf->setImplemented(true);
        }
      else
        {
          incompleteIntfs->Enter(vf->getIntfType()->GetName(), vf->getIntfType(), false);
          ret = false;
        }
    }

  Iterator<NamedType*> iter2 = incompleteIntfs->GetIterator();
  NamedType *intfType = NULL;
  while ((intfType = iter2.GetNextValue()) != NULL)
    {
      ReportError::InterfaceNotImplemented(this, intfType);
    }

  return ret;
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
    {
      ret &= formals->Nth(i)->CheckDecls(fnEnv);
    }

  if (body)
    {
      if (!body->CheckDecls(fnEnv))
        return false;
    }

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
    {
      ret &= formals->Nth(i)->Check(env);
    }

  if (body)
    {
      ret &= body->Check(env);
    }

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
  implemented = false;
}
