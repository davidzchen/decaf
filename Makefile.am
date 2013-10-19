EXTRA_DIST = m4
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory
EXTRA_DIST += bootstrap clean synthesize tests

AM_CPPFLAGS = -I${top_srcdir}/src
AM_CXXFLAGS = -Wno-unused -Wno-sign-compare
AM_YFLAGS = -dvty
AM_LFLAGS = -d

EXTRA_DIST += src/hashtable.cc

bin_PROGRAMS = dcc dcc_i386

dcc_SOURCES = \
	src/utility.cc \
	src/symtable.cc \
	src/errors.cc \
	src/arch/mips/tac.cc \
	src/arch/mips/mips.cc \
	src/codegen.cc \
	src/framealloc.cc \
	src/ast.cc \
	src/ast-decl.cc \
	src/ast-expr.cc \
	src/ast-stmt.cc \
	src/ast-type.cc \
	src/parse.cc \
	src/lex.cc \
	src/dcc.cc

dcc_CPPFLAGS = -I$(top_srcdir)/src/arch/mips $(AM_CPPFLAGS)
EXTRA_dcc_SOURCES = src/parse.yy src/lex.ll
dcc_LDADD = -lc -lm -ll

dcc_i386_SOURCES = \
	src/utility.cc \
	src/symtable.cc \
	src/errors.cc \
	src/arch/x86/tac.cc \
	src/arch/x86/x86.cc \
	src/codegen.cc \
	src/framealloc.cc \
	src/ast.cc \
	src/ast-decl.cc \
	src/ast-expr.cc \
	src/ast-stmt.cc \
	src/ast-type.cc \
	src/parse.cc \
	src/lex.cc \
	src/dcc.cc

dcc_i386_CPPFLAGS = -I$(top_srcdir)/src/arch/x86 $(AM_CPPFLAGS)
EXTRA_dcc_i386_SOURCES = src/parse.yy src/lex.ll
dcc_i386_LDADD = -lc -lm -ll

BUILT_SOURCES = \
	src/parse.cc \
	src/lex.cc \
	src/parse.output

check_SCRIPTS = \
	test/test-parse.py \
	test/test-scope.py \
	test/test-semantic.py \
	test/test-codegen.py

TESTS = $(check_SCRIPTS)

TEST_ENVIRONMENT = 

