/// @file main.cc
///
/// @section DESCRIPTION
///
/// This file defines the main() routine for the program and not much else.
/// You should not need to modify this file.

#include <string.h>
#include <stdio.h>

#include "decaf/utility.h"
#include "decaf/errors.h"
#include "decaf/dcc.h"

int kTestFlag = 0;
FILE* kOutputFile = NULL;

/// @function main
/// @brief Entry point to the entire program.
///
/// We parse the command line and turn on any debugging flags requested by the
/// user when invoking the program.
/// InitLexer() is used to set up the scanner.
/// InitParser() is used to set up the parser. The call to yyparse() will
/// attempt to parse a complete program from the input.

int main(int argc, char *argv[]) {
  ParseCommandLine(argc, argv);
  InitLexer();
  InitParser();
  yyparse();
  return (ReportError::NumErrors() == 0 ? 0 : -1);
}

