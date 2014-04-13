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

list(APPEND DECAF_SOURCES
  utility.cc
  errors.cc
  parse.cc
  lex.cc
  dcc.cc)

add_library(decaf OBJECT ${DECAF_SOURCES})
