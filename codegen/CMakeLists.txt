list(APPEND CODEGEN_SOURCES
  symtable.cc
  codegen.cc
  framealloc.cc)

add_library(codegen OBJECT ${CODEGEN_SOURCES})
