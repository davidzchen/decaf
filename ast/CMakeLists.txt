list(APPEND AST_SOURCES
  ast.cc
  decl.cc
  expr.cc
  stmt.cc
  type.cc)

add_library(ast OBJECT ${AST_SOURCES})
