/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_Void = 258,
     T_Bool = 259,
     T_Int = 260,
     T_Double = 261,
     T_String = 262,
     T_Class = 263,
     T_LessEqual = 264,
     T_GreaterEqual = 265,
     T_Equal = 266,
     T_NotEqual = 267,
     T_Dims = 268,
     T_And = 269,
     T_Or = 270,
     T_Null = 271,
     T_Extends = 272,
     T_This = 273,
     T_Interface = 274,
     T_Implements = 275,
     T_While = 276,
     T_For = 277,
     T_If = 278,
     T_Else = 279,
     T_Return = 280,
     T_Break = 281,
     T_New = 282,
     T_NewArray = 283,
     T_Print = 284,
     T_ReadInteger = 285,
     T_ReadLine = 286,
     T_Switch = 287,
     T_Case = 288,
     T_Default = 289,
     T_Incr = 290,
     T_Decr = 291,
     T_Identifier = 292,
     T_StringConstant = 293,
     T_IntConstant = 294,
     T_DoubleConstant = 295,
     T_BoolConstant = 296,
     NOELSE = 297,
     NOMETHOD = 298,
     EMPTYCASE = 299,
     EMPTYDEFAULT = 300,
     NONEMPTYCASE = 301,
     NONEMPTYDEFAULT = 302,
     NEG = 303
   };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Switch 287
#define T_Case 288
#define T_Default 289
#define T_Incr 290
#define T_Decr 291
#define T_Identifier 292
#define T_StringConstant 293
#define T_IntConstant 294
#define T_DoubleConstant 295
#define T_BoolConstant 296
#define NOELSE 297
#define NOMETHOD 298
#define EMPTYCASE 299
#define EMPTYDEFAULT 300
#define NONEMPTYCASE 301
#define NONEMPTYDEFAULT 302
#define NEG 303




/* Copy the first part of user declarations.  */
#line 11 "latte-parse.yy"


/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
 
#include <config.h>
#include "errors.h"
#include "scanner.h" // for yylex
#include "ltc.h"


