/* File: symtable.h                          -*- C++ -*-
 * ----------------
 * Implementation of symbol table and symbol table entries. Symbol table
 * is implemented as a "spaghetti stack," which "threads" the parse tree
 * during the symbol table generation pass during semantic analysis.
 */

#ifndef _H_SYMTABLE
#define _H_SYMTABLE

#include <cstdlib>

#include "arch/mips/tac.h"
#include "ast/ast.h"
#include "decaf/hashtable.h"
#include "decaf/list.h"

enum {
  S_VARIABLE,
  S_INTERFACE,
  S_FUNCTION,
  S_CLASS
};

class Node;
class SymTable;

class Symbol {
 protected:
  int type;
  Node *node;
  SymTable *env;
  Location *location;

 public:
  Symbol(int t, Node *n);
  Symbol(int t, Node *n, Location *loc);
  Symbol(int t, Node *n, SymTable *e);

  int getType() {
    return type;
  }

  void setType(int t) {
    type = t;
  }

  Node *getNode() {
    return node;
  }

  void setNode(Node *n) {
    node = n;
  }

  SymTable *getEnv() {
    return env;
  }
  void setEnv(SymTable *e) {
    env = e;
  }

  Location *getLocation() {
    return location;
  }

  void setLocation(Location *l) {
    location = l;
  }

  void print(int indentLevel);
};

class SymTable {
 protected:
  SymTable *_prev;             // Pointer to SymTable of parent scope
  Node *_refnode;              // Pointer to node that scope belongs to
  Node *_breaknode;            // Pointer to node of next upper loop
  SymTable *_super;            // Pointer to SymTable of parent class
  SymTable *_this;             // Scope of current class, NULL if no class
  Hashtable<Symbol*> *_table;  // Pointer to hash table for scope

  /* For printing purposes only */
  List<SymTable*> *_blocks;

 public:
  SymTable();

  void setParent(SymTable *p) {
    _prev = p;
  }

  SymTable *getParent() {
    return _prev;
  }

  void setSuper(SymTable *s) {
    _super = s;
  }

  SymTable *getSuper() {
    return _super;
  }

  void setThis(SymTable *t) {
    _this = t;
  }

  SymTable *getThis() {
    return _this;
  }

  void setRefNode(Node *s) {
    _refnode = s;
  }

  Node *getRefNode() {
    return _refnode;
  }

  void setBreakNode(Node *s) {
    _breaknode = s;
  }

  Node *getBreakNode() {
    return _breaknode;
  }

  Node *getThisClass();
  bool subclassOf(char *key);

  bool add(char *key, Node *node);
  bool add(char *key, Node *node, Location *loc);
  SymTable *addScope();
  SymTable *addWithScope(char *key, Node *node, int type);

  Symbol *findSuper(char *key);
  Symbol *findSuper(char *key, int type) {
    Symbol *s = findSuper(key);
    return (s && s->getType() == type) ? s : NULL;
  }

  Symbol *findLocal(char *key);
  Symbol *findLocal(char *key, int type) {
    Symbol *s = findLocal(key);
    return (s && s->getType() == type) ? s : NULL;
  }

  Symbol *findInClass(char *key);
  Symbol *findInClass(char *key, int type) {
    Symbol *s = findInClass(key);
    return (s && s->getType() == type) ? s : NULL;
  }

  Symbol *find(char *key);
  Symbol *find(char *key, int type) {
    Symbol *s = find(key);
    return (s && s->getType() == type) ? s : NULL;
  }

  Symbol *findUp(char *key);
  Symbol *findUp(char *key, int type) {
    Symbol *s = findUp(key);
    return (s && s->getType() == type) ? s : NULL;
  }

  Symbol *findClassField(char *className, char *fieldName);
  Symbol *findClassField(char *className, char *fieldName, int type) {
    Symbol *s = findClassField(className, fieldName);
    return (s && s->getType() == type) ? s : NULL;
  }

  void print(int indentLevel);
  int getSize();
};

#endif
