AM_CXXFLAGS = -g -Wno-unused -Wno-sign-compare
AM_CPPFLAGS = -I$(top_srcdir)/lib
AM_YFLAGS = -dvty
AM_LFLAGS = -d

EXTRA_DIST = hashtable.cc

bin_PROGRAMS = dcc dcc_i386 ltc

dcc_SOURCES = \
	utility.cc utility.h \
	list.h hashtable.h location.h \
	symtable.cc symtable.h \
	errors.cc errors.h \
	arch/mips/tac.cc arch/mips/tac.h \
	arch/mips/mips.cc arch/mips/mips.h \
	codegen.cc codegen.h \
	framealloc.cc framealloc.h \
	ast.cc ast.h \
	ast_decl.cc ast_decl.h \
	ast_expr.cc ast_expr.h \
	ast_stmt.cc ast_stmt.h \
	ast_type.cc ast_type.h \
	scanner.h \
	decaf-parse.cc decaf-parse.h \
	decaf-lex.cc \
	dcc.cc dcc.h
dcc_CPPFLAGS = -I$(top_srcdir)/src/arch/mips
EXTRA_dcc_SOURCES = decaf-parse.yy decaf-lex.ll
dcc_LDADD = ../lib/libgnu.a -lc -lm -ll

dcc_i386_SOURCES = \
	utility.cc utility.h \
	list.h hashtable.h location.h \
	symtable.cc symtable.h \
	errors.cc errors.h \
	arch/x86/tac.cc arch/x86/tac.h \
	arch/x86/x86.cc arch/x86/x86.h \
	codegen.cc codegen.h \
	framealloc.cc framealloc.h \
	ast.cc ast.h \
	ast_decl.cc ast_decl.h \
	ast_expr.cc ast_expr.h \
	ast_stmt.cc ast_stmt.h \
	ast_type.cc ast_type.h \
	scanner.h \
	decaf-parse.cc decaf-parse.h \
	decaf-lex.cc \
	dcc.cc dcc.h
dcc_i386_CPPFLAGS = -I$(top_srcdir)/src/arch/x86
EXTRA_dcc_i386_SOURCES = decaf-parse.yy decaf-lex.ll
dcc_i386_LDADD = ../lib/libgnu.a -lc -lm -ll

ltc_SOURCES = \
	utility.cc utility.h \
	list.h hashtable.h location.h \
	symtable.cc symtable.h \
	errors.cc errors.h \
	arch/mips/tac.cc arch/mips/tac.h \
	arch/mips/mips.cc arch/mips/mips.h \
	codegen.cc codegen.h \
	framealloc.cc framealloc.h \
	ast.cc ast.h \
	ast_decl.cc ast_decl.h \
	ast_expr.cc ast_expr.h \
	ast_stmt.cc ast_stmt.h \
	ast_type.cc ast_type.h \
	scanner.h \
	latte-parse.cc latte-parse.h \
	latte-lex.cc \
	ltc.cc ltc.h
ltc_CPPFLAGS = -I$(top_srcdir)/src/arch/mips
EXTRA_ltc_SOURCES = latte-parse.yy latte-lex.ll
ltc_LDADD = ../lib/libgnu.a -lc -lm -ll

BUILT_SOURCES = \
	decaf-parse.cc \
	decaf-lex.cc \
	decaf-parse.output \
	decaf-parse.h \
	latte-parse.cc \
	latte-lex.cc \
	latte-parse.output \
	latte-parse.h