void yyerror(const char *msg); // standard error-handling routine



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 44 "latte-parse.yy"
{
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
/* Line 193 of yacc.c.  */
#line 251 "latte-parse.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 276 "latte-parse.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNRULES -- Number of states.  */
#define YYNSTATES  225

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,    53,     2,     2,
      48,    62,    55,    52,    61,    51,    67,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    58,
      49,    64,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    65,     2,    66,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      21,    24,    26,    28,    30,    32,    34,    36,    39,    41,
      49,    56,    59,    60,    63,    64,    67,    69,    75,    78,
      81,    84,    86,    88,    90,    94,    97,   103,   108,   111,
     113,   118,   122,   126,   129,   132,   134,   137,   139,   141,
     143,   145,   147,   149,   151,   153,   155,   157,   166,   169,
     171,   176,   180,   184,   187,   193,   196,   202,   205,   209,
     216,   224,   227,   229,   235,   243,   247,   249,   251,   253,
     255,   257,   259,   261,   265,   269,   273,   276,   283,   285,
     289,   293,   295,   299,   303,   307,   311,   313,   317,   321,
     323,   327,   331,   333,   337,   341,   345,   347,   350,   353,
     356,   359,   361,   366,   370,   375,   379,   385,   392,   394,
     396,   398,   402,   404,   406,   408,   410
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    70,    -1,    70,    71,    -1,    71,    -1,
      72,    -1,    76,    -1,    80,    -1,    81,    -1,    73,    58,
      -1,    74,    37,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,    75,    -1,    74,    13,    -1,    37,
      -1,     8,    37,    77,    78,    59,    82,    60,    -1,     8,
      37,    77,    78,    59,    60,    -1,    17,    37,    -1,    -1,
      20,    79,    -1,    -1,    79,    37,    -1,    37,    -1,    19,
      37,    59,    86,    60,    -1,    85,    87,    -1,    82,    72,
      -1,    82,    81,    -1,    72,    -1,    81,    -1,    73,    -1,
      83,    61,    73,    -1,    85,    58,    -1,    74,    37,    48,
      83,    62,    -1,    74,    37,    48,    62,    -1,    86,    84,
      -1,    84,    -1,    59,    89,    88,    60,    -1,    59,    89,
      60,    -1,    59,    88,    60,    -1,    59,    60,    -1,    88,
      90,    -1,    90,    -1,    89,    72,    -1,    72,    -1,   100,
      -1,    95,    -1,    98,    -1,    96,    -1,    97,    -1,    99,
      -1,   101,    -1,    91,    -1,    87,    -1,    32,    48,   103,
      62,    59,    92,    94,    60,    -1,    92,    93,    -1,    93,
      -1,    33,    39,    63,    88,    -1,    33,    39,    63,    -1,
      34,    63,    88,    -1,    34,    63,    -1,    21,    48,   103,
      62,    90,    -1,    26,    58,    -1,    29,    48,   102,    62,
      58,    -1,    25,    58,    -1,    25,   103,    58,    -1,    22,
      48,   100,   100,    62,    90,    -1,    22,    48,   100,   100,
     103,    62,    90,    -1,   103,    58,    -1,    58,    -1,    23,
      48,   103,    62,    90,    -1,    23,    48,   103,    62,    90,
      24,    90,    -1,   102,    61,   103,    -1,   103,    -1,   104,
      -1,   109,    -1,   105,    -1,   106,    -1,   107,    -1,   108,
      -1,   115,    64,   104,    -1,    30,    48,    62,    -1,    31,
      48,    62,    -1,    27,    75,    -1,    28,    48,   103,    61,
      74,    62,    -1,   110,    -1,   109,    15,   110,    -1,   109,
      14,   110,    -1,   111,    -1,   110,    49,   111,    -1,   110,
      50,   111,    -1,   110,    10,   111,    -1,   110,     9,   111,
      -1,   112,    -1,   111,    11,   112,    -1,   111,    12,   112,
      -1,   113,    -1,   112,    52,   113,    -1,   112,    51,   113,
      -1,   114,    -1,   113,    55,   114,    -1,   113,    54,   114,
      -1,   113,    53,   114,    -1,   115,    -1,    51,   114,    -1,
      57,   114,    -1,   114,    35,    -1,   114,    36,    -1,   116,
      -1,   115,    65,   103,    66,    -1,    37,    48,    62,    -1,
      37,    48,   102,    62,    -1,   115,    67,    37,    -1,   115,
      67,    37,    48,    62,    -1,   115,    67,    37,    48,   102,
      62,    -1,    37,    -1,    18,    -1,   117,    -1,    48,   103,
      62,    -1,    39,    -1,    40,    -1,    41,    -1,    38,    -1,
      16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   183,   183,   203,   204,   208,   209,   210,   211,   215,
     219,   226,   227,   228,   229,   230,   231,   232,   236,   243,
     247,   254,   258,   262,   265,   269,   274,   282,   289,   296,
     297,   298,   299,   303,   304,   310,   314,   318,   325,   328,
     332,   335,   336,   337,   344,   345,   349,   350,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   366,   372,   373,
     377,   381,   388,   391,   397,   403,   407,   413,   414,   420,
     423,   429,   430,   434,   437,   443,   444,   448,   452,   453,
     454,   455,   456,   457,   463,   467,   471,   475,   481,   482,
     486,   493,   494,   498,   502,   506,   513,   514,   518,   525,
     526,   530,   537,   541,   545,   549,   556,   557,   561,   565,
     569,   576,   577,   578,   582,   586,   590,   594,   601,   604,
     605,   606,   610,   611,   612,   613,   614
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Switch", "T_Case", "T_Default", "T_Incr", "T_Decr",
  "T_Identifier", "T_StringConstant", "T_IntConstant", "T_DoubleConstant",
  "T_BoolConstant", "NOELSE", "NOMETHOD", "EMPTYCASE", "EMPTYDEFAULT",
  "NONEMPTYCASE", "NONEMPTYDEFAULT", "'('", "'<'", "'>'", "'-'", "'+'",
  "'%'", "'/'", "'*'", "NEG", "'!'", "';'", "'{'", "'}'", "','", "')'",
  "':'", "'='", "'['", "']'", "'.'", "$accept", "Program", "DeclList",
  "Decl", "VarDecl", "Variable", "Type", "NamedType", "ClassDecl",
  "ClassExtends", "ClassImplements", "ImplementsTypeList", "InterfaceDecl",
  "FnDecl", "FieldList", "FormalsList", "Prototype", "FnDef",
  "PrototypeList", "StmtBlock", "StmtList", "VarDeclList", "Stmt",
  "SwitchStmt", "CaseStmtList", "CaseStmt", "DefaultStmt", "WhileStmt",
  "BreakStmt", "PrintStmt", "ReturnStmt", "ForStmt", "ExprStmt", "IfStmt",
  "ExprList", "Expr", "AssignExpr", "ReadIntegerExpr", "ReadLineExpr",
  "NewExpr", "NewArrayExpr", "LogicalExpr", "RelationalExpr",
  "EqualityExpr", "AdditiveExpr", "MultiplicativeExpr", "UnaryExpr",
  "LValue", "PrimaryExpr", "Constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,    40,    60,
      62,    45,    43,    37,    47,    42,   303,    33,    59,   123,
     125,    44,    41,    58,    61,    91,    93,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    70,    71,    71,    71,    71,    72,
      73,    74,    74,    74,    74,    74,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    81,    82,
      82,    82,    82,    83,    83,    84,    85,    85,    86,    86,
      87,    87,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    92,    92,
      93,    93,    94,    94,    95,    96,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   104,   104,
     104,   104,   104,   104,   105,   106,   107,   108,   109,   109,
     109,   110,   110,   110,   110,   110,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     116,   116,   117,   117,   117,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     7,
       6,     2,     0,     2,     0,     2,     1,     5,     2,     2,
       2,     1,     1,     1,     3,     2,     5,     4,     2,     1,
       4,     3,     3,     2,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     8,     2,     1,
       4,     3,     3,     2,     5,     2,     5,     2,     3,     6,
       7,     2,     1,     5,     7,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     2,     6,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       2,     1,     4,     3,     4,     3,     5,     6,     1,     1,
       1,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,    12,    13,    14,    15,     0,     0,    18,     0,
       2,     4,     5,     0,     0,    16,     6,     7,     8,     0,
      22,     0,     1,     3,     9,    17,    10,     0,    28,     0,
      24,     0,     0,   126,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   125,   122,   123,
     124,     0,     0,     0,    72,    43,    47,     0,    56,     0,
       0,    45,    55,    49,    51,    52,    50,    53,    48,    54,
       0,    77,    79,    80,    81,    82,    78,    88,    91,    96,
      99,   102,   106,   111,   120,    21,     0,     0,     0,    39,
       0,     0,    37,    33,     0,     0,     0,     0,   118,    67,
       0,    65,    86,     0,     0,     0,     0,     0,     0,     0,
     107,   106,   108,    10,    42,    44,    41,    46,     0,    71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   109,   110,     0,     0,     0,    26,    23,
       0,     0,    35,    27,    38,     0,    36,     0,     0,     0,
      68,     0,     0,    76,    84,    85,     0,   113,     0,   121,
      40,    90,    89,    95,    94,    92,    93,    97,    98,   101,
     100,   105,   104,   103,    83,     0,   115,    25,    20,    31,
      32,     0,    34,     0,     0,     0,     0,     0,     0,     0,
     114,   112,     0,    19,    29,    30,    64,     0,     0,    73,
       0,    75,    66,     0,   116,     0,    69,     0,     0,    87,
       0,     0,    59,   117,    70,    74,     0,     0,    58,     0,
      61,    63,    57,    60,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    30,
      87,   139,    17,    18,   181,    94,    89,    19,    91,    58,
      59,    60,    61,    62,   211,   212,   219,    63,    64,    65,
      66,    67,    68,    69,   152,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -127
static const yytype_int16 yypact[] =
{
     571,  -127,  -127,  -127,  -127,  -127,    -9,    -6,  -127,    37,
     571,  -127,  -127,    -7,    16,  -127,  -127,  -127,  -127,    -1,
      79,    42,  -127,  -127,  -127,  -127,    75,   163,  -127,    88,
     131,   124,    35,  -127,  -127,   104,   106,   107,   464,    98,
     122,   123,   132,   134,   135,   139,    63,  -127,  -127,  -127,
    -127,   532,     9,     9,  -127,  -127,  -127,    17,  -127,   340,
     212,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
     114,  -127,  -127,  -127,  -127,  -127,    76,    58,    87,    61,
     -10,    74,   -41,  -127,  -127,  -127,   160,   140,    19,  -127,
     147,    15,  -127,  -127,    53,   532,   498,   532,   150,  -127,
     148,  -127,  -127,   532,   532,   145,   151,   532,   246,   162,
    -127,   -32,  -127,  -127,  -127,  -127,  -127,  -127,   385,  -127,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,  -127,  -127,   532,   532,   172,  -127,   173,
     136,    75,  -127,  -127,  -127,   124,  -127,   164,   498,   165,
    -127,   168,    56,  -127,  -127,  -127,   170,  -127,    60,  -127,
    -127,    58,    58,    87,    87,    87,    87,    61,    61,   -10,
     -10,    74,    74,    74,  -127,   146,   177,  -127,  -127,  -127,
    -127,   171,  -127,   430,   274,   430,   124,   532,   178,   186,
    -127,  -127,   302,  -127,  -127,  -127,  -127,   430,   184,   223,
       0,  -127,  -127,   215,  -127,    71,  -127,   430,   430,  -127,
     216,   101,  -127,  -127,  -127,  -127,   191,   193,  -127,   197,
     430,   430,  -127,   430,   430
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,   248,   -24,   -25,   -26,   219,  -127,  -127,
    -127,  -127,  -127,  -126,  -127,  -127,   174,   -20,  -127,   242,
     -58,  -127,   -59,  -127,  -127,    55,  -127,  -127,  -127,  -127,
    -127,  -127,   -84,  -127,  -100,   -34,   133,  -127,  -127,  -127,
    -127,  -127,    24,   -19,    10,    18,   -37,   -43,  -127,  -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int16 yytable[] =
{
     115,    57,   118,    56,   100,    88,    57,    93,   158,   111,
     111,    90,   148,    25,   180,   110,   112,   109,     1,     2,
       3,     4,     5,   135,   136,    33,   137,    34,    20,    25,
      25,    21,    25,   136,    57,   137,   117,    22,     1,     2,
       3,     4,     5,   130,   131,   132,    98,    47,    48,    49,
      50,    24,     8,    26,   113,   195,   141,    51,    27,   115,
      52,   147,   209,   149,   184,    88,    53,   122,   123,   151,
     153,    90,     8,   156,   153,   143,   -18,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     120,   121,   205,   171,   172,   173,    29,    92,   126,   127,
     -18,    31,   175,   163,   164,   165,   166,   124,   125,   133,
     134,   108,   128,   129,   145,   146,   179,   187,   188,    57,
     182,   187,   190,    32,   196,    85,   199,     1,     2,     3,
       4,     5,   187,   213,   210,   217,   167,   168,   206,     1,
       2,     3,     4,     5,   161,   162,   169,   170,   214,   215,
     198,    86,    95,   201,    96,    97,   101,   194,   153,     8,
     200,     8,   223,   224,   115,   115,     1,     2,     3,     4,
       5,   103,   119,     8,     1,     2,     3,     4,     5,    33,
     104,    34,   105,   106,    35,    36,    37,   107,    38,    39,
      40,    41,    42,    43,    44,    45,   178,   138,   108,   140,
      46,    47,    48,    49,    50,   142,   150,   154,     8,   176,
     177,    51,   191,   155,    52,     1,     2,     3,     4,     5,
      53,    54,    27,    55,   159,   192,   183,   185,    33,   186,
      34,   193,   189,    35,    36,    37,   202,    38,    39,    40,
      41,    42,    43,    44,    45,   203,   207,   208,   210,    46,
      47,    48,    49,    50,   220,   216,   221,   222,    23,   102,
      51,    28,    33,    52,    34,   144,   218,     0,   174,    53,
      54,    27,   116,    40,    41,     0,    43,    44,     0,     0,
       0,     0,     0,    98,    47,    48,    49,    50,     0,     0,
      33,     0,    34,     0,    51,     0,     0,    52,     0,     0,
       0,    40,    41,    53,    43,    44,     0,     0,   157,     0,
       0,    98,    47,    48,    49,    50,     0,     0,    33,     0,
      34,     0,    51,     0,     0,    52,     0,     0,     0,    40,
      41,    53,    43,    44,     0,     0,   197,     0,     0,    98,
      47,    48,    49,    50,     0,     0,     0,     0,     0,     0,
      51,     0,     0,    52,     0,     0,    33,     0,    34,    53,
       0,    35,    36,    37,   204,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,     0,     0,    98,    47,    48,
      49,    50,     0,     0,     0,     0,     0,     0,    51,     0,
       0,    52,     0,     0,     0,     0,     0,    53,    54,    27,
     114,    33,     0,    34,     0,     0,    35,    36,    37,     0,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
       0,     0,    98,    47,    48,    49,    50,     0,     0,     0,
       0,     0,     0,    51,     0,     0,    52,     0,     0,     0,
       0,     0,    53,    54,    27,   160,    33,     0,    34,     0,
       0,    35,    36,    37,     0,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,     0,     0,    98,    47,    48,
      49,    50,     0,     0,     0,     0,     0,     0,    51,     0,
      33,    52,    34,     0,     0,     0,     0,    53,    54,    27,
       0,    40,    41,     0,    43,    44,     0,     0,     0,     0,
       0,    98,    47,    48,    49,    50,     0,     0,     0,     0,
       0,     0,    51,     0,    33,    52,    34,     0,     0,     0,
       0,    53,    99,     0,     0,    40,    41,     0,    43,    44,
       0,     0,     0,     0,     0,    98,    47,    48,    49,    50,
       0,     0,     0,     0,     0,     0,    51,     0,    33,    52,
      34,     0,     0,     0,     0,    53,    54,     0,     0,    40,
      41,     0,    43,    44,     0,     0,     0,     0,     0,    98,
      47,    48,    49,    50,     1,     2,     3,     4,     5,     6,
      51,     0,     0,    52,     0,     0,     0,     0,     0,    53,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8
};

static const yytype_int16 yycheck[] =
{
      59,    27,    60,    27,    38,    31,    32,    32,   108,    52,
      53,    31,    96,    13,   140,    52,    53,    51,     3,     4,
       5,     6,     7,    64,    65,    16,    67,    18,    37,    13,
      13,    37,    13,    65,    60,    67,    60,     0,     3,     4,
       5,     6,     7,    53,    54,    55,    37,    38,    39,    40,
      41,    58,    37,    37,    37,   181,    37,    48,    59,   118,
      51,    95,    62,    97,   148,    91,    57,     9,    10,   103,
     104,    91,    37,   107,   108,    60,    13,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
      14,    15,   192,   130,   131,   132,    17,    62,    11,    12,
      37,    59,   136,   122,   123,   124,   125,    49,    50,    35,
      36,    48,    51,    52,    61,    62,   140,    61,    62,   145,
     145,    61,    62,    48,   183,    37,   185,     3,     4,     5,
       6,     7,    61,    62,    33,    34,   126,   127,   197,     3,
       4,     5,     6,     7,   120,   121,   128,   129,   207,   208,
     184,    20,    48,   187,    48,    48,    58,   181,   192,    37,
     186,    37,   220,   221,   223,   224,     3,     4,     5,     6,
       7,    48,    58,    37,     3,     4,     5,     6,     7,    16,
      48,    18,    48,    48,    21,    22,    23,    48,    25,    26,
      27,    28,    29,    30,    31,    32,    60,    37,    48,    59,
      37,    38,    39,    40,    41,    58,    58,    62,    37,    37,
      37,    48,    66,    62,    51,     3,     4,     5,     6,     7,
      57,    58,    59,    60,    62,    48,    62,    62,    16,    61,
      18,    60,    62,    21,    22,    23,    58,    25,    26,    27,
      28,    29,    30,    31,    32,    59,    62,    24,    33,    37,
      38,    39,    40,    41,    63,    39,    63,    60,    10,    40,
      48,    19,    16,    51,    18,    91,   211,    -1,   135,    57,
      58,    59,    60,    27,    28,    -1,    30,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,
      16,    -1,    18,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    27,    28,    57,    30,    31,    -1,    -1,    62,    -1,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    16,    -1,
      18,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    27,
      28,    57,    30,    31,    -1,    -1,    62,    -1,    -1,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    16,    -1,    18,    57,
      -1,    21,    22,    23,    62,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      60,    16,    -1,    18,    -1,    -1,    21,    22,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    16,    -1,    18,    -1,
      -1,    21,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      16,    51,    18,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    27,    28,    -1,    30,    31,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    16,    51,    18,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    27,    28,    -1,    30,    31,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    16,    51,
      18,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    27,
      28,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,     3,     4,     5,     6,     7,     8,
      48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    37,    69,
      70,    71,    72,    73,    74,    75,    76,    80,    81,    85,
      37,    37,     0,    71,    58,    13,    37,    59,    87,    17,
      77,    59,    48,    16,    18,    21,    22,    23,    25,    26,
      27,    28,    29,    30,    31,    32,    37,    38,    39,    40,
      41,    48,    51,    57,    58,    60,    72,    74,    87,    88,
      89,    90,    91,    95,    96,    97,    98,    99,   100,   101,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    37,    20,    78,    74,    84,
      85,    86,    62,    73,    83,    48,    48,    48,    37,    58,
     103,    58,    75,    48,    48,    48,    48,    48,    48,   103,
     114,   115,   114,    37,    60,    90,    60,    72,    88,    58,
      14,    15,     9,    10,    49,    50,    11,    12,    51,    52,
      53,    54,    55,    35,    36,    64,    65,    67,    37,    79,
      59,    37,    58,    60,    84,    61,    62,   103,   100,   103,
      58,   103,   102,   103,    62,    62,   103,    62,   102,    62,
      60,   110,   110,   111,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   114,   104,   103,    37,    37,    60,    72,
      81,    82,    73,    62,   100,    62,    61,    61,    62,    62,
      62,    66,    48,    60,    72,    81,    90,    62,   103,    90,
      74,   103,    58,    59,    62,   102,    90,    62,    24,    62,
      33,    92,    93,    62,    90,    90,    39,    34,    93,    94,
      63,    63,    60,    88,    88
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 183 "latte-parse.yy"
    {
				  (yylsp[(1) - (1)]);
				  /* pp2: The @1 is needed to convince 
				   * yacc to set up yylloc. You can remove 
				   * it once you have other uses of @n*/
				  Program *program = new Program((yyvsp[(1) - (1)].declList));
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
    break;

  case 3:
#line 203 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 4:
#line 204 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].decl)); }
    break;

  case 5:
#line 208 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].varDecl); }
    break;

  case 6:
#line 209 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].classDecl); }
    break;

  case 7:
#line 210 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].interfaceDecl); }
    break;

  case 8:
#line 211 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].fnDecl); }
    break;

  case 9:
#line 215 "latte-parse.yy"
    { (yyval.varDecl) = (yyvsp[(1) - (2)].varDecl); }
    break;

  case 10:
#line 219 "latte-parse.yy"
    {
	                          Identifier *i = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
	                          (yyval.varDecl) = new VarDecl(i, (yyvsp[(1) - (2)].type)); 
	                        }
    break;

  case 11:
#line 226 "latte-parse.yy"
    { (yyval.type) = Type::voidType; }
    break;

  case 12:
#line 227 "latte-parse.yy"
    { (yyval.type) = Type::boolType; }
    break;

  case 13:
#line 228 "latte-parse.yy"
    { (yyval.type) = Type::intType; }
    break;

  case 14:
#line 229 "latte-parse.yy"
    { (yyval.type) = Type::doubleType; }
    break;

  case 15:
#line 230 "latte-parse.yy"
    { (yyval.type) = Type::stringType; }
    break;

  case 16:
#line 231 "latte-parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].namedType); }
    break;

  case 17:
#line 232 "latte-parse.yy"
    { (yyval.type) = new ArrayType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].type)); }
    break;

  case 18:
#line 236 "latte-parse.yy"
    { 
				  Identifier *i = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
				  (yyval.namedType) = new NamedType(i); 
				}
    break;

  case 19:
#line 243 "latte-parse.yy"
    {
				  Identifier *i = new Identifier((yylsp[(2) - (7)]), (yyvsp[(2) - (7)].identifier));
				  (yyval.classDecl) = new ClassDecl(i, (yyvsp[(3) - (7)].namedType), (yyvsp[(4) - (7)].implementsTypeList), (yyvsp[(6) - (7)].declList));
				}
    break;

  case 20:
#line 247 "latte-parse.yy"
    {
				  Identifier *i = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
				  (yyval.classDecl) = new ClassDecl(i, (yyvsp[(3) - (6)].namedType), (yyvsp[(4) - (6)].implementsTypeList), new List<Decl*>);
				}
    break;

  case 21:
#line 254 "latte-parse.yy"
    { 
				  Identifier *i = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
				  (yyval.namedType) = new NamedType(i); 
				}
    break;

  case 22:
#line 258 "latte-parse.yy"
    { (yyval.namedType) = NULL; }
    break;

  case 23:
#line 262 "latte-parse.yy"
    { 
				  (yyval.implementsTypeList) = (yyvsp[(2) - (2)].implementsTypeList); 
				}
    break;

  case 24:
#line 265 "latte-parse.yy"
    { (yyval.implementsTypeList) = new List<NamedType*>; }
    break;

  case 25:
#line 269 "latte-parse.yy"
    { 
				  Identifier *i = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
				  NamedType *t = new NamedType(i);
				  ((yyval.implementsTypeList) = (yyvsp[(1) - (2)].implementsTypeList))->Append(t); 
				}
    break;

  case 26:
#line 274 "latte-parse.yy"
    { 
				  Identifier *i = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
				  NamedType *t = new NamedType(i);
				  ((yyval.implementsTypeList) = new List<NamedType*>)->Append(t); 
				}
    break;

  case 27:
#line 282 "latte-parse.yy"
    {
				  Identifier *i = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));
				  (yyval.interfaceDecl) = new InterfaceDecl(i, (yyvsp[(4) - (5)].declList));
				}
    break;

  case 28:
