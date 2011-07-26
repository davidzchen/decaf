/* File: symtable.cc
 * -----------------
 * Symbol table implementation
 */

#include "utility.h"
#include "symtable.h"

/* Class: Symbol
 * -------------
 * Implementation for symbol class
 */

Symbol::Symbol(int t, Node *n)
{
  type = t;
  node = n;
  child = NULL;
}

Symbol::Symbol(int t, Node *n, SymTable *c)
{
  type = t;
  node = n;
  child = c;
}

void Symbol::print(int indentLevel)
{
  const int numSpaces = 3;
  printf("\n");
  printf("%*s; %d", numSpaces * indentLevel, node->GetPrintNameForNode(), type);
  if (child)
      child->print(indentLevel + 1);
}

/* Class: SymTable 
 * ---------------
 * Implementation for SymTable class.
 */

SymTable::SymTable()
{
  prev = NULL;
  table = new Hashtable<Symbol*>;
}

bool SymTable::add(char *key, Node *node)
{
  Symbol *s = new Symbol(S_VARIABLE, node);
  table->Enter(key, s, false);

  return true;
}

SymTable *SymTable::addScope()
{
  SymTable *child = new SymTable();
  child->setParent(this);

  return child;
}

SymTable *SymTable::addWithScope(char *key, Node *node, int type)
{
  SymTable *child = new SymTable();
  child->setParent(this);
  Symbol *s = new Symbol(type, node, child);
  table->Enter(key, s, false);

  return child;
}

Symbol *SymTable::findLocal(char *key)
{
  return table->Lookup(key);
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

void SymTable::print(int indentLevel)
{
  const char numSpaces = 3;
  printf("\n");
  printf("%*s", numSpaces * indentLevel, "++Table");

  Iterator<Symbol*> iter = table->GetIterator();
  Symbol *sym;

  while ((sym = iter.GetNextValue()) != NULL)
    {
      sym->print(indentLevel);
    }
}
