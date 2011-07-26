AM_CXXFLAGS = -g -Wno-unused -Wno-sign-compare
AM_YFLAGS = -dvty
AM_LFLAGS = -d

DIST_FILES = hashtable.cc

bin_PROGRAMS = dcc ltc

dcc_SOURCES = \
	utility.cc utility.h \
	list.h hashtable.h location.h \
	symtable.cc symtable.h \
	errors.cc errors.h \
	ast.cc ast.h \
	ast_decl.cc ast_decl.h \
	ast_expr.cc ast_expr.h \
	ast_stmt.cc ast_stmt.h \
	ast_type.cc ast_type.h \
	scanner.h \
	decaf-parse.yy \
	decaf-lex.ll \
	dcc.cc dcc.h
dcc_LDADD = -lc -lm -ll -ly

ltc_SOURCES = \
	utility.cc utility.h \
	list.h hashtable.h location.h \
	symtable.cc symtable.h \
	errors.cc errors.h \
	ast.cc ast.h \
	ast_decl.cc ast_decl.h \
	ast_expr.cc ast_expr.h \
	ast_stmt.cc ast_stmt.h \
	ast_type.cc ast_type.h \
	scanner.h \
	latte-parse.yy \
	latte-lex.ll \
	ltc.cc ltc.h
ltc_LDADD = -lc -lm -ll -ly

CLEANFILES = \
	decaf-parse.cc \
	decaf-lex.cc \
	decaf-parse.output \
	decaf-parse.h \
	latte-parse.cc \
	latte-lex.cc \
	latte-parse.output \
	latte-parse.h