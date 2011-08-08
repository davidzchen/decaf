ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -G -Wno-unused -Wno-sign-compare

SUBDIRS = lib src

EXTRA_DIST = bootstrap clean synthesize tests m4/gnulib-cache.m4

if USE_ALL_TESTS

test:
	cd tests && $(MAKE) $(AM_MAKEFLAGS)
	cd all-tests && $(MAKE) $(AM_MAKEFLAGS)

clean-local:
	cd tests && $(MAKE) clean
	cd all-tests && $(MAKE) clean

check-local:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) check
	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check

check-parse:
	cd all-tests && $(MAKE) $(AM_MAKEFLAGS) check-parse

check-scope:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) check-scope

check-semantic:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) check-semantic

.PHONY: test clean-local check-local check-parse check-scope check-semantic

else

test:
	cd tests && $(MAKE) $(AM_MAKEFLAGS)

clean-local:
	cd tests && $(MAKE) clean

check-local:
	cd tests && $(MAKE) $(AM_MAKEFLAGS) check

.PHONY: test clean-local check-codegen

endif

check-codegen:
	cd tests && $(MAKE) check-codegen
