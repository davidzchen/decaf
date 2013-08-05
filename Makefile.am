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
	src/ast_decl.cc \
	src/ast_expr.cc \
	src/ast_stmt.cc \
	src/ast_type.cc \
	src/decaf-parse.cc \
	src/decaf-lex.cc \
	src/dcc.cc

dcc_CPPFLAGS = -I$(top_srcdir)/src/arch/mips $(AM_CPPFLAGS)
EXTRA_dcc_SOURCES = src/decaf-parse.yy src/decaf-lex.ll
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
	src/ast_decl.cc \
	src/ast_expr.cc \
	src/ast_stmt.cc \
	src/ast_type.cc \
	src/decaf-parse.cc \
	src/decaf-lex.cc \
	src/dcc.cc

dcc_i386_CPPFLAGS = -I$(top_srcdir)/src/arch/x86 $(AM_CPPFLAGS)
EXTRA_dcc_i386_SOURCES = src/decaf-parse.yy src/decaf-lex.ll
dcc_i386_LDADD = -lc -lm -ll

BUILT_SOURCES = \
	src/decaf-parse.cc \
	src/decaf-lex.cc \
	src/decaf-parse.output \
	src/decaf-parse.h

#test:
#	cd tests && $(MAKE) $(AM_MAKEFLAGS)
#	cd all-tests && $(MAKE) $(AM_MAKEFLAGS)

#clean-local:
#	cd tests && $(MAKE) clean
#	cd all-tests && $(MAKE) clean

#check-local:
#	cd tests && $(MAKE) $(AM_MAKEFLAGS) check
#	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check

#check-parse:
#	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check-parse

#check-scope:
#	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check-scope

#check-semantic:
#	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check-semantic

#.PHONY: test clean-local check-local check-parse check-scope check-semantic



#test:
#	cd tests && $(MAKE) $(AM_MAKEFLAGS)

#clean-local:
#	cd tests && $(MAKE) clean

#check-local:
#	cd tests && $(MAKE) $(AM_MAKEFLAGS) check

#.PHONY: test clean-local check-codegen

#check-codegen:
#	cd tests && $(MAKE) check-codegen