#line 289 "latte-parse.yy"
    { 
				  FnDecl *f = (yyvsp[(1) - (2)].fnDecl);
				  f->SetFunctionBody((yyvsp[(2) - (2)].stmtBlock));
				}
    break;

  case 29:
#line 296 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].varDecl)); }
    break;

  case 30:
#line 297 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].fnDecl)); }
    break;

  case 31:
#line 298 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 32:
#line 299 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].fnDecl)); }
    break;

  case 33:
#line 303 "latte-parse.yy"
    { ((yyval.varDeclList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 34:
#line 304 "latte-parse.yy"
    {
				  ((yyval.varDeclList) = (yyvsp[(1) - (3)].varDeclList))->Append((yyvsp[(3) - (3)].varDecl));
				}
    break;

  case 35:
#line 310 "latte-parse.yy"
    { (yyval.fnDecl) = (yyvsp[(1) - (2)].fnDecl); }
    break;

  case 36:
#line 314 "latte-parse.yy"
    {
				  Identifier *i = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));
				  (yyval.fnDecl) = new FnDecl(i, (yyvsp[(1) - (5)].type), (yyvsp[(4) - (5)].varDeclList));
				}
    break;

  case 37:
#line 318 "latte-parse.yy"
    {
				  Identifier *i = new Identifier((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].identifier));
				  (yyval.fnDecl) = new FnDecl(i, (yyvsp[(1) - (4)].type), new List<VarDecl*>);
				}
    break;

  case 38:
