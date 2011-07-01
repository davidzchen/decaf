/* File:  scanner.l
 * ----------------
 * Lex inupt file to generate the scanner for the compiler.
 */

%{

/* The text within this first region delimited by %{ and %} is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */

#include <cstring>
#include <string>
#include "dscanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"

/* Global variable: yylval
 * -----------------------
 * This global variable is how we get attribute information about the token
 * just scanned to the client. The scanner sets the global variable
 * appropriately and since it's global the client can just read it.  In the
 * future, this variable will be declared for us in the y.tab.c file
 * produced by Yacc, but for now, we declare it manually.
 */
YYSTYPE yylval;  // manually declared for pp1, later Yacc provides

/* Global variable: yylloc
 * -----------------------
 * This global variable is how we get position information about the token
 * just scanned to the client. (Operates similarly to yylval above)
 */
struct yyltype yylloc; // manually dclared for pp1, later Yacc provides

/* Macro: YY_USER_ACTION 
 * ---------------------
 * This flex built-in macro can be defined to provide an action which is
 * always executed prior to any matched rule's action. Basically, it is
 * a way of having a piece of code common to all actions factored out to
 * this routine.  We already defined it for you and left the empty
 * function DoBeforeEachAction ready for your use as needed. It will
 * be called once for each pattern scanned from the file, before
 * executing its action.
 */
static void DoBeforeEachAction(); 
#define YY_USER_ACTION DoBeforeEachAction();

/* Function: AdvanceLocation(int c)
 * ================================
 * Updates the last_column and last_line fields of yylloc depending
 * on the character encountered
 */
void AdvanceLocation(int c)
{
	switch (c) {
	case '\n':
		yylloc.last_column = 0;
		yylloc.last_line++;
		break;
	case '\t':
		yylloc.last_column += 8;
		break;
	default:
		yylloc.last_column++;
		break;
	}
}

%}

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later. 
  */

Z_DDIGIT		[0-9]
Z_ODIGIT		[0-7]
Z_XDIGIT		[0-9a-fA-F]
Z_IDENTIFIER		[a-zA-Z][a-zA-Z0-9_]*
Z_ONEOP			[\+\-\*/;\{\}\[\]\.%=\(\)\<\>!\,]
Z_DINTCONSTANT		{Z_DDIGIT}+
Z_XINTCONSTANT		0[xX]{Z_XDIGIT}+
Z_DOUBLECONSTANT	{Z_DDIGIT}+"."{Z_DDIGIT}*([eE][\+\-]?{Z_DDIGIT}+)?


%%             /* BEGIN RULES SECTION */
 /* All patterns and actions should be placed between the start and stop
  * %% markers which delimit the Rules section.
  *
  * TODO: String constants. Error handling for long identifiers.
  * Modify tests for error output. xtoi does not handle capital X
  */ 

"//".*$			{}
"/*"			{
			register int c;
			
			for ( ; ; ) {
				while ((c = yyinput()) != '*' && c != EOF) {
					AdvanceLocation(c);
				}
				if (c == '*') {
					while ((c = yyinput()) == '*') {
						AdvanceLocation(c);
					}
					AdvanceLocation(c);
					if (c == '/')
						break;
				}
				if (c == EOF) {
					ReportError::UntermComment();
				}	
			}
			}
\"[^\n\"]*\"		{ yylval.stringConstant = new char[strlen(yytext) + 1]; 
			  strcpy(yylval.stringConstant, yytext); 
			  return T_StringConstant; }
"<="			{ return T_LessEqual; }
">="			{ return T_GreaterEqual; }
"=="			{ return T_Equal; }
"!="			{ return T_NotEqual; }
"&&"			{ return T_And; }
"||"			{ return T_Or; }
"[]"			{ return T_Dims; }
{Z_ONEOP}		{ return yytext[0]; }
"void"			{ return T_Void; }
"int"			{ return T_Int; }
"double"		{ return T_Double; }
"bool"			{ return T_Bool; }
"string"		{ return T_String; }
"class"			{ return T_Class; }
"null"			{ return T_Null; }
"while"			{ return T_While; }
"for"			{ return T_For; }
"if"			{ return T_If; }
"else"			{ return T_Else; }
"return"		{ return T_Return; }
"break"			{ return T_Break; }
"extends"		{ return T_Extends; }
"this"			{ return T_This; }
"implements"		{ return T_Implements; }
"interface"		{ return T_Interface; }
"new"			{ return T_New; }
"NewArray"		{ return T_NewArray; }
"Print"			{ return T_Print; }
"ReadInteger"		{ return T_ReadInteger; }
"ReadLine"		{ return T_ReadLine; }
"true"			{ yylval.boolConstant = 1;
			  return T_BoolConstant; }
"false"			{ yylval.boolConstant = 0;
			  return T_BoolConstant; }
{Z_XINTCONSTANT}	{ yylval.integerConstant = xtoi(yytext);
			  return T_IntConstant; }
{Z_DINTCONSTANT}	{ yylval.integerConstant = atoi(yytext);
			  return T_IntConstant; }
{Z_DOUBLECONSTANT}	{ yylval.doubleConstant = strtod(yytext, NULL);
			  return T_DoubleConstant; }
{Z_IDENTIFIER}		{
			if (strlen(yytext) > MaxIdentLen) {
				ReportError::LongIdentifier(&yylloc, yytext);
				strncpy(yylval.identifier, yytext, MaxIdentLen);
				yylval.identifier[MaxIdentLen] = '\0';
			 } else {
			 	strcpy(yylval.identifier, yytext);
			 }
			 return T_Identifier; 
			}
[ \t\n]+		{}
.			{ ReportError::UnrecogChar(&yylloc, *yytext); }
%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated lex.yy.c file.
 * This section is where you put definitions of helper functions.
 */


/* Function: InitScanner
 * ---------------------
 * This function will be called before any calls to yylex().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the scanner (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yy_flex_debug that controls whether flex prints debugging information
 * about each token and what rule was matched. If set to false, no information
 * is printed. Setting it to true will give you a running trail that might
 * be helpful when debugging your scanner. Please be sure the variable is
 * set to false when submitting your final version.
 */
void InitScanner()
{
	PrintDebug("lex", "Initializing scanner");
	yy_flex_debug = false;

	yylloc.first_line   = 1;
	yylloc.first_column = 1;
	yylloc.last_line    = 1;
	yylloc.last_column  = 0;
}
	

/* Function: DoBeforeEachAction()
 * ------------------------------
 * This function is installed as the YY_USER_ACTION. This is a place
 * to group code common to all actions.
 */
static void DoBeforeEachAction()
{
	yylloc.first_line   = yylloc.last_line;
	yylloc.first_column = yylloc.last_column + 1;

	if (yylloc.last_column == 0)
		yylloc.first_column = 1;

	int i;

	for (i = 0; i < yyleng; i++) {
		AdvanceLocation(yytext[i]);
	}
}
