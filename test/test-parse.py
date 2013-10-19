#!/usr/bin/env python

import os
from subprocess import *

TEST_DIRECTORY = 'test/parse'

def main():
  for _, _, files in os.walk(TEST_DIRECTORY):
    for file in files:
      if not (file.endswith('.decaf')):
        continue
      ref_name = os.path.join(TEST_DIRECTORY, "%s.out" % file.split('.')[0])
      test_name = os.path.join(TEST_DIRECTORY, file)
      result = Popen('./dcc ' + test_name + ' -t parser', 
                     shell = True, stderr = STDOUT, stdout = PIPE)
      result = Popen('diff - ' + ref_name, 
                     shell = True, stdin = result.stdout, stdout = PIPE)
      print 'Executing test "%s"' % test_name
      print ''.join(result.stdout.readlines())

if __name__ == '__main__':
  main()

# vim: set ai ts=2 sts=2 sw=2 et::q

