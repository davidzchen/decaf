/// @file ast.cc

#include <string.h>
#include <stdio.h>

#include "ast/ast.h"

Node::Node(yyltype loc) {
  location_ = new yyltype(loc);
  parent_ = NULL;
}

Node::Node() {
  location_ = NULL;
  parent_ = NULL;
}

/// The Print method is used to print the parse tree nodes.
/// If this node has a location (most nodes do, but some do not), it
/// will first print the line number to help you match the parse tree
/// back to the source text. It then indents the proper number of levels
/// and prints the "print name" of the node. It then will invoke the
/// virtual function PrintChildren which is expected to print the
/// internals of the node (itself & children) as appropriate.
void Node::Print(int indentLevel, const char *label) {
  const int numSpaces = 3;
  fprintf(kOutputFile, "\n");
  if (location_ != NULL) {
    fprintf(kOutputFile, "%*d", numSpaces, location_->first_line);
  } else {
    fprintf(kOutputFile, "%*s", numSpaces, "");
  }
  fprintf(kOutputFile, "%*s%s%s: ", indentLevel * numSpaces, "",
          label? label : "",
          GetPrintNameForNode());
  PrintChildren(indentLevel);
}

Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
  name_ = strdup(n);
}

void Identifier::PrintChildren(int indentLevel) {
  fprintf(kOutputFile, "%s", name_);
}

bool Identifier::Check(SymTable *env) {
  if (!env->find(name_)) {
    return false;
  }
  return true;
}

bool Identifier::Check(SymTable *env, int type) {
  if (!env->find(name_, type)) {
    return false;
  }

  return true;
}

// vim: set ai ts=2 sts=2 sw=2 et:
