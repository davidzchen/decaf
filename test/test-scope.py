#!/usr/bin/env python

import os
from subprocess import *

TEST_DIRECTORY = 'test/scope'

def main():
  total_tests = 0
  passed_tests = 0
  print "=== Scope tests ==="
  for _, _, files in os.walk(TEST_DIRECTORY):
    for file in files:
      if not (file.endswith('.decaf')):
        continue
      total_tests += 1
      ref_name = os.path.join(TEST_DIRECTORY, "%s.out" % file.split('.')[0])
      test_name = os.path.join(TEST_DIRECTORY, file)
      result = Popen('./dcc ' + test_name + ' -t semantic', 
                     shell = True, stderr = STDOUT, stdout = PIPE)
      result = Popen('diff - ' + ref_name, 
                     shell = True, stdin = result.stdout, stdout = PIPE)
      print 'Test "%s"' % test_name
      result = ''.join(result.stdout.readlines())
      if len(result) > 0:
        print 'FAIL'
        print result
      else:
        print 'PASS'
        passed_tests += 1

    # Print results
    print "-------------------------"
    print "Scope tests: %i/%i passed" % (passed_tests, total_tests)
    if passed_tests < total_tests:
      exit(1)


if __name__ == '__main__':
  main()

# vim: set ai ts=2 sts=2 sw=2 et::q