#line 325 "latte-parse.yy"
    {
				  ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].fnDecl));
				}
    break;

  case 39:
#line 328 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].fnDecl)); }
    break;

  case 40:
#line 332 "latte-parse.yy"
    {
				  (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (4)].varDeclList), (yyvsp[(3) - (4)].stmtList));
				}
    break;

  case 41:
#line 335 "latte-parse.yy"
    { (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (3)].varDeclList), new List<Stmt*>); }
    break;

  case 42:
#line 336 "latte-parse.yy"
    { (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>, (yyvsp[(2) - (3)].stmtList)); }
    break;

  case 43:
#line 337 "latte-parse.yy"
    { 
				  (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>,
				  		     new List<Stmt*>);
				}
    break;

  case 44:
#line 344 "latte-parse.yy"
    { ((yyval.stmtList) = (yyvsp[(1) - (2)].stmtList))->Append((yyvsp[(2) - (2)].stmt)); }
    break;

  case 45:
#line 345 "latte-parse.yy"
    { ((yyval.stmtList) = new List<Stmt*>)->Append((yyvsp[(1) - (1)].stmt)); }
    break;

  case 46:
#line 349 "latte-parse.yy"
    { ((yyval.varDeclList) = (yyvsp[(1) - (2)].varDeclList))->Append((yyvsp[(2) - (2)].varDecl)); }
    break;

  case 47:
