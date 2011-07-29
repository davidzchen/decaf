ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -G -Wno-unused -Wno-sign-compare

SUBDIRS = lib src

EXTRA_DIST = bootstrap clean synthesize tests m4/gnulib-cache.m4

test:
	cd tests && $(MAKE) $(AM_MAKEFLAGS)

clean-local:
	cd tests && $(MAKE) clean

check-local:
	cd tests && $(MAKE) check

check-parse:
	cd all-tests && $(MAKE) check-parse

check-scope:
	cd tests && $(MAKE) check-scope

check-semantic:
	cd tests && $(MAKE) check-semantic
