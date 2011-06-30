AM_CXXFLAGS = -g -Wno-unused -Wno-sign-compare
AM_YFLAGS = -dvty
AM_LFLAGS = -d

CLEANFILES = dscanner.cc lscanner.cc

include_HEADERS = location.h \
		  errors.h \
		  dscanner.h \
		  lscanner.h \
		  utility.h

bin_PROGRAMS = dcc lcc

dcc_SOURCES = utility.cc errors.cc dscanner.ll dcc.cc
dcc_LDADD = -lc -lm -ll

lcc_SOURCES = utility.cc errors.cc lscanner.ll lcc.cc
lcc_LDADD = -lc -lm -ll
