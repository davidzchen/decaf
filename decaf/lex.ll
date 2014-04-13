%{

#include <cstring>
#include <vector>

#include "decaf/lexer.h"
#include "decaf/utility.h"
#include "decaf/errors.h"
#include "decaf/dcc.h"

#define TAB_SIZE 8

// Globals to keep track of state preserved between calls to yylex or used
// outside the lexer.

static int current_line;
static int current_column;
std::vector<const char*> saved_lines;

static void StartAction();
#define YY_USER_ACTION StartAction();

%}

/* The COPY exclusive state matches each line and copies it to the vector of
   lines read before re-processing it, allowing the line to be printed later
   to provide context on errors. */

%s N
%x COPY
%x COMMENT
%option stack

DECIMAL_DIGIT   ([0-9])
DECIMAL_INTEGER ({DECIMAL_DIGIT}+)
OCTAL_DIGIT     ([0-7])
OCTAL_INTEGER   (0{OCTAL_DIGIT});
HEX_DIGIT       ([0-9a-fA-F])
HEX_INTEGER     (0[xX]{HEX_DIGIT}+)
EXPONENT        ([eE][+-]?{DECIMAL_INTEGER})
DOUBLE          ({DECIMAL_INTEGER}"."{DECIMAL_DIGIT}*{EXPONENT}?)
START_STRING    (\"[^"\n]*)
STRING          ({START_STRING}\")
IDENTIFIER      ([a-zA-Z_][a-zA-Z_0-9]*)
OPERATOR        ([-+/*%=.,;!<>^&\|~()[\]{}:])
START_COMMENT   ("/*")
END_COMMENT     ("*/")
SINGLE_COMMENT  ("//"[^\n]*)

%%

<COPY>.* {
  saved_lines.push_back(strdup(yytext));
  current_column = 1;
  yy_pop_state();
  yyless(0);
}

<COPY><<EOF>> {
  yy_pop_state();
}

<*>\n {
  ++current_line;
  current_column = 1;
  if (YYSTATE == COPY) {
    saved_lines.push_back("");
  } else {
    yy_push_state(COPY);
  }
}

[ ]+ {
}

<*>[\t] {
  current_column += TAB_SIZE - current_column % TAB_SIZE + 1;
}

{START_COMMENT} {
  BEGIN(COMMENT);
}

<COMMENT>{END_COMMENT} {
  BEGIN(N);
}

<COMMENT><<EOF>> {
  ReportError::UntermComment();
  return 0;
}

<COMMENT>. {
}

{SINGLE_COMMENT} {
}

"<=" {
  return T_LessEqual;
}

">=" {
  return T_GreaterEqual;
}

"==" {
  return T_Equal;
}

"!=" {
  return T_NotEqual;
}

"&&" {
  return T_And;
}

"||" {
  return T_Or;
}

"[]" {
  return T_Dims;
}

"++" {
  return T_Incr;
}

"--" {
  return T_Decr;
}

">>" {
  return T_RightShift;
}

"<<" {
  return T_LeftShift;
}

{OPERATOR} {
  return yytext[0];
}

"void" {
  return T_Void;
}

"int" {
  return T_Int;
}

"double" {
  return T_Double;
}

"bool" {
  return T_Bool;
}

"string" {
  return T_String;
}

"class" {
  return T_Class;
}

"null" {
  return T_Null;
}

"while" {
  return T_While;
}

"for" {
  return T_For;
}

"if" {
  return T_If;
}

"else" {
  return T_Else;
}

"return" {
  return T_Return;
}

"break" {
  return T_Break;
}

"switch" {
  return T_Switch;
}

"case" {
  return T_Case;
}

"default" {
  return T_Default;
}

"extends" {
  return T_Extends;
}

"this" {
  return T_This;
}

"implements" {
  return T_Implements;
}

"interface" {
  return T_Interface;
}

"new" {
  return T_New;
}

"NewArray" {
  return T_NewArray;
}

"Print" {
  return T_Print;
}

"ReadInteger" {
  return T_ReadInteger;
}

"ReadLine" {
  return T_ReadLine;
}

"true" {
  yylval.boolConstant = 1;
  return T_BoolConstant;
}

"false" {
  yylval.boolConstant = 0;
  return T_BoolConstant;
}

{DECIMAL_INTEGER} {
  yylval.integerConstant = atoi(yytext);
  return T_IntConstant;
}

{OCTAL_INTEGER} {
  int len = strlen(yytext);
  yylval.integerConstant = strtol(yytext, NULL, 8);
  return T_IntConstant;
}

{HEX_INTEGER} {
  yylval.integerConstant = xtoi(yytext);
  return T_IntConstant;
}

{DOUBLE} {
  yylval.doubleConstant = strtod(yytext, NULL);
  return T_DoubleConstant;
}

{STRING} {
  yylval.stringConstant = strdup(yytext);
  return T_StringConstant;
}

{START_STRING} {
  ReportError::UntermString(&yylloc, yytext);
}

{IDENTIFIER} {
  int len = strlen(yytext);
  if (len > MaxIdentLen) {
    ReportError::LongIdentifier(&yylloc, yytext);
    strncpy(yylval.identifier, yytext, MaxIdentLen);
    yylval.identifier[MaxIdentLen] = '\0';
  } else {
    strncpy(yylval.identifier, yytext, len);
    yylval.identifier[len] = '\0';
  }
  return T_Identifier;
}

. {
  ReportError::UnrecogChar(&yylloc, yytext[0]);
}

%%

void InitLexer() {
  PrintDebug("lex", "Initializing lexer.");
  yy_flex_debug = false;
  BEGIN(N);
  yy_push_state(COPY);
  current_line = 1;
  current_column = 1;
}

static void StartAction() {
  yylloc.first_line = current_line;
  yylloc.first_column = current_column;
  yylloc.last_column = current_column + yyleng - 1;
  current_column += yyleng;
}

const char* GetLineNumbered(int line) {
  if (line <= 0 || line > saved_lines.size()) {
    return NULL;
  }
  return saved_lines[line - 1];
}
