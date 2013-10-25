#!/usr/bin/env python

import os
from subprocess import *

TEST_DIRECTORY = 'test/codegen'
EXCEPTION_FILE = 'etc/exceptions.s'

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
      result.wait()
     
      input_name = os.path.join(TEST_DIRECTORY, "%s.in" % file.split('.')[0])
      if os.path.exists(input_name):
        result = Popen('spim -exception_file ' + EXCEPTION_FILE + ' -file tmp.asm < ' + input_name,
                       shell = True, stderr = STDOUT, stdout = PIPE)
      else:
        result = Popen('spim -exception_file ' + EXCEPTION_FILE + ' -file tmp.asm',
                       shell = True, stderr = STDOUT, stdout = PIPE)
      
      result = Popen('diff -w - ' + ref_name, 
                     shell = True, stdin = result.stdout, stdout = PIPE)
      print 'Executing test "%s"' % test_name
      result = ''.join(result.stdout.readlines())
      if len(result) > 0:
        print 'FAIL'
        print result
      else:
        print 'PASS'
        passed_tests += 1
      os.remove('tmp.asm')

    # Print results
    print "---------------------------"
    print "Codegen tests: %i/%i passed" % (passed_tests, total_tests)
    if passed_tests < total_tests:
      exit(1)

if __name__ == '__main__':
  main()

# vim: set ai ts=2 sts=2 sw=2 et::q

