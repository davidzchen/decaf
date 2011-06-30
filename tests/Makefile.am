TESTS = badbool.test \
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

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)/tests

EXTRA_DIST = $(TESTS) *.out *.frag *.decaf

clean-local:
	rm -rf *.err *.put

.PHONY: clean-local
