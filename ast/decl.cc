/// @file ast_decl.cc
/// @brief Implementation of Decl node classes.

#include "decaf/errors.h"
#include "ast/decl.h"
#include "ast/type.h"
#include "ast/stmt.h"

/* Class: Decl
 * -----------
 * Implementation of Decl class
 */

Decl::Decl(Identifier *n) : Node(*n->location()) {
  Assert(n != NULL);
  (id_ = n)->set_parent(this);
}

/* Class: VarDecl
 * --------------
 * Implementation of VarDecl class
 */

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
  Assert(n != NULL && t != NULL);
  (type_ = t)->set_parent(this);
}

void VarDecl::PrintChildren(int indent_level) {
  type_->Print(indent_level + 1);
  id_->Print(indent_level + 1);
}

bool VarDecl::CheckDecls(SymTable *env) {
  Symbol *sym = NULL;
  if ((sym = env->findLocal(id_->name())) != NULL) {
    ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
    return false;
  }
  if (!env->add(id_->name(), this)) {
    return false;
  }
  return true;
}

bool VarDecl::Check(SymTable *env) {
  bool ret = type_->Check(env);
  // If type is invalid, set type as error
  if (!ret) {
    ReportError::IdentifierNotDeclared(type_->GetIdent(), kLookingForType);
    type_ = Type::errorType;
  }
  return ret;
}

void VarDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
    SymTable *env) {
  Location* loc = falloc->Alloc(id_->name(), 4);
  Symbol* sym = env->find(id_->name(), S_VARIABLE);
  sym->setLocation(loc);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "Var Decl\t%s @ %d:%d\n", id_->name(), loc->GetSegment(),
      loc->GetOffset());
#endif
}

/* Class: ClassDecl
 * ----------------
 * Implementation of ClassDecl class
 */

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp,
    List<Decl*> *m) : Decl(n) {
  // extends can be NULL, impl & mem may be empty lists but cannot be NULL
  Assert(n != NULL && imp != NULL && m != NULL);
  extends_ = ex;
  if (extends_ != NULL) {
    extends_->set_parent(this);
  }

  (implements_ = imp)->SetParentAll(this);
  (members_ = m)->SetParentAll(this);

  class_env_ = NULL;
  v_functions_ = NULL;
  parent_ = NULL;
  class_falloc_ = NULL;
  v_table_ = NULL;
  fields_ = NULL;
  num_fields_ = 0;
}

void ClassDecl::PrintChildren(int indent_level) {
  id_->Print(indent_level+1);
  if (extends_) {
    extends_->Print(indent_level + 1, "(extends) ");
  }
  implements_->PrintAll(indent_level + 1, "(implements) ");
  members_->PrintAll(indent_level + 1);
}

bool ClassDecl::CheckDecls(SymTable *env) {
  Symbol *sym = NULL;
  if ((sym = env->findLocal(id_->name())) != NULL) {
    ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
  }

  if ((class_env_ = env->addWithScope(id_->name(), this, S_CLASS)) == NULL) {
    return false;
  }

  class_env_->setThis(class_env_);
  for (int i = 0; i < members_->NumElements(); ++i) {
    members_->Nth(i)->CheckDecls(class_env_);
  }

  return true;
}