#line 350 "latte-parse.yy"
    { ((yyval.varDeclList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 48:
#line 354 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].expr); }
    break;

  case 49:
#line 355 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].whileStmt); }
    break;

  case 50:
#line 356 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].returnStmt); }
    break;

  case 51:
#line 357 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].breakStmt); }
    break;

  case 52:
#line 358 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].printStmt); }
    break;

  case 53:
#line 359 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].forStmt); }
    break;

  case 54:
#line 360 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].ifStmt); }
    break;

  case 55:
#line 361 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].switchStmt); }
    break;

  case 56:
#line 362 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmtBlock); }
    break;

  case 57:
#line 366 "latte-parse.yy"
    {
				  (yyval.switchStmt) = new SwitchStmt((yyvsp[(3) - (8)].expr), (yyvsp[(6) - (8)].caseStmtList), (yyvsp[(7) - (8)].defaultStmt));
				}
    break;

  case 58:
#line 372 "latte-parse.yy"
    { ((yyval.caseStmtList) = (yyvsp[(1) - (2)].caseStmtList))->Append((yyvsp[(2) - (2)].caseStmt)); }
    break;

  case 59:
#line 373 "latte-parse.yy"
    { ((yyval.caseStmtList) = new List<CaseStmt*>)->Append((yyvsp[(1) - (1)].caseStmt)); }
    break;

  case 60:
#line 377 "latte-parse.yy"
    { 
				  IntConstant *ic = new IntConstant((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].integerConstant));
				  (yyval.caseStmt) = new CaseStmt(ic, (yyvsp[(4) - (4)].stmtList));
				}
    break;

  case 61:
#line 381 "latte-parse.yy"
    {
				  IntConstant *ic = new IntConstant((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].integerConstant));
				  (yyval.caseStmt) = new CaseStmt(ic, new List<Stmt*>);
				}
    break;

  case 62:
#line 388 "latte-parse.yy"
    { 
				  (yyval.defaultStmt) = new DefaultStmt((yyvsp[(3) - (3)].stmtList));
				}
    break;

  case 63:
#line 391 "latte-parse.yy"
    { 
				  (yyval.defaultStmt) = new DefaultStmt(new List<Stmt*>);
				}
    break;

  case 64:
#line 397 "latte-parse.yy"
    {
				  (yyval.whileStmt) = new WhileStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt));
				}
    break;

  case 65:
