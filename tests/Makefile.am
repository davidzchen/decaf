EXTRA_DIST = gentest.pl

clean-local:
	cd scanner && $(MAKE) clean
	cd parse && $(MAKE) clean
	cd scope && $(MAKE) clean

all-local:
	cd scanner && $(MAKE) $(AM_MAKEFLAGS)
	cd parse && $(MAKE) $(AM_MAKEFLAGS)
	cd scope && $(MAKE) $(AM_MAKEFLAGS)

check-local: check-scanner check-parse check-scope check-semantic

check-scanner:
	cd scanner && $(MAKE) $(AM_MAKEFLAGS) check

check-parse:
	cd parse && $(MAKE) $(AM_MAKEFLAGS) check

check-scope:
	cd scope && $(MAKE) $(AM_MAKEFLAGS) check

check-semantic:
	cd semantic && $(MAKE) $(AM_MAKEFLAGS) check

.PHONY: clean-local all-local check-scanner check-parse check-scope check-semantic
