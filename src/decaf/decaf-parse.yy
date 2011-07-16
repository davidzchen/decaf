/* File: parser.y
 * --------------
 * Bison input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parse.h"
#include <errors.h>

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
 
%token T_Void T_Bool T_Int T_Double T_String T_Class 
%token T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token T_While T_For T_If T_Else T_Return T_Break
%token T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token <identifier> T_Identifier
%token <stringConstant> T_StringConstant 
%token <integerConstant> T_IntConstant
%token <doubleConstant> T_DoubleConstant
%token <boolConstant> T_BoolConstant

%nonassoc NOELSE
%nonassoc T_Else
%left T_Equal
%left T_NotEqual
%left '<'
%left '>'
%left T_LessEqual
%left T_GreaterEqual
%left '-'
%left '+'
%left '%'
%left '/'
%left '*'



/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList>  DeclList 
%type <decl>      Decl


%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   
	: DeclList		{
				  @1;
				  /* pp2: The @1 is needed to convince 
				   * yacc to set up yylloc. You can remove 
				   * it once you have other uses of @n*/
				  Program *program = new Program($1);
				  // if no errors, advance to next phase
				  if (ReportError::NumErrors() == 0) 
					program->Print(0);
                        	}
	;

DeclList  
	: DeclList Decl		{ ($$ = $1)->Append($2); }
	| Decl			{ ($$ = new List<Decl*>)->Append($1); }
	;

Decl      
	: VarDecl		{ /*$$ = new VarDecl*/ }
	| ClassDecl		{}
	| InterfaceDecl		{}
	| FnDecl		{}
	;

VarDecl   
	: Variable ';'		{ /*$$ = $1;*/ }
	;

Variable  
	: Type T_Identifier	{ /*$$ = new VarDecl($2, $1);*/ }
	;

Type      
	: T_Void		{ /*$$ = Type::voidType;*/ }
	| T_Bool		{ /*$$ = Type::boolType;*/ }
	| T_Int			{ /*$$ = Type::intType;*/ }
	| T_Double		{ /*$$ = Type::doubleType;*/ }
	| T_String		{ /*$$ = Type::stringType;*/ }
	| T_Identifier		{ /*$$ = new NamedType($1);*/ }
	| Type T_Dims		{ /*$$ = new ArrayType(yylloc, $1);*/ }
	;

ClassDecl 
	: T_Class T_Identifier ClassExtends ClassImplements '{' FieldList '}' {}
	;

ClassExtends
	: T_Extends T_Identifier {}
	| /* empty */
	;
	
ClassImplements
	: T_Implements IdentifierList {}
	| /* empty */
	;

InterfaceDecl
	: T_Interface T_Identifier '{' PrototypeList '}' {}
	;
	
FnDecl
	: FnDef	StmtBlock	{}
	;
	
FieldList
	: FieldList VarDecl	{}
	| FieldList Prototype	{}
	| /* empty */
	;

FormalsList
	: Variable 		{}
	| FormalsList ',' Variable {}
	| /* empty */
	;

Prototype     
	: FnDef ';' {}
	;

FnDef
	: Type T_Identifier '(' FormalsList ')' {}
	;

PrototypeList
	: PrototypeList Prototype {}
	| Prototype		{}
	;

IdentifierList
	: IdentifierList T_Identifier {}
	| T_Identifier		{}
	;

StmtBlock
	: '{' StmtList '}'	{}
	| '{' '}'		{}
	;

StmtList
	: StmtList VarDecl	{}
	| StmtList Stmt		{}
	| Stmt			{}
	| VarDecl		{}
	;
	
Stmt
	: ExprStmt		{}
	| WhileStmt		{}
	| ReturnStmt		{}
	| BreakStmt		{}
	| PrintStmt		{}
	| ForStmt		{}
	| IfStmt		{}
	| StmtBlock		{}
	;
	
WhileStmt
	: T_While '(' BinaryExpr ')' Stmt {}
	;

BreakStmt
	: T_Break ';'		{}
	;
	
PrintStmt
	: T_Print '(' ExprList ')' ';' {}
	;
	
ReturnStmt
	: T_Return ';'		{}
	| T_Return AssignExpr ';' {}
	;
	
ForStmt
	: T_For '(' ExprStmt ExprStmt ')' Stmt {}
	| T_For '(' ExprStmt ExprStmt PrimaryExpr ')' Stmt {}
	;
	
ExprStmt
	: PrimaryExpr ';'	{}
	| ';'			{}
	;

IfStmt
	: T_If '(' BinaryExpr ')' Stmt %prec NOELSE {}
	| T_If '(' BinaryExpr ')' Stmt T_Else Stmt {}
	;
	
Expr
	: Constant		{}
	| '(' PrimaryExpr ')'	{}
	;

ExprList
	: Expr			{}
	| ExprList ',' Expr	{}
	;

PrimaryExpr
	: AssignExpr		{}
	| PrimaryExpr ',' AssignExpr {}
	;

AssignExpr
	: BinaryExpr		{}
	| ReadIntegerExpr	{}
	| ReadLineExpr		{}
	| NewExpr		{}
	| NewArrayExpr		{}
	| LValue '=' AssignExpr {}
	;
	
ReadIntegerExpr
	: T_ReadInteger '(' ')'	{}
	;
	
ReadLineExpr
	: T_ReadLine '(' ')'	{}
	;
	
NewExpr
	: T_New T_Identifier	{}
	;
	
NewArrayExpr
	: T_NewArray '(' BinaryExpr ',' Type ')' {}
	;
	
BinaryExpr
	: UnaryExpr		{}
	| BinaryExpr T_Or UnaryExpr {}
	| BinaryExpr T_And UnaryExpr {}
	| BinaryExpr '<' UnaryExpr {}
	| BinaryExpr '>' UnaryExpr {}
	| BinaryExpr T_GreaterEqual UnaryExpr {}
	| BinaryExpr T_LessEqual UnaryExpr {}
	| BinaryExpr T_Equal UnaryExpr {}
	| BinaryExpr T_NotEqual UnaryExpr {}
	| BinaryExpr '+' UnaryExpr {}
	| BinaryExpr '-' UnaryExpr {}
	| BinaryExpr '*' UnaryExpr {}
	| BinaryExpr '/' UnaryExpr {}
	| BinaryExpr '%' UnaryExpr {}
	;
	
UnaryExpr
	: LValue		{}
	| Constant		{}
	| '-' UnaryExpr		{}
	| '!' UnaryExpr		{}
	;
	
LValue
	: T_Identifier		{}
	| T_This		{}
	| LValue '[' PrimaryExpr ']' {}
	| LValue '(' ')'	{}
	| LValue '(' ExprList ')' {}
	| LValue '.' T_Identifier {}
	;
	
Constant
	: T_IntConstant		{}
	| T_DoubleConstant	{}
	| T_BoolConstant	{}
	| T_StringConstant	{}
	| T_Null		{}
	;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
