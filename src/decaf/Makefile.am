AM_CXXFLAGS = -g -Wno-unused -Wno-sign-compare
AM_YFLAGS = -dvty
AM_LFLAGS = -d

bin_PROGRAMS = dcc
AM_CPPFLAGS = -I../

dcc_SOURCES = \
	ast.cc \
	ast_decl.cc \
	ast_expr.cc \
	ast_stmt.cc \
	ast_type.cc \
	decaf-parse.yy \
	decaf-lex.ll \
	dcc.cc

include_HEADERS = \
	ast.h \
	ast_decl.h \
	ast_expr.h \
	ast_stmt.h \
	ast_type.h \
	decaf-parse.h \
	parse.h \
	scanner.h

CLEANFILES = \
	decaf-parse.cc \
	decaf-lex.cc \
	decaf-parse.output \
	decaf-parse.h

dcc_LDADD = ../libtiramisu.la -lc -lm -ll -ly
