EXTRA_DIST = gentest.pl

clean-local:
	cd scope && $(MAKE) clean
	cd semantic && $(MAKE) clean

all-local:
	cd scope && $(MAKE) $(AM_MAKEFLAGS)
	cd semantic && $(MAKE) $(AM_MAKEFLAGS)

check-local: check-scope check-semantic

check-scope:
	cd scope && $(MAKE) $(AM_MAKEFLAGS) check

check-semantic:
	cd semantic && $(MAKE) $(AM_MAKEFLAGS) check

.PHONY: clean-local all-local check-scope check-semantic