bool ClassDecl::ImplementsInterface(char *name) {
  for (int i = 0; i < implements_->NumElements(); ++i) {
    if (strcmp(name, implements_->Nth(i)->GetName()) == 0) {
      return true;
    }
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
bool ClassDecl::Inherit(SymTable *env) {
  bool ret = true;
  if (extends_) {
    Symbol *base_class = NULL;
    if ((base_class = env->find(extends_->GetName(), S_CLASS)) != NULL) {
      class_env_->setSuper(base_class->getEnv());
      parent_ = dynamic_cast<ClassDecl*>(base_class->getNode());
      Assert(parent_ != 0);
    }
  }

  v_functions_ = new Hashtable<VFunction*>;
  for (int i = 0; i < implements_->NumElements(); ++i) {
    NamedType *interface = implements_->Nth(i);
    Symbol *intf_sym = NULL;
    if ((intf_sym = env->find(interface->GetName(), S_INTERFACE)) == NULL) {
      continue;
    }
    InterfaceDecl *intfDecl = dynamic_cast<InterfaceDecl*>(intf_sym->getNode());
    Assert(intfDecl != 0);
    List<Decl*> *intf_members = intfDecl->getMembers();
    for (int j = 0; j < intf_members->NumElements(); ++j) {
      FnDecl *fn = dynamic_cast<FnDecl*>(intf_members->Nth(j));
      Assert(fn != 0);
      VFunction *vf = NULL;
      if ((vf = v_functions_->Lookup(fn->GetName())) == NULL) {
        v_functions_->Enter(fn->GetName(), new VFunction(fn, implements_->Nth(i)));
        continue;
      }

      if (!fn->TypeEqual(vf->getPrototype())) {
        // XXX: what if two interfaces have the same function with
        //      different type signatures?
        ret = false;
        ReportError::OverrideMismatch(fn);
      }
    }
  }

  return ret;
}

bool ClassDecl::CheckAgainstParents(SymTable *env) {
  bool ret = true;
  Symbol *sym = NULL;

  // Check that parent exists
  if (extends_) {
    if ((sym = env->find(extends_->GetName())) == NULL) {
      ReportError::IdentifierNotDeclared(extends_->GetIdent(), kLookingForClass);
      ret = false;
    }
  }

  // Check each method and variable against parent fields for override
  // errors
  for (int i = 0; i < members_->NumElements(); ++i) {
    FnDecl *method = dynamic_cast<FnDecl*>(members_->Nth(i));
    VarDecl *field = NULL;
    if (method != 0) {
      if ((sym = class_env_->findSuper(method->GetName(), S_FUNCTION)) != NULL) {
        FnDecl *otherMethod = dynamic_cast<FnDecl*>(sym->getNode());
        Assert(otherMethod != 0);
        if (!method->TypeEqual(otherMethod)) {
          ReportError::OverrideMismatch(method);
          ret = false;
        }
      }
    } else {
      field = dynamic_cast<VarDecl*>(members_->Nth(i));
      Assert(field != 0);
      if ((sym = class_env_->findSuper(field->GetName(), S_VARIABLE)) != NULL) {
        ReportError::DeclConflict(field, dynamic_cast<Decl*>(sym->getNode()));
        ret = false;
      }
    }
  }

  return ret;
}

bool ClassDecl::CheckAgainstInterfaces(SymTable *env) {
  bool ret = true;
  VFunction *vf = NULL;
  Iterator<VFunction*> iter = v_functions_->GetIterator();
  Hashtable<NamedType*> *incompleteIntfs = new Hashtable<NamedType*>;
  Symbol *sym = NULL;

  // Check that all interfaces implemented exists
  for (int i = 0; i < implements_->NumElements(); ++i) {
    NamedType *intf = implements_->Nth(i);
    if ((sym = env->find(intf->GetName())) == NULL) {
      ReportError::IdentifierNotDeclared(intf->GetIdent(), kLookingForInterface);
      ret = false;
    }
  }

  // Check each interface's methods have been implemented with correct type
  // signature. Otherwise, give OverrideMismatch error
  while ((vf = iter.GetNextValue()) != NULL) {
    sym = class_env_->findInClass(vf->getPrototype()->GetName(), S_FUNCTION);
    if (sym == NULL) {
      incompleteIntfs->Enter(vf->getIntfType()->GetName(), vf->getIntfType(), false);
      ret = false;
      continue;
    }
    FnDecl* method = dynamic_cast<FnDecl*>(sym->getNode());
    Assert(method != 0);
    if (!method->TypeEqual(vf->getPrototype())) {
      ReportError::OverrideMismatch(method);
      ret = false;
    }
  }

  // Report interfaces that have not been implemented
  Iterator<NamedType*> iter2 = incompleteIntfs->GetIterator();
  NamedType *intf_type = NULL;
  while ((intf_type = iter2.GetNextValue()) != NULL) {
    ReportError::InterfaceNotImplemented(this, intf_type);
  }

  delete incompleteIntfs;
  return ret;
}

/* Preconditions:
 *   1. Class hierarchy is set up.
 *   2. There are no conflicts among interfaces being implemented
 *   3. All the functions from interfaces being implemented have been added to
 *      the v_functions_ table.
 *
 * pp3-checkpoint: for scope checking,
 */
bool ClassDecl::Check(SymTable *env) {
  bool ret = true;
  Assert(env != NULL && class_env_ != NULL);
  ret &= CheckAgainstParents(env);
  ret &= CheckAgainstInterfaces(env);
  // Check all members_
  for (int i = 0; i < members_->NumElements(); ++i) {
    ret &= members_->Nth(i)->Check(env);
  }
  return ret;
}

void ClassDecl::EmitSetup(FrameAllocator *falloc, CodeGenerator *codegen,
                          SymTable *env) {
  // Because we're doing recursive walks up the class hierarchy tree, this
  // method for this object may be called by a child. If Emit has already been
  // called, just return.
  if (class_falloc_ != NULL) {
    return;
  }

#ifdef __DEBUG_TAC
  PrintDebug("tac", "ClassDecl %s\n", id_->name());
#endif

  // Recursively call Emit on the parent class to make sure that the v_table_ and
  // fields list we are inheriting are properly set up in case the parent's
  // ClassDecl comes after this one. If we are inheriting, copy the parent's
  // vtable, field list, and FrameAllocator. Because any new fields would be
  // placed after all inherited methods, we can begin at the offset set by
  // the parent's FrameAllocator
  class_label_ = codegen->NewClassLabel(id_->name());
  v_table_ = new List<FnDecl*>;
  fields_ = new List<VarDecl*>;
  if (extends_) {
    Assert(parent_ != NULL);

    // Note: parent will ignore falloc and env parameters and use its own
    parent_->EmitSetup(falloc, codegen, env);
    List<FnDecl*> *parentVTable = parent_->GetVTable();
    List<VarDecl*> *parentFields = parent_->GetFields();
    for (int i = 0; i < parentVTable->NumElements(); ++i) {
      v_table_->Append(parentVTable->Nth(i));
    }
    for (int i = 0; i < parentFields->NumElements(); ++i) {
      fields_->Append(parentFields->Nth(i));
    }

#ifdef __DEBUG_TAC
    PrintDebug("tac", "Before: vtable %d fields %d\n", v_table_->NumElements(),
               fields_->NumElements());
#endif

    class_falloc_ = new FrameAllocator(parent_->GetFalloc());
  } else {
    class_falloc_ = new FrameAllocator(classRelative, FRAME_UP);
  }

  // Merge class's methods and fields with v_table_ and fields inherited from
  // parent or empty v_table_ and field lists if class is a base class. For each
  // field or method, call the field or method's Emit method to set up the
  // field location (relative to base of class) and
  //
  // XXX Okay, this will be O(n^2), but right now we just need to get this to
  //     work. Optimize the algorithm later.

  FnDecl *method = NULL;
  VarDecl *field = NULL;

  methods_to_emit_ = new List<FnDecl*>;
  for (int i = 0; i < members_->NumElements(); ++i) {
    method = dynamic_cast<FnDecl*>(members_->Nth(i));
    if (method != 0) {
      int j;
      for (j = 0; j < v_table_->NumElements(); ++j) {
        if (method->PrototypeEqual(v_table_->Nth(j))) {
          v_table_->RemoveAt(j);
          v_table_->InsertAt(method, j);

          method->SetMethodLabel(class_label_);
          method->SetMethodOffset(j);
          methods_to_emit_->Append(method);
          break;
        }
      }

      if (j >= v_table_->NumElements()) {
        // Method does not override any parent methods
        v_table_->Append(method);

        method->SetMethodLabel(class_label_);
        method->SetMethodOffset(j);
        methods_to_emit_->Append(method);
      }
    } else {
      field = dynamic_cast<VarDecl*>(members_->Nth(i));
      Assert(field != 0);

      // We might not need the insertion for loop because semantically
      // correct code will not be overriding parent fields.
      fields_->Append(field);
      field->Emit(class_falloc_, codegen, class_env_);
    }
  }
}

void ClassDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                     SymTable *env) {
  for (int i = 0; i < methods_to_emit_->NumElements(); ++i) {
    methods_to_emit_->Nth(i)->EmitMethod(this, class_falloc_, codegen, class_env_);
  }

  // Emit vtable. We have already emitted fields and methods
#ifdef __DEBUG_TAC
  PrintDebug("tac", "After: vtable %d fields %d\n",
      v_table_->NumElements(), fields_->NumElements());
#endif

  num_fields_ = fields_->NumElements();
  List<const char*> *method_label_s = new List<const char*>;
  for (int i = 0; i < v_table_->NumElements(); ++i) {
    method_label_s->Append(v_table_->Nth(i)->GetMethodLabel());
  }
  codegen->GenVTable(class_label_, method_label_s);
}

/* Class: InterfaceDecl
 * --------------------
 * Implementation of class InterfaceDecl
 */

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
  Assert(n != NULL && m != NULL);
  (members_ = m)->SetParentAll(this);
}

