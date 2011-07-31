bin_SCRIPTS = \
        bad1.test \
        bad2.test \
        bad3.test \
        bad4.test \
        bad5.test \
        bad6.test \
        bad7.test \
        bad8.test \
        bad9.test \
        blackjack.test \
        matrix.test \
        t1.test \
        t2.test \
        t3.test \
        t4.test \
        t5.test \
        t6.test \
        t7.test \
        t8.test \
        t9.test \
        t10.test

TESTS = $(bin_SCRIPTS)

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)/tests/scope

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
        
bad8.test:
	$(AM_V_GEN)$(GEN) -f bad8 -e decaf && chmod +x bad8.test
        
bad9.test:
	$(AM_V_GEN)$(GEN) -f bad9 -e decaf && chmod +x bad9.test
        
blackjack.test:
	$(AM_V_GEN)$(GEN) -f blackjack -e decaf && chmod +x blackjack.test
        
matrix.test:
	$(AM_V_GEN)$(GEN) -f matrix -e decaf && chmod +x matrix.test
        
t1.test:
	$(AM_V_GEN)$(GEN) -f t1 -e decaf && chmod +x t1.test

t2.test:
	$(AM_V_GEN)$(GEN) -f t2 -e decaf && chmod +x t2.test

t3.test:
	$(AM_V_GEN)$(GEN) -f t3 -e decaf && chmod +x t3.test

t4.test:
	$(AM_V_GEN)$(GEN) -f t4 -e decaf && chmod +x t4.test

t5.test:
	$(AM_V_GEN)$(GEN) -f t5 -e decaf && chmod +x t5.test

t6.test:
	$(AM_V_GEN)$(GEN) -f t6 -e decaf && chmod +x t6.test

t7.test:
	$(AM_V_GEN)$(GEN) -f t7 -e decaf && chmod +x t7.test

t8.test:
	$(AM_V_GEN)$(GEN) -f t8 -e decaf && chmod +x t8.test

t9.test:
	$(AM_V_GEN)$(GEN) -f t9 -e decaf && chmod +x t9.test

t10.test:
	$(AM_V_GEN)$(GEN) -f t10 -e decaf && chmod +x t10.test