#line 403 "latte-parse.yy"
    { (yyval.breakStmt) = new BreakStmt((yylsp[(1) - (2)])); }
    break;

  case 66:
#line 407 "latte-parse.yy"
    {
				  (yyval.printStmt) = new PrintStmt((yyvsp[(3) - (5)].exprList));
				}
    break;

  case 67:
#line 413 "latte-parse.yy"
    { (yyval.returnStmt) = new ReturnStmt((yylsp[(1) - (2)]), new EmptyExpr); }
    break;

  case 68:
#line 414 "latte-parse.yy"
    {
				  (yyval.returnStmt) = new ReturnStmt((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].expr));
				}
    break;

  case 69:
#line 420 "latte-parse.yy"
    {
				  (yyval.forStmt) = new ForStmt((yyvsp[(3) - (6)].expr), (yyvsp[(4) - (6)].expr), new EmptyExpr, (yyvsp[(6) - (6)].stmt));
				}
    break;

  case 70:
#line 423 "latte-parse.yy"
    {
				  (yyval.forStmt) = new ForStmt((yyvsp[(3) - (7)].expr), (yyvsp[(4) - (7)].expr), (yyvsp[(5) - (7)].expr), (yyvsp[(7) - (7)].stmt));
				}
    break;

  case 71:
