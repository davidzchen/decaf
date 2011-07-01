

bin_SCRIPTS = badbool.test \
	baddouble.test \
	badident.test \
	badint.test \
	badop.test \
	badpre.test \
	badreserve.test \
	badstring.test \
	comment.test \
	define.test \
	ident.test \
	number.test \
	program2.test \
	program3.test \
	reserve_op.test \
	string.test

TESTS = $(bin_SCRIPTS)

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)/tests

EXTRA_DIST = $(TESTS) *.out *.frag *.decaf test.in gentest.pl

clean-local:
	rm -rf *.err *.put *.test

GEN = ./gentest.pl

badbool.test:
	$(AM_V_GEN)$(GEN) -f badbool -e frag && chmod +x badbool.test

baddouble.test:
	$(AM_V_GEN)$(GEN) -f baddouble -e frag && chmod +x baddouble.test

badident.test:
	$(AM_V_GEN)$(GEN) -f badident -e frag && chmod +x badident.test

badint.test:
	$(AM_V_GEN)$(GEN) -f badint -e frag && chmod +x badint.test

badop.test:
	$(AM_V_GEN)$(GEN) -f badop -e frag && chmod +x badop.test

badpre.test:
	$(AM_V_GEN)$(GEN) -f badpre -e frag && chmod +x badpre.test

badreserve.test:
	$(AM_V_GEN)$(GEN) -f badreserve -e frag && chmod +x badreserve.test

badstring.test:
	$(AM_V_GEN)$(GEN) -f badstring -e frag && chmod +x badstring.test

comment.test:
	$(AM_V_GEN)$(GEN) -f comment -e frag && chmod +x comment.test

define.test:
	$(AM_V_GEN)$(GEN) -f define -e frag && chmod +x define.test

ident.test:
	$(AM_V_GEN)$(GEN) -f ident -e frag && chmod +x ident.test

number.test:
	$(AM_V_GEN)$(GEN) -f number -e frag && chmod +x number.test

program2.test:
	$(AM_V_GEN)$(GEN) -f program2 -e decaf && chmod +x program2.test

program3.test:
	$(AM_V_GEN)$(GEN) -f program3 -e decaf && chmod +x program3.test

reserve_op.test:
	$(AM_V_GEN)$(GEN) -f reserve_op -e frag && chmod +x reserve_op.test

string.test:
	$(AM_V_GEN)$(GEN) -f string -e frag && chmod +x string.test

.PHONY: clean-local
