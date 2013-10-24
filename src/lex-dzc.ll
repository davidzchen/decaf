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
#include <vector>

#include <utility.h> // for PrintDebug()
#include <errors.h>
#include <scanner.h>
#include <parse.h>

using namespace std;

#define TAB_SIZE 8

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

string tmp_string;
struct yyltype tmp_loc;

%}

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later. 
  */

Z_DDIGIT		[0-9]
Z_XDIGIT		[0-9a-fA-F]
Z_IDENTIFIER		[a-zA-Z][a-zA-Z0-9_]*
Z_ONEOP			[\+\-\*/;\{\}\[\]\.%=\(\)\<\>!\,]
Z_DINTCONSTANT		{Z_DDIGIT}+
Z_XINTCONSTANT		0[xX]{Z_XDIGIT}+
Z_DOUBLECONSTANT	{Z_DDIGIT}+"."{Z_DDIGIT}*([eE][\+\-]?{Z_DDIGIT}+)?


%%             /* BEGIN RULES SECTION */
 /* All patterns and actions should be placed between the start and stop
  * %% markers which delimit the Rules section.
  */ 

"//".*$			{}
"/*"			{
			int c;
			
			for ( ; ; ) {
				while ((c = yyinput()) != '*' && c != EOF && c != 0) {
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
				if (c == EOF || c == 0) {
					ReportError::UntermComment();
					break;
				}	
			}
			}
\"			{
			int c, i;

			tmp_string = yytext;
			for ( ; ; ) {
				while ((c = yyinput()) != '"' && c != '\n' && c != EOF && c != 0) {
					AdvanceLocation(c);
					tmp_string.append(1, c);
				}
				if (c == '"') {
					AdvanceLocation(c);
					tmp_string.append(1, c);
					yytext = (char *) tmp_string.c_str();
					yylval.stringConstant = new char[tmp_string.size() + 1];
					strcpy(yylval.stringConstant, tmp_string.c_str());
					return T_StringConstant;
				}
				if (c == '\n' || c == EOF || c == 0) {
					yytext = (char *) tmp_string.c_str();
					ReportError::UntermString(&yylloc, yytext);
					unput(c);
					break;
				}
			}
			}
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

/*	printf("called firstline: %d firstcol %d lastline %d lastcol %d\n",
	       yylloc.first_line,
	       yylloc.first_column,
	       yylloc.last_line,
	       yylloc.last_column); */
}

const char *GetLineNumbered(int num)
{
	return NULL;
}