#line 429 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (2)].expr); }
    break;

  case 72:
#line 430 "latte-parse.yy"
    { (yyval.expr) = new EmptyExpr; }
    break;

  case 73:
#line 434 "latte-parse.yy"
    {
				  (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt), NULL);
				}
    break;

  case 74:
#line 437 "latte-parse.yy"
    {
				  (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt));
				}
    break;

  case 75:
#line 443 "latte-parse.yy"
    { ((yyval.exprList) = (yyvsp[(1) - (3)].exprList))->Append((yyvsp[(3) - (3)].expr)); }
    break;

  case 76:
#line 444 "latte-parse.yy"
    { ((yyval.exprList) = new List<Expr*>)->Append((yyvsp[(1) - (1)].expr)); }
    break;

  case 77:
#line 448 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 78:
#line 452 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 79:
#line 453 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].readIntegerExpr); }
    break;

  case 80:
#line 454 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].readLineExpr); }
    break;

  case 81:
#line 455 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].newExpr); }
    break;

  case 82:
#line 456 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].newArrayExpr); }
    break;

  case 83:
#line 457 "latte-parse.yy"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "=");
				  (yyval.expr) = new AssignExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 84:
#line 463 "latte-parse.yy"
    { (yyval.readIntegerExpr) = new ReadIntegerExpr((yylsp[(1) - (3)])); }
    break;

  case 85:
