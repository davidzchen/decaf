set(FlexOutput lex.cc)
if(FLEX_FOUND)
  add_custom_command(
    OUTPUT ${FlexOutput}
    COMMAND ${FLEX_EXECUTABLE} -d -o ${FlexOutput} lex.ll)
endif()

set(BisonOutput parse.cc)
if(BISON_FOUND)
  add_custom_command(
    OUTPUT ${BisonOutput}
    COMMAND ${BISON_EXECUTABLE} -dvty parse.yy -o ${BisonOutput}
    DEPENDS ${FlexOutput})
endif()

set_source_files_properties(parse.cc GENERATED)

list(APPEND DECAF_MIPS_SOURCES
  utility.cc
  symtable.cc
  errors.cc
  arch/mips/tac.cc
  arch/mips/mips.cc
  codegen.cc
  framealloc.cc
  ast/ast.cc
  ast/decl.cc
  ast/expr.cc
  ast/stmt.cc
  ast/type.cc
  parse.cc
  lex.cc
  dcc.cc)

add_executable(dcc ${DECAF_MIPS_SOURCES})
target_link_libraries(dcc -ll)
