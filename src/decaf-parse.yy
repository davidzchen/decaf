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
#include "errors.h"
#include "scanner.h" // for yylex
#include "dcc.h"


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
    int              integerConstant;
    bool             boolConstant;
    char             *stringConstant;
    double           doubleConstant;
    char             identifier[MaxIdentLen+1];
    Decl             *decl;
    List<Decl*>      *declList;
    VarDecl          *varDecl;
    ClassDecl        *classDecl;
    InterfaceDecl    *interfaceDecl;
    FnDecl           *fnDecl;
    Type             *type;
    NamedType        *namedType;
    ArrayType        *arrayType;
    List<NamedType*> *implementsTypeList;
    List<VarDecl*>   *varDeclList;
    StmtBlock        *stmtBlock;
    List<Stmt*>      *stmtList;
    Stmt             *stmt;
    WhileStmt        *whileStmt;
    ReturnStmt       *returnStmt;
    PrintStmt        *printStmt;
    BreakStmt        *breakStmt;
    ForStmt          *forStmt;
    IfStmt           *ifStmt;
    Expr             *expr;
    List<Expr*>      *exprList;
    AssignExpr       *assignExpr;
    FieldAccess      *fieldAccess;
    NewExpr          *newExpr;
    ReadIntegerExpr  *readIntegerExpr;
    ReadLineExpr     *readLineExpr;
    NewArrayExpr     *newArrayExpr;
    SwitchStmt       *switchStmt;
    CaseStmt         *caseStmt;
    List<CaseStmt*>  *caseStmtList;
    DefaultStmt      *defaultStmt;
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
%token T_Switch T_Case T_Default T_Incr T_Decr

%token <identifier> T_Identifier
%token <stringConstant> T_StringConstant 
%token <integerConstant> T_IntConstant
%token <doubleConstant> T_DoubleConstant
%token <boolConstant> T_BoolConstant

%nonassoc NOELSE
%nonassoc T_Else
%nonassoc NOMETHOD
%nonassoc EMPTYCASE
%nonassoc EMPTYDEFAULT
%nonassoc NONEMPTYCASE
%nonassoc NONEMPTYDEFAULT
%right '('
%left T_Or
%left T_And
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
%right '*'
%right T_Incr
%right T_Decr
%right NEG
%right '!'

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
 
%type <declList>        DeclList FieldList PrototypeList
%type <decl>            Decl
%type <type>            Type
%type <varDecl>         VarDecl Variable
%type <classDecl>       ClassDecl
%type <interfaceDecl>   InterfaceDecl
%type <fnDecl>          FnDecl Prototype FnDef
%type <namedType>       ClassExtends NamedType
%type <implementsTypeList> ImplementsTypeList ClassImplements
%type <varDeclList>     FormalsList VarDeclList
%type <stmtBlock>       StmtBlock
%type <stmtList>        StmtList
%type <stmt>            Stmt
%type <whileStmt>       WhileStmt
%type <returnStmt>      ReturnStmt
%type <printStmt>       PrintStmt
%type <breakStmt>       BreakStmt
%type <forStmt>         ForStmt
%type <ifStmt>          IfStmt
%type <expr>            Expr ExprStmt AssignExpr UnaryExpr LValue
			PrimaryExpr Constant LogicalExpr RelationalExpr
			EqualityExpr AdditiveExpr MultiplicativeExpr
%type <exprList>        ExprList
%type <readIntegerExpr> ReadIntegerExpr
%type <readLineExpr>    ReadLineExpr
%type <newExpr>         NewExpr
%type <newArrayExpr>    NewArrayExpr
%type <switchStmt>      SwitchStmt
%type <caseStmt>        CaseStmt
%type <caseStmtList>    CaseStmtList
%type <defaultStmt>     DefaultStmt

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
				    {
				      //program->Print(0);
				      
				      /*
				       * pp3: if no errors, check program
				       */
				      program->Check();
				    }
                        	}
	;

DeclList  
	: DeclList Decl		{ ($$ = $1)->Append($2); }
	| Decl			{ ($$ = new List<Decl*>)->Append($1); }
	;

Decl      
	: VarDecl		{ $$ = $1; }
	| ClassDecl		{ $$ = $1; }
	| InterfaceDecl		{ $$ = $1; }
	| FnDecl		{ $$ = $1; }
	;

VarDecl   
	: Variable ';'		{ $$ = $1; }
	;

Variable
	: Type T_Identifier	{
	                          Identifier *i = new Identifier(@2, $2);
	                          $$ = new VarDecl(i, $1); 
	                        }
	;