#line 467 "latte-parse.yy"
    { (yyval.readLineExpr) = new ReadLineExpr((yylsp[(1) - (3)])); }
    break;

  case 86:
#line 471 "latte-parse.yy"
    { (yyval.newExpr) = new NewExpr((yylsp[(1) - (2)]), (yyvsp[(2) - (2)].namedType)); }
    break;

  case 87:
#line 475 "latte-parse.yy"
    {
				  (yyval.newArrayExpr) = new NewArrayExpr((yylsp[(1) - (6)]), (yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].type));
				}
    break;

  case 88:
#line 481 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 89:
#line 482 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "||");
				  (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 90:
#line 486 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "&&");
				  (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 91:
#line 493 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 92:
#line 494 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "<");
				  (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 93:
#line 498 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), ">");
				  (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 94:
#line 502 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), ">=");
				  (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 95:
#line 506 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "<=");
				  (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 96:
#line 513 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 97:
#line 514 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "==");
				  (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 98:
#line 518 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "!=");
				  (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 99:
#line 525 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 100:
#line 526 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "+");
				  (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 101:
#line 530 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "-");
				  (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 102:
#line 537 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 103:
#line 541 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "*");
				  (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 104:
#line 545 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "/");
				  (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 105:
#line 549 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (3)]), "%");
				  (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
				}
    break;

  case 106:
#line 556 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 107:
#line 557 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(1) - (2)]), "-");
				  (yyval.expr) = new ArithmeticExpr(op, (yyvsp[(2) - (2)].expr));
				}
    break;

  case 108:
#line 561 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(1) - (2)]), "!");
				  (yyval.expr) = new LogicalExpr(op, (yyvsp[(2) - (2)].expr));
				}
    break;

  case 109:
#line 565 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (2)]), "++");
				  (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr), op);
				}
    break;

  case 110:
#line 569 "latte-parse.yy"
    {
				  Operator *op = new Operator((yylsp[(2) - (2)]), "--");
				  (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr), op);
				}
    break;

  case 111:
#line 576 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 112:
#line 577 "latte-parse.yy"
    { (yyval.expr) = new ArrayAccess((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); }
    break;

  case 113:
#line 578 "latte-parse.yy"
    { 
				  Identifier *id = new Identifier((yylsp[(1) - (3)]), (yyvsp[(1) - (3)].identifier));
				  (yyval.expr) = new Call((yylsp[(1) - (3)]), NULL, id, new List<Expr*>); 
				}
    break;

  case 114:
#line 582 "latte-parse.yy"
    {
				  Identifier *id = new Identifier((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].identifier));
				  (yyval.expr) = new Call((yylsp[(1) - (4)]), NULL, id, (yyvsp[(3) - (4)].exprList));
				}
    break;

  case 115:
#line 586 "latte-parse.yy"
    {
				  Identifier *id = new Identifier((yylsp[(3) - (3)]), (yyvsp[(3) - (3)].identifier));
				  (yyval.expr) = new FieldAccess((yyvsp[(1) - (3)].expr), id);
				}
    break;

  case 116:
#line 590 "latte-parse.yy"
    { 
				  Identifier *id = new Identifier((yylsp[(3) - (5)]), (yyvsp[(3) - (5)].identifier));
				  (yyval.expr) = new Call((yylsp[(1) - (5)]), (yyvsp[(1) - (5)].expr), id, new List<Expr*>);
				}
    break;

  case 117:
#line 594 "latte-parse.yy"
    {
				  Identifier *id = new Identifier((yylsp[(3) - (6)]), (yyvsp[(3) - (6)].identifier));
				  (yyval.expr) = new Call((yylsp[(1) - (6)]), (yyvsp[(1) - (6)].expr), id, (yyvsp[(5) - (6)].exprList));
				}
    break;

  case 118:
#line 601 "latte-parse.yy"
    { Identifier *id = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
				  (yyval.expr) = new FieldAccess(NULL, id); 
				}
    break;

  case 119:
#line 604 "latte-parse.yy"
    { (yyval.expr) = new This((yylsp[(1) - (1)])); }
    break;

  case 120:
#line 605 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 121:
#line 606 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 122:
#line 610 "latte-parse.yy"
    { (yyval.expr) = new IntConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].integerConstant)); }
    break;

  case 123:
#line 611 "latte-parse.yy"
    { (yyval.expr) = new DoubleConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].doubleConstant)); }
    break;

  case 124:
#line 612 "latte-parse.yy"
    { (yyval.expr) = new BoolConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].boolConstant)); }
    break;

  case 125:
#line 613 "latte-parse.yy"
    { (yyval.expr) = new StringConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].stringConstant)); }
    break;

  case 126:
#line 614 "latte-parse.yy"
    { (yyval.expr) = new NullConstant((yylsp[(1) - (1)])); }
    break;


/* Line 1267 of yacc.c.  */
#line 2577 "latte-parse.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 617 "latte-parse.yy"


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

