AM_CXXFLAGS = -g -Wno-unused -Wno-sign-compare
AM_YFLAGS = -dvty
AM_LFLAGS = -d

bin_PROGRAMS = ltc
AM_CPPFLAGS = -I../

ltc_SOURCES = \
	ast.cc \
	ast_decl.cc \
	ast_expr.cc \
	ast_stmt.cc \
	ast_type.cc \
	latte-parse.yy \
	latte-lex.ll \
	ltc.cc

include_HEADERS = \
	ast.h \
	ast_decl.h \
	ast_expr.h \
	ast_stmt.h \
	ast_type.h \
	latte-parse.h \
	parse.h \
	scanner.h

CLEANFILES = \
	latte-lex.cc \
	latte-parse.cc \
	latte-parse.h \
	latte-parse.output

ltc_LDADD = ../libtiramisu.la -lc -lm -ll
