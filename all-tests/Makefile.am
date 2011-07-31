clean-local:
	cd parse && $(MAKE) clean
	cd scope && $(MAKE) clean
	cd semantic && $(MAKE) clean

all-local:
	cd parse && $(MAKE) $(AM_MAKEFLAGS)
	cd scope && $(MAKE) $(AM_MAKEFLAGS)
	cd semantic && $(MAKE) $(AM_MAKEFLAGS)

check-local: check-parse check-scope check-semantic

check-parse:
	cd parse && $(MAKE) $(AM_MAKEFLAGS) check

check-scope:
	cd scope && $(MAKE) $(AM_MAKEFLAGS) check

check-semantic:
	cd semantic && $(MAKE) $(AM_MAKEFLAGS) check
	
.PHONY: clean-local all-local check-llocal check-parse check-scope check-semantic