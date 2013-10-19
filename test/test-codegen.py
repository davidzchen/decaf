#!/usr/bin/env python

import os
from subprocess import *

TEST_DIRECTORY = 'test/codegen'

def main():
  total_tests = 0
  passed_tests = 0
  print "=== Codegen tests ==="
  for _, _, files in os.walk(TEST_DIRECTORY):
    for file in files:
      if not (file.endswith('.decaf')):
        continue
      total_tests += 1
      ref_name = os.path.join(TEST_DIRECTORY, "%s.out" % file.split('.')[0])
      test_name = os.path.join(TEST_DIRECTORY, file)
      result = Popen('./dcc ' + test_name + ' -o tmp.asm', 
                     shell = True, stderr = STDOUT)
      result = Popen('spim -file tmp.asm',
                     shell = True, stderr = STDOUT, stdout = PIPE)
      result = Popen('diff - ' + ref_name, 
                     shell = True, stdin = result.stdout, stdout = PIPE)
      print 'Executing test "%s"' % test_name
      print ''.join(result.stdout.readlines())

    # Print results
    print "---------------------------"
    print "Codegen tests: %i/%i passed" % (passed_tests, total_tests)
    os.remove('tmp.asm')
    if passed_tests < total_tests:
      exit(1)

if __name__ == '__main__':
  main()

# vim: set ai ts=2 sts=2 sw=2 et::q

