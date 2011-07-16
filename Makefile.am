
AM_CXXFLAGS = -G -Wno-unused -Wno-sign-compare
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src src/decaf src/latte

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
