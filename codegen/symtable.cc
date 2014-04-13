/* File: symtable.cc
 * -----------------
 * Symbol table implementation
 */

#include <iostream>
#include <sstream>
#include <string>

#include "ast/decl.h"
#include "codegen/symtable.h"

/* Class: Symbol
 * -------------
 * Implementation for symbol class
 */

Symbol::Symbol(int t, Node *n) {
  type = t;
  node = n;
  env = NULL;
  location = NULL;
}

Symbol::Symbol(int t, Node *n, Location *loc) {
  type = t;
  node = n;
  env = NULL;
  location = loc;
}

Symbol::Symbol(int t, Node *n, SymTable *e) {
  type = t;
  node = n;
  env = e;
  location = NULL;
}

void Symbol::print(int indentLevel) {
  const int numSpaces = 3;
  std::ostringstream stream;

  stream << dynamic_cast<Decl*>(node);

  printf("\n");
  printf("%*s%s: %d [%s] [addr: %p] [table addr: %p]",
         numSpaces * indentLevel, "",
         node->GetPrintNameForNode(), type,
         stream.str().c_str(),
         this, env);
  if (env) {
    env->print(indentLevel + 1);
  }
}

/* Class: SymTable
 * ---------------
 * Implementation for SymTable class.
 */

SymTable::SymTable() {
  _prev = NULL;
  _super = NULL;
  _this = NULL;
  _table = new Hashtable<Symbol*>;
  _blocks = new List<SymTable*>;
  _refnode = NULL;
  _breaknode = NULL;
}

Node *SymTable::getThisClass() {
  if (!_this) {
    return NULL;
  }
  SymTable *classEnv = _this;
  return classEnv->getRefNode();

}

bool SymTable::add(char *key, Node *node) {
  Symbol *s = new Symbol(S_VARIABLE, node);
  _table->Enter(key, s, false);
  return true;
}

bool SymTable::add(char *key, Node *node, Location *loc) {
  Symbol *s = new Symbol(S_VARIABLE, node, loc);
  _table->Enter(key, s, false);
  return true;
}

SymTable *SymTable::addScope() {
  SymTable *child = new SymTable;
  child->setParent(this);
  if (_this) {
    child->setThis(_this);
  }
  _blocks->Append(child);

  if (_refnode) {
    child->setRefNode(_refnode);
  }
  if (_breaknode) {
    child->setBreakNode(_breaknode);
  }
  return child;
}

SymTable *SymTable::addWithScope(char *key, Node *node, int type) {
  SymTable *newEnv = new SymTable;
  Symbol *refNode = NULL;
  newEnv->setParent(this);
  if (_this) {
    newEnv->setThis(_this);
  }

  refNode = new Symbol(type, node, newEnv);
  _table->Enter(key, refNode, false);
  newEnv->setRefNode(node);
  _breaknode = NULL;
  return newEnv;
}

bool SymTable::subclassOf(char *key) {
  SymTable *current = _super;
  ClassDecl *classDecl = NULL;

  if (!_super) {
    return false;
  }

  for ( ; current != NULL; current = current->getSuper()) {
    classDecl = dynamic_cast<ClassDecl*>(current->getRefNode());
    if (classDecl == 0) {
      continue;
    }

    if (strcmp(key, classDecl->GetName()) == 0 ||
        classDecl->ImplementsInterface(key)) {
      return true;
    }
  }

  return false;
}

Symbol *SymTable::findSuper(char *key) {
  Symbol *sym = NULL;
  SymTable *current = _super;

  if (!_super) {
    return NULL;
  }

  for ( ; current != NULL; current = current->getSuper()) {
    if ((sym = current->findLocal(key)) != NULL) {
      return sym;
    }
  }

  return NULL;
}

Symbol *SymTable::findInClass(char *key) {
  Symbol *sym = NULL;

  if ((sym = findLocal(key)) != NULL) {
    return sym;
  }

  if ((sym = findSuper(key)) != NULL) {
    return sym;
  }

  return NULL;
}

Symbol *SymTable::findLocal(char *key) {
  Symbol *sym = NULL;

  if ((sym = _table->Lookup(key)) != NULL) {
    return sym;
  }

  if (_super) {
    if ((sym = findSuper(key)) != NULL) {
      return sym;
    }
  }

  return NULL;
}


Symbol *SymTable::find(char *key) {
  SymTable *current = this;
  Symbol *sym = NULL;

  for ( ; current != NULL; current = current->getParent()) {
    if ((sym = current->findLocal(key)) != NULL) {
      return sym;
    }
  }

  if (_super) {
    if ((sym = findSuper(key)) != NULL) {
      return sym;
    }
  }

  return NULL;
}

Symbol *SymTable::findUp(char *key) {
  SymTable *current = _prev;
  Symbol *sym = NULL;

  for ( ; current != NULL; current = current->getParent()) {
    if ((sym = current->findLocal(key)) != NULL) {
      return sym;
    }
  }

  return NULL;
}

Symbol *SymTable::findClassField(char *className, char *fieldName) {
  Symbol *classSym = find(className);
  if (classSym == NULL) {
    return NULL;
  }
  return classSym->getEnv()->find(fieldName);
}

void SymTable::print(int indentLevel) {
  const char numSpaces = 3;
  printf("\n");
  printf("%*s%s %d ref %p this %p",
      numSpaces * indentLevel,
      "",
      "Scope Table",
      _table->NumEntries(),
      _refnode,
      _this);

  Iterator<Symbol*> iter = _table->GetIterator();
  Symbol *sym;

  while ((sym = iter.GetNextValue()) != NULL) {
    sym->print(indentLevel);
  }

  for (int i = 0; i < _blocks->NumElements(); i++) {
    _blocks->Nth(i)->print(indentLevel + 1);
  }
}

int SymTable::getSize() {
  return _table->NumEntries();
}
