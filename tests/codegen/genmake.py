#!/usr/bin/python

import sys
import os

def main(argv=None):
	if argv is None:
		argv = sys.argv

	in_files = []
	out_files = []

	try:
		in_files = os.listdir('.')
	except:
		print >> sys.stderr, "cannot read directory"
		return 3

	for filename in in_files:
		name = os.path.splitext(filename)[0] 
		extension = os.path.splitext(filename)[1]
		if extension == '.decaf':
			out_files.append(name)

	out_files.sort()
	
	try:
		out = open('Makefile.am', 'w')
	except:
		print >> sys.stderr, "cannot write Makefile.am"
		return 2

	out.write("bin_SCRIPTS = \\\n")
	for name in out_files:
		out.write("\t" + name + ".test \\\n")
	out.write("\n")
	out.write("TESTS = $(bin_SCRIPTS)\n\n")
	out.write("TESTS_ENVIRONMENT = top_builddir=$(top_builddir/tests/codegen\n\n")
	out.write("EXTRA_DIST = $(TESTS) *.out *.decaf *.in gentest.pl\n\n")
	out.write("clean-local:\n")
	out.write("\trm -rf *.err *.put *.test\n\n")
	out.write("GEN = ./gentest.pl\n\n")

	for name in out_files:
		out.write("" + name + ".test:\n")
		out.write("\t$(AM_V_GEN)$(GEN) -f " + name + " -e decaf && chmod +x " + name +".test\n\n")

	out.close()

	return 0


if __name__ == "__main__":
	sys.exit(main())

