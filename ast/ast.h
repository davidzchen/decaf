/// @file ast.h
///
/// This file defines the abstract base class Node and the concrete
/// Identifier and Error node subclasses that are used through the tree as
/// leaf nodes. A parse tree is a hierarchical collection of ast nodes (or,
/// more correctly, of instances of concrete subclassses such as VarDecl,
/// ForStmt, and AssignExpr).
///
/// Location: Each node maintains its lexical location (line and columns in
/// file), that location can be NULL for those nodes that don't care/use
/// locations. The location is typcially set by the node constructor.  The
/// location is used to provide the context when reporting semantic errors.
///
/// Parent: Each node has a pointer to its parent. For a Program node, the
/// parent is NULL, for all other nodes it is the pointer to the node one level
/// up in the parse tree.  The parent is not set in the constructor (during a
/// bottom-up parse we don't know the parent at the time of construction) but
/// instead we wait until assigning the children into the parent node and then
/// set up links in both directions. The parent link is typically not used
/// during parsing, but is more important in later phases.
///
/// Printing: The only interesting behavior of the node classes for pp2 is the
/// bility to print the tree using an in-order walk.  Each node class is
/// responsible for printing itself/children by overriding the virtual
/// PrintChildren() and GetPrintNameForNode() methods. All the classes we
/// provide already implement these methods, so your job is to construct the
/// nodes and wire them up during parsing. Once that's done, printing is a snap!
///
/// Semantic analysis: For pp3 you are adding "Check" behavior to the ast
/// node classes. Your semantic analyzer should do an inorder walk on the
/// parse tree, and when visiting each node, verify the particular
/// semantic rules that apply to that construct.

#ifndef AST_AST_H_
#define AST_AST_H_

#include <iostream>
#include <stdlib.h>

#include "codegen/symtable.h"
#include "codegen/codegen.h"
#include "codegen/framealloc.h"
#include "decaf/location.h"
#include "decaf/errors.h"
#include "decaf/list.h"

class SymTable;

class Node {
 public:
  Node(yyltype loc);
  Node();
  virtual ~Node() {}

  yyltype* location() { return location_; }
  Node* parent() { return parent_; }

  void set_parent(Node* parent) { parent_ = parent; }

  virtual const char* GetPrintNameForNode() = 0;

  // Print() is deliberately _not_ virtual
  // subclasses should override PrintChildren() instead
  void Print(int indentLevel, const char* label = NULL);
  virtual void PrintChildren(int indentLevel) {}
  virtual bool Check(SymTable* env) { return true; }

 protected:
  yyltype* location_;
  Node* parent_;
};

class Identifier : public Node {
 public:
  Identifier(yyltype loc, const char* name);
  const char* GetPrintNameForNode() { return "Identifier"; }
  void PrintChildren(int indentLevel);
  friend std::ostream& operator<<(std::ostream& out, Identifier* id) {
    return out << id->name_;
  }
  char* name() { return name_; }
  bool Check(SymTable *env);
  bool Check(SymTable *env, int type);

 protected:
  char* name_;
};

// This node class is designed to represent a portion of the tree that
// encountered syntax errors during parsing. The partial completed tree
// is discarded along with the states being popped, and an instance of
// the Error class can stand in as the placeholder in the parse tree
// when your parser can continue after an error.
class Error : public Node {
 public:
  Error() : Node() {}
  const char* GetPrintNameForNode() { return "Error"; }
  bool check(SymTable *env) { return true; }
};

// vim: set ai ts=2 sts=2 sw=2 et:
#endif /* AST_AST_H_ */
