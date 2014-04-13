/// @file location.h
///
/// This file just contains features relative to the location structure
/// used to record the lexical position of a token or symbol.  This file
/// establishes the cmoon definition for the yyltype structure, the global
/// variable yylloc, and a utility function to join locations you might
/// find handy at times.

#ifndef YYLTYPE

// Defines the struct type that is used by the lexer to store
// position information about each lexeme scanned.
typedef struct yyltype {
  // you can ignore this field
  int timestamp;
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  // you can also ignore this field
  char *text;
} yyltype;

#define YYLTYPE yyltype

// The global variable holding the position information about the
// lexeme just scanned.
extern struct yyltype yylloc;

// Takes two locations and returns a new location which represents
// the span from first to last, inclusive.
inline yyltype Join(yyltype first, yyltype last) {
  yyltype combined;
  combined.first_column = first.first_column;
  combined.first_line = first.first_line;
  combined.last_column = last.last_column;
  combined.last_line = last.last_line;
  return combined;
}

// Same as above, except operates on pointers as a convenience
inline yyltype Join(yyltype *firstPtr, yyltype *lastPtr) {
  return Join(*firstPtr, *lastPtr);
}

// vim: set ai ts=2 sts=2 sw=2 et:
#endif
