EXTRA_DIST = gentest.pl

clean-local:
	cd scanner && $(MAKE) clean
	cd parse && $(MAKE) clean


all-local:
	cd scanner && $(MAKE) $(AM_MAKEFLAGS)
	cd parse && $(MAKE) $(AM_MAKEFLAGS)

check-scanner:
	cd scanner && $(MAKE) $(AM_MAKEFLAGS) check

check-parse:
	cd parse && $(MAKE) $(AM_MAKEFLAGS) check