void InterfaceDecl::PrintChildren(int indent_level) {
  id_->Print(indent_level + 1);
  members_->PrintAll(indent_level + 1);
}

bool InterfaceDecl::CheckDecls(SymTable *env) {
  Symbol *sym = NULL;
  bool ret = true;

  if ((sym = env->findLocal(id_->name())) != NULL) {
    ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
    ret = false;
  }

  interface_env_ = env->addWithScope(id_->name(), this, S_INTERFACE);
  if (interface_env_ == false) {
    return false;
  }

  for (int i = 0; i < members_->NumElements(); ++i) {
    ret &= members_->Nth(i)->CheckDecls(interface_env_);
  }

  return ret;
}

/* pp3-checkpoint: Scope checking
 *   1. Check each FnDecl
 */
bool InterfaceDecl::Check(SymTable *env) {
  bool ret = true;
  for (int i = 0; i < members_->NumElements(); ++i) {
    ret &= members_->Nth(i)->Check(env);
  }

  return ret;
}

void InterfaceDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen,
                         SymTable *env) {
  // XXX: Interfaces not implemented
  Failure("Interfaces not implemented");
}

/* Class: FnDecl
 * -------------
 * Implementation of class FnDecl
 */

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
  Assert(n != NULL && r!= NULL && d != NULL);
  (return_type_ = r)->set_parent(this);
  (formals_ = d)->SetParentAll(this);
  body_ = NULL;
  fn_env_ = NULL;
  param_falloc_ = NULL;
  body_falloc_ = NULL;
  method_label_ = NULL;
  function_label_ = NULL;
  method_offset_ = 0;
}