Type      
	: T_Void		{ $$ = Type::voidType; }
	| T_Bool		{ $$ = Type::boolType; }
	| T_Int			{ $$ = Type::intType; }
	| T_Double		{ $$ = Type::doubleType; }
	| T_String		{ $$ = Type::stringType; }
	| NamedType		{ $$ = $1; } 
	| Type T_Dims		{ $$ = new ArrayType(@1, $1); }
	;

NamedType
	: T_Identifier		{ 
				  Identifier *i = new Identifier(@1, $1);
				  $$ = new NamedType(i); 
				}
	;

ClassDecl 
	: T_Class T_Identifier ClassExtends ClassImplements '{' FieldList '}' {
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new ClassDecl(i, $3, $4, $6);
				}
	| T_Class T_Identifier ClassExtends ClassImplements '{' '}' {
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new ClassDecl(i, $3, $4, new List<Decl*>);
				}
	;

ClassExtends
	: T_Extends T_Identifier { 
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new NamedType(i); 
				}
	| /* empty */		{ $$ = NULL; }
	;
	
ClassImplements
	: T_Implements ImplementsTypeList { 
				  $$ = $2; 
				}
	| /* empty */		{ $$ = new List<NamedType*>; }
	;
	
ImplementsTypeList
	: ImplementsTypeList ',' T_Identifier { 
				  Identifier *i = new Identifier(@3, $3);
				  NamedType *t = new NamedType(i);
				  ($$ = $1)->Append(t); 
				}
	| T_Identifier		{ 
				  Identifier *i = new Identifier(@1, $1);
				  NamedType *t = new NamedType(i);
				  ($$ = new List<NamedType*>)->Append(t); 
				}
	;

InterfaceDecl
	: T_Interface T_Identifier '{' PrototypeList '}' {
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new InterfaceDecl(i, $4);
				}
	;
	
FnDecl
	: FnDef	StmtBlock	{ 
				  FnDecl *f = $1;
				  f->SetFunctionBody($2);
				}
	;
	
FieldList
	: FieldList VarDecl	{ ($$ = $1)->Append($2); }
	| FieldList FnDecl	{ ($$ = $1)->Append($2); }
	| VarDecl		{ ($$ = new List<Decl*>)->Append($1); }
	| FnDecl		{ ($$ = new List<Decl*>)->Append($1); }
	;

FormalsList
	: Variable 		{ ($$ = new List<VarDecl*>)->Append($1); }
	| FormalsList ',' Variable {
				  ($$ = $1)->Append($3);
				}
	;

Prototype     
	: FnDef ';' 		{ $$ = $1; }
	;

FnDef
	: Type T_Identifier '(' FormalsList ')' {
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new FnDecl(i, $1, $4);
				}
	| Type T_Identifier '(' ')' {
				  Identifier *i = new Identifier(@2, $2);
				  $$ = new FnDecl(i, $1, new List<VarDecl*>);
				}
	;

PrototypeList
	: PrototypeList Prototype {
				  ($$ = $1)->Append($2);
				}
	| Prototype		{ ($$ = new List<Decl*>)->Append($1); }
	;

StmtBlock
	: '{' VarDeclList StmtList '}'	{
				  $$ = new StmtBlock($2, $3);
				}
	| '{' VarDeclList '}'	{ $$ = new StmtBlock($2, new List<Stmt*>); }
	| '{' StmtList '}' 	{ $$ = new StmtBlock(new List<VarDecl*>, $2); }
	| '{' '}'		{ 
				  $$ = new StmtBlock(new List<VarDecl*>,
				  		     new List<Stmt*>);
				}
	;

StmtList
	: StmtList Stmt		{ ($$ = $1)->Append($2); }
	| Stmt			{ ($$ = new List<Stmt*>)->Append($1); }
	;

VarDeclList
	: VarDeclList VarDecl	{ ($$ = $1)->Append($2); }
	| VarDecl		{ ($$ = new List<VarDecl*>)->Append($1); }
	;

Stmt
	: ExprStmt		{ $$ = $1; }
	| WhileStmt		{ $$ = $1; }
	| ReturnStmt		{ $$ = $1; }
	| BreakStmt		{ $$ = $1; }
	| PrintStmt		{ $$ = $1; }
	| ForStmt		{ $$ = $1; }
	| IfStmt		{ $$ = $1; }
	| SwitchStmt            { $$ = $1; }
	| StmtBlock		{ $$ = $1; }
	;

