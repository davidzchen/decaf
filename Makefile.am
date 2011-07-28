
AM_CXXFLAGS = -G -Wno-unused -Wno-sign-compare

SUBDIRS = src

EXTRA_DIST = bootstrap clean synthesize tests

test:
	cd tests && $(MAKE) $(AM_MAKEFLAGS)

clean-local:
	cd tests && $(MAKE) clean

check-local:
	cd tests && $(MAKE) check

check-scanner:
	cd tests && $(MAKE) check-scanner

check-parse:
	cd tests && $(MAKE) check-parse

check-scope:
	cd tests && $(MAKE) check-scope

check-semantic:
	cd tests && $(MAKE) check-semantic
