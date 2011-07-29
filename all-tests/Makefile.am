clean-local:
	cd parse && $(MAKE) clean

all-local:
	cd parse && $(MAKE) $(AM_MAKEFLAGS)

check-local: check-parse

check-parse:
	cd parse && $(MAKE) $(AM_MAKEFLAGS) check
	
.PHONY: check-parse