SwitchStmt
	: T_Switch '(' Expr ')' '{' CaseStmtList DefaultStmt '}' {
				  $$ = new SwitchStmt($3, $6, $7);
				}
	;

CaseStmtList
	: CaseStmtList CaseStmt { ($$ = $1)->Append($2); }
	| CaseStmt		{ ($$ = new List<CaseStmt*>)->Append($1); }
	;

CaseStmt
	: T_Case T_IntConstant ':' StmtList %prec NONEMPTYCASE { 
				  IntConstant *ic = new IntConstant(@2, $2);
				  $$ = new CaseStmt(ic, $4);
				}
	| T_Case T_IntConstant ':' %prec EMPTYCASE {
				  IntConstant *ic = new IntConstant(@2, $2);
				  $$ = new CaseStmt(ic, new List<Stmt*>);
				}
	;
	
DefaultStmt
	: T_Default ':' StmtList %prec NONEMPTYDEFAULT { 
				  $$ = new DefaultStmt($3);
				}
	| T_Default ':' %prec EMPTYDEFAULT { 
				  $$ = new DefaultStmt(new List<Stmt*>);
				}
	;

WhileStmt
	: T_While '(' Expr ')' Stmt {
				  $$ = new WhileStmt($3, $5);
				}
	;

BreakStmt
	: T_Break ';'		{ $$ = new BreakStmt(@1); }
	;

PrintStmt
	: T_Print '(' ExprList ')' ';' {
				  $$ = new PrintStmt($3);
				}
	;
	
ReturnStmt
	: T_Return ';'		{ $$ = new ReturnStmt(@1, new EmptyExpr); }
	| T_Return Expr ';' {
				  $$ = new ReturnStmt(@1, $2);
				}
	;
	
ForStmt
	: T_For '(' ExprStmt ExprStmt ')' Stmt {
				  $$ = new ForStmt($3, $4, new EmptyExpr, $6);
				}
	| T_For '(' ExprStmt ExprStmt Expr ')' Stmt {
				  $$ = new ForStmt($3, $4, $5, $7);
				}
	;
	
ExprStmt
	: Expr ';'              { $$ = $1; }
	| ';'			{ $$ = new EmptyExpr; }
	;

IfStmt
	: T_If '(' Expr ')' Stmt %prec NOELSE {
				  $$ = new IfStmt($3, $5, NULL);
				}
	| T_If '(' Expr ')' Stmt T_Else Stmt {
				  $$ = new IfStmt($3, $5, $7);
				}
	;

ExprList
	: ExprList ',' Expr	{ ($$ = $1)->Append($3); }
	| Expr			{ ($$ = new List<Expr*>)->Append($1); }
	;
	
Expr
	: AssignExpr            { $$ = $1; } 
	;

AssignExpr
	: LogicalExpr		{ $$ = $1; }
	| ReadIntegerExpr	{ $$ = $1; }
	| ReadLineExpr		{ $$ = $1; }
	| NewExpr		{ $$ = $1; }
	| NewArrayExpr		{ $$ = $1; }
	| LValue '=' AssignExpr	{ Operator *op = new Operator(@2, "=");
				  $$ = new AssignExpr($1, op, $3);
				}
	;

ReadIntegerExpr
	: T_ReadInteger '(' ')'	{ $$ = new ReadIntegerExpr(@1); }
	;
	
ReadLineExpr
	: T_ReadLine '(' ')'	{ $$ = new ReadLineExpr(@1); }
	;
	
NewExpr
	: T_New NamedType	{ $$ = new NewExpr(@1, $2); }
	;
	
NewArrayExpr
	: T_NewArray '(' Expr ',' Type ')' {
				  $$ = new NewArrayExpr(@1, $3, $5);
				}
	;
	
LogicalExpr
	: RelationalExpr	{ $$ = $1; }
	| LogicalExpr T_Or RelationalExpr {
				  Operator *op = new Operator(@2, "||");
				  $$ = new LogicalExpr($1, op, $3);
				}
	| LogicalExpr T_And RelationalExpr {
				  Operator *op = new Operator(@2, "&&");
				  $$ = new LogicalExpr($1, op, $3);
				}
	;
	
