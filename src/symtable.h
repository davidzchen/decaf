/* File: symtable.h                          -*- C++ -*-
 * ----------------
 * Implementation of symbol table and symbol table entries. Symbol table
 * is implemented as a "spaghetti stack," which "threads" the parse tree
 * during the symbol table generation pass during semantic analysis.
 */

#ifndef _H_SYMTABLE
#define _H_SYMTABLE

#include <cstdlib>
#include "hashtable.h"
#include "ast.h"
#include "list.h"

enum
{
  S_VARIABLE,
  S_INTERFACE,
  S_FUNCTION,
  S_CLASS
};

class Node;
class SymTable;

class Symbol
{
  protected:
    int type;
    Node *node;
    SymTable *env;

  public:
    Symbol(int t, Node *n);
    Symbol(int t, Node *n, SymTable *e);

    int getType() { return type; }
    void setType(int t) { type = t; }
    Node *getNode() { return node; }
    void setNode(Node *n) { node = n; }
    SymTable *getEnv() { return env; }
    void setEnv(SymTable *e) { env = e; }

    void print(int indentLevel);
};

class SymTable
{
  protected:
    SymTable *prev;
    Hashtable<Symbol*> *table;
    List<SymTable*> *blocks;
    SymTable *super;

  public:
    SymTable();

    void setParent(SymTable *p) { prev = p; }
    SymTable *getParent() { return prev; }
    void setSuper(SymTable *s) { super = s; }
    SymTable *getSuper() { return super; }

    bool add(char *key, Node *node);
    SymTable *addScope();
    SymTable *addWithScope(char *key, Node *node, int type);

    Symbol *findSuper(char *key);
    Symbol *findSuper(char *key, int type);
    Symbol *findLocal(char *key);
    Symbol *findLocal(char *key, int type);
    Symbol *find(char *key);
    Symbol *find(char *key, int type);
    Symbol *findUp(char *key);
    Symbol *findUp(char *key, int type);

    void print(int indentLevel);
    int getSize();
};

#endif