void FnDecl::SetFunctionBody(Stmt *b) {
  (body_ = b)->set_parent(this);
}

void FnDecl::PrintChildren(int indent_level) {
  return_type_->Print(indent_level + 1, "(return type) ");
  id_->Print(indent_level + 1);
  formals_->PrintAll(indent_level + 1, "(formals) ");
  if (body_) {
    body_->Print(indent_level + 1, "(body) ");
  }
}

bool FnDecl::CheckDecls(SymTable *env) {
  bool ret = true;
  Symbol *sym;
  if ((sym = env->findLocal(id_->name())) != NULL) {
    ret = false;
    ReportError::DeclConflict(this, dynamic_cast<Decl *>(sym->getNode()));
  }
  if ((fn_env_ = env->addWithScope(id_->name(), this, S_FUNCTION)) == false) {
    return false;
  }
  for (int i = 0; i < formals_->NumElements(); ++i) {
    ret &= formals_->Nth(i)->CheckDecls(fn_env_);
  }
  if (body_) {
    if (!body_->CheckDecls(fn_env_)) {
      return false;
    }
  }
  return ret;
}

/* pp3-checkpoint: scope checking
 *   1. Check return type
 *   2. Check formals
 *   3. If body, call body's check
 */
bool FnDecl::Check(SymTable *env) {
  bool ret = true;
  ret &= return_type_->Check(env);
  for (int i = 0; i < formals_->NumElements(); ++i) {
    ret &= formals_->Nth(i)->Check(env);
  }
  if (body_) {
    ret &= body_->Check(env);
  }
  return ret;
}

