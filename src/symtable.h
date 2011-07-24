/* File: symtable.h                          -*- C++ -*-
 * ----------------
 * Symbol table implementation
 */

#ifndef _H_SYMTABLE
#define _H_SYMTABLE

#include <cstdlib>
#include "hashtable.h"
#include "ast.h"

enum {
  S_VARIABLE,
  S_INTERFACE,
  S_FUNCTION,
  S_CLASS
};

class SymTable;

class Symbol
{
 protected:
  int type;
  Node *node;
  SymTable *child;

 public:
  Symbol(int t, Node *n);
  Symbol(int t, Node *n, SymTable *c);
  int getType() { return type; }
  void setType(int t) { type = t; }
  Node *getNode() { return node; }
  void setNode(Node *n) { node = n; }
  SymTable *getChild() { return child; }
  void setChild(SymTable *c) { child = c; } 
  void print(int indentLevel);
};

class SymTable
{
 protected:
  SymTable *prev;
  Hashtable<Symbol*> *table;

 public:
  SymTable();
  bool add(char *key, Node *node);
  SymTable *addScope();
  SymTable *addWithScope(char *key, Node *node, int type);
  void setParent(SymTable *p) { prev = p; }
  SymTable *getParent() { return prev; } 
  Symbol *findLocal(char *key);
  Symbol *find(char *key);
  Symbol *findUp(char *key);
  void print(int indentLevel);
};

#endif
