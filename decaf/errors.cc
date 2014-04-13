/**
 * File: errors.cc
 * ---------------
 * Implementation for error-reporting class.
 */

#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>

#include "decaf/errors.h"
#include "decaf/lexer.h"
#include "ast/type.h"
#include "ast/expr.h"
#include "ast/stmt.h"
#include "ast/decl.h"

using std::cerr;
using std::endl;

int ReportError::num_errors_ = 0;

void ReportError::UnderlineErrorInLine(const char *line, yyltype *pos) {
  if (!line) {
    return;
  }
  cerr << line << endl;
  for (int i = 1; i <= pos->last_column; ++i) {
    cerr << (i >= pos->first_column ? '^' : ' ');
  }
  cerr << endl;
}

void ReportError::OutputError(yyltype *loc, std::string msg) {
  ++num_errors_;
  fflush(stdout); // make sure any buffered text has been output
  if (loc) {
    cerr << endl << "*** Error line " << loc->first_line << "." << endl;
    UnderlineErrorInLine(GetLineNumbered(loc->first_line), loc);
  } else {
    cerr << endl << "*** Error." << endl;
  }
  cerr << "*** " << msg << endl << endl;
}

void ReportError::Formatted(yyltype *loc, const char *format, ...) {
  va_list args;
  char errbuf[2048];
  va_start(args, format);
  vsprintf(errbuf,format, args);
  va_end(args);
  OutputError(loc, errbuf);
}

void ReportError::UntermComment() {
  OutputError(NULL, "Input ends with unterminated comment");
}

void ReportError::LongIdentifier(yyltype *loc, const char *ident) {
  std::ostringstream s;
  s << "Identifier too long: \"" << ident << "\"";
  OutputError(loc, s.str());
}

void ReportError::UntermString(yyltype *loc, const char *str) {
  std::ostringstream s;
  s << "Unterminated string constant: " << str;
  OutputError(loc, s.str());
}

void ReportError::UnrecogChar(yyltype *loc, char ch) {
  std::ostringstream s;
  s << "Unrecognized char: '" << ch << "'";
  OutputError(loc, s.str());
}

void ReportError::DeclConflict(Decl *decl, Decl *prevDecl) {
  std::ostringstream s;
  s << "Declaration of '" << decl << "' here conflicts with declaration on line "
    << prevDecl->location()->first_line;
  OutputError(decl->location(), s.str());
}

void ReportError::OverrideMismatch(Decl *fnDecl) {
  std::ostringstream s;
  s << "Method '" << fnDecl << "' must match inherited type signature";
  OutputError(fnDecl->location(), s.str());
}

void ReportError::InterfaceNotImplemented(Decl *cd, Type *interfaceType) {
  std::ostringstream s;
  s << "Class '" << cd << "' does not implement entire interface '"
    << interfaceType << "'";
  OutputError(interfaceType->location(), s.str());
}

void ReportError::IdentifierNotDeclared(Identifier *ident,
                                        LookingReason whyNeeded) {
  std::ostringstream s;
  static const char *names[] =  {
    "type", "class", "interface", "variable", "function"
  };
  Assert(whyNeeded >= 0 && whyNeeded <= sizeof(names)/sizeof(names[0]));
  s << "No declaration found for "<< names[whyNeeded] << " '" << ident << "'";
  OutputError(ident->location(), s.str());
}

void ReportError::IncompatibleOperands(Operator *op, Type *lhs, Type *rhs) {
  std::ostringstream s;
  s << "Incompatible operands: " << lhs << " " << op << " " << rhs;
  OutputError(op->location(), s.str());
}

void ReportError::IncompatibleOperand(Operator *op, Type *rhs) {
  std::ostringstream s;
  s << "Incompatible operand: " << op << " " << rhs;
  OutputError(op->location(), s.str());
}

void ReportError::ThisOutsideClassScope(This *th) {
  OutputError(th->location(), "'this' is only valid within class scope");
}

void ReportError::BracketsOnNonArray(Expr *baseExpr) {
  OutputError(baseExpr->location(), "[] can only be applied to arrays");
}

void ReportError::SubscriptNotInteger(Expr *subscriptExpr) {
  OutputError(subscriptExpr->location(), "Array subscript must be an integer");
}

void ReportError::NewArraySizeNotInteger(Expr *sizeExpr) {
  OutputError(sizeExpr->location(), "Size for NewArray must be an integer");
}

void ReportError::NumArgsMismatch(Identifier *fnIdent, int numExpected,
                                  int numGiven) {
  std::ostringstream s;
  s << "Function '"<< fnIdent << "' expects " << numExpected
    << " argument" << (numExpected == 1 ? "" : "s")
    << " but " << numGiven << " given";
  OutputError(fnIdent->location(), s.str());
}

void ReportError::ArgMismatch(Expr *arg, int argIndex, Type *given,
                              Type *expected) {
  std::ostringstream s;
  s << "Incompatible argument " << argIndex << ": " << given << " given, "
    << expected << " expected";
  OutputError(arg->location(), s.str());
}

void ReportError::ReturnMismatch(ReturnStmt *rStmt, Type *given,
                                 Type *expected) {
  std::ostringstream s;
  s << "Incompatible return: " << given << " given, " << expected << " expected";
  OutputError(rStmt->location(), s.str());
}

void ReportError::FieldNotFoundInBase(Identifier *field, Type *base) {
  std::ostringstream s;
  s << base << " has no such field '" << field <<"'";
  OutputError(field->location(), s.str());
}

void ReportError::InaccessibleField(Identifier *field, Type *base) {
  std::ostringstream s;
  s  << base << " field '" << field << "' only accessible within class scope";
  OutputError(field->location(), s.str());
}

void ReportError::PrintArgMismatch(Expr *arg, int argIndex, Type *given) {
  std::ostringstream s;
  s << "Incompatible argument " << argIndex << ": " << given
    << " given, int/bool/string expected";
  OutputError(arg->location(), s.str());
}

void ReportError::TestNotBoolean(Expr *expr) {
  OutputError(expr->location(), "Test expression must have boolean type");
}

void ReportError::SwitchTestNotInt(Expr *expr) {
  OutputError(expr->location(), "Switch test expression must have int type");
}

void ReportError::BreakOutsideLoop(BreakStmt *bStmt) {
  OutputError(bStmt->location(), "break is only allowed inside a loop");
}

void ReportError::NoMainFound() {
    OutputError(NULL, "Linker: function 'main' not defined");
}

/**
 * Function: yyerror()
 * -------------------
 * Standard error-reporting function expected by yacc. Our version merely
 * just calls into the error reporter above, passing the location of
 * the last token read. If you want to suppress the ordinary "parse error"
 * message from yacc, you can implement yyerror to do nothing and
 * then call ReportError::Formatted yourself with a more descriptive
 * message.
 */

void yyerror(const char *msg) {
  ReportError::Formatted(&yylloc, "%s", msg);
}

/* vim: set ts=2 sts=2 sw=2 et: */