bool FnDecl::TypeEqual(FnDecl *fn) {
  if (!return_type_->IsEquivalentTo(fn->GetReturnType())) {
    return false;
  }
  List<VarDecl*> *other_formals_ = fn->GetFormals();
  if (formals_->NumElements() != other_formals_->NumElements()) {
    return false;
  }
  for (int i = 0; i < other_formals_->NumElements(); ++i) {
    if (!formals_->Nth(i)->GetType()->IsEquivalentTo(other_formals_->Nth(i)->GetType())) {
      return false;
    }
  }
  return true;
}

bool FnDecl::PrototypeEqual(FnDecl *fn) {
  if (!TypeEqual(fn)) {
    return false;
  }

  if (strcmp(id_->name(), fn->GetName()) == 0) {
    return true;
  } else {
    return false;
  }
}

void FnDecl::Emit(FrameAllocator *falloc, CodeGenerator *codegen, SymTable *env) {
  BeginFunc *begin_fn;
  Symbol *sym = NULL;
  param_falloc_ = new FrameAllocator(fpRelative, FRAME_UP);
  body_falloc_  = new FrameAllocator(fpRelative, FRAME_DOWN);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "FnDecl %s\n", id_->name());
#endif

  function_label_ = codegen->NewFunctionLabel(id_->name());
  codegen->GenLabel(function_label_);
  begin_fn = codegen->GenBeginFunc();
  for (int i = 0; i < formals_->NumElements(); ++i) {
    formals_->Nth(i)->Emit(param_falloc_, codegen, fn_env_);
  }
  body_->Emit(body_falloc_, codegen, fn_env_);
  begin_fn->SetFrameSize(body_falloc_->GetSize());
  codegen->GenEndFunc();
}

void FnDecl::EmitMethod(ClassDecl *classDecl, FrameAllocator *falloc,
    CodeGenerator *codegen, SymTable *env) {
  BeginFunc *begin_fn;
  param_falloc_ = new FrameAllocator(fpRelative, FRAME_UP);
  body_falloc_  = new FrameAllocator(fpRelative, FRAME_DOWN);

#ifdef __DEBUG_TAC
  PrintDebug("tac", "FnDecl Method %s::%s\n", classDecl->GetName(), id_->name());
#endif

  codegen->GenLabel(method_label_);
  begin_fn = codegen->GenBeginFunc();

  // Simulate an implicit first "this" parameter
  char *thisName = strdup("this");
  Location *thisParam = param_falloc_->Alloc(thisName, 4);
  fn_env_->add(thisName, NULL, thisParam);
  for (int i = 0; i < formals_->NumElements(); ++i) {
    formals_->Nth(i)->Emit(param_falloc_, codegen, fn_env_);
  }

  body_->Emit(body_falloc_, codegen, fn_env_);
  begin_fn->SetFrameSize(body_falloc_->GetSize());
  codegen->GenEndFunc();
}

void FnDecl::SetMethodLabel(char *class_label_) {
  int len = strlen(class_label_) + strlen(id_->name()) + 2;
  method_label_ = (char *) malloc(len);
  if (method_label_ == NULL) {
    Failure("FnDecl::SetMethodLabel(): Malloc out of memory");
  }

  sprintf(method_label_, "%s.%s", class_label_, id_->name());
  method_label_[len - 1] = '\0';
}

/* Class: VFunction
 * ----------------
 * Implementation for VFunction class
 */

VFunction::VFunction(FnDecl *p, NamedType *type) {
  prototype_ = p;
  intf_type_ = type;
  implemented_ = false;
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
