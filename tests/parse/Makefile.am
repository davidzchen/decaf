

bin_SCRIPTS = \
	bad1.test \
	bad2.test \
	bad3.test \
	bad4.test \
	bad5.test \
	bad6.test \
	bad7.test \
	class.test \
	control.test \
	expressions.test \
	functions.test \
	incrdecr.test \
	inheritance.test \
	interface.test \
	matrix.test \
	simple.test \
	switch.test

TESTS = $(bin_SCRIPTS)

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)/tests/parse

EXTRA_DIST = $(TESTS) *.out *.decaf test.in gentest.pl

clean-local:
	rm -rf *.err *.put *.test

GEN = ./gentest.pl

bad1.test:
	$(AM_V_GEN)$(GEN) -f bad1 -e decaf && chmod +x bad1.test
	
bad2.test:
	$(AM_V_GEN)$(GEN) -f bad2 -e decaf && chmod +x bad2.test

bad3.test:
	$(AM_V_GEN)$(GEN) -f bad3 -e decaf && chmod +x bad3.test

bad4.test:
	$(AM_V_GEN)$(GEN) -f bad4 -e decaf && chmod +x bad4.test

bad5.test:
	$(AM_V_GEN)$(GEN) -f bad5 -e decaf && chmod +x bad5.test

bad6.test:
	$(AM_V_GEN)$(GEN) -f bad6 -e decaf && chmod +x bad6.test

bad7.test:
	$(AM_V_GEN)$(GEN) -f bad7 -e decaf && chmod +x bad7.test

class.test:
	$(AM_V_GEN)$(GEN) -f class -e decaf && chmod +x class.test

control.test:
	$(AM_V_GEN)$(GEN) -f control -e decaf && chmod +x control.test

expressions.test:
	$(AM_V_GEN)$(GEN) -f expressions -e decaf && chmod +x expressions.test

functions.test:
	$(AM_V_GEN)$(GEN) -f functions -e decaf && chmod +x functions.test

incrdecr.test:
	$(AM_V_GEN)$(GEN) -f incrdecr -e decaf && chmod +x incrdecr.test

inheritance.test:
	$(AM_V_GEN)$(GEN) -f inheritance -e decaf && chmod +x inheritance.test

interface.test:
	$(AM_V_GEN)$(GEN) -f interface -e decaf && chmod +x interface.test

matrix.test:
	$(AM_V_GEN)$(GEN) -f matrix -e decaf && chmod +x matrix.test

simple.test:
	$(AM_V_GEN)$(GEN) -f simple -e decaf && chmod +x simple.test

switch.test:
	$(AM_V_GEN)$(GEN) -f switch -e decaf && chmod +x switch.test



