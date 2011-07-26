/* File: symtable.cc
 * -----------------
 * Symbol table implementation
 */

#include <iostream>
#include <sstream>
#include <string>
#include "utility.h"
#include "symtable.h"
#include "ast_decl.h"

/* Class: Symbol
 * -------------
 * Implementation for symbol class
 */

Symbol::Symbol(int t, Node *n)
{
  type = t;
  node = n;
  env = NULL;
}

Symbol::Symbol(int t, Node *n, SymTable *e)
{
  type = t;
  node = n;
  env = e;
}

void Symbol::print(int indentLevel)
{
  const int numSpaces = 3;
  ostringstream stream;

  stream << dynamic_cast<Decl*>(node);

  printf("\n");
  printf("%*s%s: %d [%s]", numSpaces * indentLevel, "",
         node->GetPrintNameForNode(), type, stream.str().c_str());
  if (env)
      env->print(indentLevel + 1);
}

/* Class: SymTable 
 * ---------------
 * Implementation for SymTable class.
 */

SymTable::SymTable()
{
  prev = NULL;
  super = NULL;
  table = new Hashtable<Symbol*>;
  blocks = new List<SymTable*>;
}

bool SymTable::add(char *key, Node *node)
{
  Symbol *s = new Symbol(S_VARIABLE, node);
  table->Enter(key, s, false);

  return true;
}

SymTable *SymTable::addScope()
{
  SymTable *child = new SymTable;
  child->setParent(this);
  blocks->Append(child);

  return child;
}

SymTable *SymTable::addWithScope(char *key, Node *node, int type)
{
  SymTable *env = new SymTable;
  env->setParent(this);
  Symbol *s = new Symbol(type, node, env);
  table->Enter(key, s, false);

  return env;
}

Symbol *SymTable::findSuper(char *key)
{
  Symbol *sym = NULL;
  SymTable *current = this;

  for ( ; current != NULL; current = current->getSuper())
    {
      if ((sym = current->findLocal(key)) != NULL)
        return sym;
    }

  return NULL;
}

Symbol *SymTable::findSuper(char *key, int type)
{
  Symbol *s = findSuper(key);

  if (s)
    {
      if (s->getType() == type)
        return s;
      else
        return NULL;
    }

  return NULL;
}

Symbol *SymTable::findLocal(char *key)
{
  Symbol *sym = NULL;

  if ((sym = table->Lookup(key)) != NULL)
    return sym;

  if (super)
    {
      if ((sym = findSuper(key)) != NULL)
        return sym;
    }

  return NULL;
}

Symbol *SymTable::findLocal(char *key, int type)
{
  Symbol *s = findLocal(key);

  if (s)
    {
      if (s->getType() == type)
        return s;
      else
        return NULL;
    }

  return NULL;
}

Symbol *SymTable::find(char *key)
{
  SymTable *current = this;
  Symbol *sym = NULL;

  for ( ; current != NULL; current = current->getParent())
    {
      if ((sym = current->findLocal(key)) != NULL)
	return sym;
    }

  if (super)
    {
      if ((sym = findSuper(key)) != NULL)
        return sym;
    }

  return NULL;
}

Symbol *SymTable::find(char *key, int type)
{
  Symbol *s = find(key);

  if (s)
    {
      if (s->getType() == type)
        return s;
      else
        return NULL;
    }

  return NULL;
}

Symbol *SymTable::findUp(char *key)
{
  SymTable *current = prev;
  Symbol *sym = NULL;

  for ( ; current != NULL; current = current->getParent())
    {
      if ((sym = current->findLocal(key)) != NULL)
	return sym;
    }

  return NULL;
}

Symbol *SymTable::findUp(char *key, int type)
{
  Symbol *s = findUp(key);

  if (s)
    {
      if (s->getType() == type)
        return s;
      else
        return NULL;
    }

  return NULL;
}

void SymTable::print(int indentLevel)
{
  const char numSpaces = 3;
  printf("\n");
  printf("%*s%s %d", numSpaces * indentLevel, "", "Scope Table", table->NumEntries());

  Iterator<Symbol*> iter = table->GetIterator();
  Symbol *sym;

  while ((sym = iter.GetNextValue()) != NULL)
    {
      sym->print(indentLevel);
    }

  for (int i = 0; i < blocks->NumElements(); i++)
    {
      blocks->Nth(i)->print(indentLevel + 1);
    }
}

int SymTable::getSize()
{
  return table->NumEntries();
}