RelationalExpr
	: EqualityExpr		{ $$ = $1; }
	| RelationalExpr '<' EqualityExpr {
				  Operator *op = new Operator(@2, "<");
				  $$ = new RelationalExpr($1, op, $3);
				}
	| RelationalExpr '>' EqualityExpr {
				  Operator *op = new Operator(@2, ">");
				  $$ = new RelationalExpr($1, op, $3);
				}
	| RelationalExpr T_GreaterEqual EqualityExpr {
				  Operator *op = new Operator(@2, ">=");
				  $$ = new RelationalExpr($1, op, $3);
				}
	| RelationalExpr T_LessEqual EqualityExpr {
				  Operator *op = new Operator(@2, "<=");
				  $$ = new RelationalExpr($1, op, $3);
				}
	;
	
EqualityExpr
	: AdditiveExpr		{ $$ = $1; }
	| EqualityExpr T_Equal AdditiveExpr {
				  Operator *op = new Operator(@2, "==");
				  $$ = new EqualityExpr($1, op, $3);
				}
	| EqualityExpr T_NotEqual AdditiveExpr {
				  Operator *op = new Operator(@2, "!=");
				  $$ = new EqualityExpr($1, op, $3);
				}
	;
	
AdditiveExpr
	: MultiplicativeExpr	{ $$ = $1; }
	| AdditiveExpr '+' MultiplicativeExpr {
				  Operator *op = new Operator(@2, "+");
				  $$ = new ArithmeticExpr($1, op, $3);
				}
	| AdditiveExpr '-' MultiplicativeExpr {
				  Operator *op = new Operator(@2, "-");
				  $$ = new ArithmeticExpr($1, op, $3);
				}
	;
	
MultiplicativeExpr
	: UnaryExpr		{ $$ = $1; }
	
	
	
	| MultiplicativeExpr '*' UnaryExpr {
				  Operator *op = new Operator(@2, "*");
				  $$ = new ArithmeticExpr($1, op, $3);
				}
	| MultiplicativeExpr '/' UnaryExpr {
				  Operator *op = new Operator(@2, "/");
				  $$ = new ArithmeticExpr($1, op, $3);
				}
	| MultiplicativeExpr '%' UnaryExpr {
				  Operator *op = new Operator(@2, "%");
				  $$ = new ArithmeticExpr($1, op, $3);
				}
	;
	
UnaryExpr
	: LValue		{ $$ = $1; }
	| '-' UnaryExpr %prec NEG {
				  Operator *op = new Operator(@1, "-");
				  $$ = new ArithmeticExpr(op, $2);
				}
	| '!' UnaryExpr		{
				  Operator *op = new Operator(@1, "!");
				  $$ = new LogicalExpr(op, $2);
				}
	| UnaryExpr T_Incr	{
				  Operator *op = new Operator(@2, "++");
				  $$ = new PostfixExpr($1, op);
				}
	| UnaryExpr T_Decr 	{
				  Operator *op = new Operator(@2, "--");
				  $$ = new PostfixExpr($1, op);
				}
	;
	
LValue
	: PrimaryExpr		{ $$ = $1; }
	| LValue '[' Expr ']'	{ $$ = new ArrayAccess(@1, $1, $3); }
	| T_Identifier '(' ')'	{ 
				  Identifier *id = new Identifier(@1, $1);
				  $$ = new Call(@1, NULL, id, new List<Expr*>); 
				}
	| T_Identifier '(' ExprList ')' {
				  Identifier *id = new Identifier(@1, $1);
				  $$ = new Call(@1, NULL, id, $3);
				}
	| LValue '.' T_Identifier %prec NOMETHOD {
				  Identifier *id = new Identifier(@3, $3);
				  $$ = new FieldAccess($1, id);
				}
	| LValue '.' T_Identifier '(' ')' { 
				  Identifier *id = new Identifier(@3, $3);
				  $$ = new Call(@1, $1, id, new List<Expr*>);
				}
	| LValue '.' T_Identifier '(' ExprList ')' {
				  Identifier *id = new Identifier(@3, $3);
				  $$ = new Call(@1, $1, id, $5);
				}
	;

PrimaryExpr
	: T_Identifier		{ Identifier *id = new Identifier(@1, $1);
				  $$ = new FieldAccess(NULL, id); 
				}
	| T_This		{ $$ = new This(@1); }
	| Constant		{ $$ = $1; }
	| '(' Expr ')'		{ $$ = $2; }
	;

Constant
	: T_IntConstant		{ $$ = new IntConstant(@1, $1); }
	| T_DoubleConstant	{ $$ = new DoubleConstant(@1, $1); }
	| T_BoolConstant	{ $$ = new BoolConstant(@1, $1); }
	| T_StringConstant	{ $$ = new StringConstant(@1, $1); }
	| T_Null		{ $$ = new NullConstant(@1); }
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
