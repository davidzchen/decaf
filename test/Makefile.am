EXTRA_DIST = gentest.pl

clean-local:
	cd codegen && $(MAKE) clean

all-local:
	cd codegen && $(MAKE) $(AM_MAKEFLAGS)

check-local: check-codegen

check-codegen:
	cd codegen && $(MAKE) $(AM_MAKEFLAGS) check


.PHONY: clean-local all-local check-local
