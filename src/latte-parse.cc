
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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



/* Line 189 of yacc.c  */
#line 93 "latte-parse.cc"

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
     NEG = 297,
     NOELSE = 298,
     EMPTYCASE = 299,
     EMPTYDEFAULT = 300,
     NONEMPTYCASE = 301,
     NONEMPTYDEFAULT = 302
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
#define NEG 297
#define NOELSE 298
#define EMPTYCASE 299
#define EMPTYDEFAULT 300
#define NONEMPTYCASE 301
#define NONEMPTYDEFAULT 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 44 "latte-parse.yy"

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
    IfStmt           *ifStmt;
    Expr             *expr;
    List<Expr*>      *exprList;
    FieldAccess      *fieldAccess;
    CaseStmt         *caseStmt;
    List<CaseStmt*>  *caseStmtList;
    DefaultStmt      *defaultStmt;



/* Line 214 of yacc.c  */
#line 254 "latte-parse.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


/* Line 264 of yacc.c  */
#line 279 "latte-parse.cc"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   985

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,    49,     2,     2,
      61,    62,    47,    45,    65,    46,    52,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    66,    59,
      43,    42,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    67,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    51,    54,    55,
      56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    23,    26,    28,    34,    37,    38,    40,    42,    44,
      46,    48,    50,    53,    55,    63,    70,    73,    74,    77,
      78,    82,    84,    90,    93,   103,   106,   109,   111,   113,
     115,   119,   122,   128,   130,   131,   134,   136,   141,   145,
     149,   152,   155,   157,   160,   162,   165,   171,   174,   178,
     181,   187,   197,   199,   208,   210,   212,   213,   216,   218,
     223,   227,   231,   234,   240,   248,   252,   254,   256,   258,
     260,   264,   268,   272,   276,   280,   284,   288,   292,   296,
     300,   304,   308,   312,   315,   318,   321,   324,   328,   330,
     334,   338,   341,   348,   352,   354,   360,   365,   372,   374,
     375,   377,   381,   386,   388,   390,   392,   394
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    70,    -1,    70,    71,    -1,    71,    -1,
      72,    -1,    78,    -1,    82,    -1,    83,    -1,    84,    -1,
      73,    59,    -1,    74,    37,    -1,    76,    -1,    76,    60,
      61,    75,    62,    -1,    75,    76,    -1,    -1,     3,    -1,
       4,    -1,     5,    -1,     6,    -1,     7,    -1,    77,    -1,
      76,    13,    -1,    37,    -1,     8,    37,    79,    80,    63,
      85,    64,    -1,     8,    37,    79,    80,    63,    64,    -1,
      17,    37,    -1,    -1,    20,    81,    -1,    -1,    81,    65,
      37,    -1,    37,    -1,    19,    37,    63,    90,    64,    -1,
      88,    91,    -1,    76,    61,    60,    37,    62,    61,    89,
      62,    59,    -1,    85,    72,    -1,    85,    83,    -1,    72,
      -1,    83,    -1,    73,    -1,    86,    65,    73,    -1,    88,
      59,    -1,    74,    37,    61,    89,    62,    -1,    86,    -1,
      -1,    90,    87,    -1,    87,    -1,    63,    93,    92,    64,
      -1,    63,    93,    64,    -1,    63,    92,    64,    -1,    63,
      64,    -1,    92,    94,    -1,    94,    -1,    93,    72,    -1,
      72,    -1,    95,    59,    -1,    21,    61,   101,    62,    94,
      -1,    25,    59,    -1,    25,   101,    59,    -1,    26,    59,
      -1,    29,    61,   100,    62,    59,    -1,    22,    61,    95,
      59,   101,    59,    95,    62,    94,    -1,    99,    -1,    32,
      61,   101,    62,    63,    96,    98,    64,    -1,    91,    -1,
     101,    -1,    -1,    96,    97,    -1,    97,    -1,    33,    39,
      66,    92,    -1,    33,    39,    66,    -1,    34,    66,    92,
      -1,    34,    66,    -1,    23,    61,   101,    62,    94,    -1,
      23,    61,   101,    62,    94,    24,    94,    -1,   100,    65,
     101,    -1,   101,    -1,   105,    -1,   103,    -1,   106,    -1,
     101,    15,   101,    -1,   101,    14,   101,    -1,   101,    43,
     101,    -1,   101,    44,   101,    -1,   101,    10,   101,    -1,
     101,     9,   101,    -1,   101,    11,   101,    -1,   101,    12,
     101,    -1,   101,    45,   101,    -1,   101,    46,   101,    -1,
     101,    47,   101,    -1,   101,    48,   101,    -1,   101,    49,
     101,    -1,    46,   101,    -1,    50,   101,    -1,   101,    35,
      -1,   101,    36,    -1,    61,   101,    62,    -1,    18,    -1,
      30,    61,    62,    -1,    31,    61,    62,    -1,    27,    77,
      -1,    28,    61,   101,    65,    74,    62,    -1,   105,    42,
     101,    -1,   102,    -1,    60,    61,    89,    62,    91,    -1,
      37,    61,   104,    62,    -1,   101,    52,    37,    61,   104,
      62,    -1,   100,    -1,    -1,    37,    -1,   101,    52,    37,
      -1,   101,    53,   101,    67,    -1,    39,    -1,    40,    -1,
      41,    -1,    38,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   179,   180,   184,   185,   186,   187,   188,
     194,   198,   206,   207,   214,   215,   219,   220,   221,   222,
     223,   224,   225,   229,   237,   242,   250,   255,   259,   263,
     267,   273,   282,   290,   298,   305,   306,   307,   308,   312,
     313,   320,   324,   332,   333,   337,   341,   345,   349,   350,
     351,   359,   360,   364,   365,   369,   370,   374,   375,   376,
     377,   381,   385,   386,   390,   394,   395,   400,   401,   405,
     410,   418,   422,   429,   433,   440,   441,   445,   446,   447,
     448,   453,   458,   463,   468,   473,   478,   483,   488,   493,
     498,   503,   508,   513,   518,   523,   528,   533,   534,   535,
     536,   537,   538,   542,   547,   553,   561,   565,   572,   573,
     577,   578,   579,   584,   585,   586,   587,   588
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
  "T_BoolConstant", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "NEG", "'.'", "'['", "NOELSE", "EMPTYCASE", "EMPTYDEFAULT",
  "NONEMPTYCASE", "NONEMPTYDEFAULT", "';'", "'^'", "'('", "')'", "'{'",
  "'}'", "','", "':'", "']'", "$accept", "Program", "DeclList", "Decl",
  "VarDecl", "Variable", "Type", "TypeList", "SimpleType", "NamedType",
  "ClassDecl", "ClassExtends", "ClassImplements", "ImplementsTypeList",
  "InterfaceDecl", "FnDecl", "ClosureDecl", "FieldList", "FormalsList",
  "Prototype", "FnDef", "Formals", "PrototypeList", "StmtBlock",
  "StmtList", "VarDeclList", "Stmt", "OptExpr", "CaseStmtList", "CaseStmt",
  "DefaultStmt", "IfStmt", "ExprList", "Expr", "ClosureExpr", "Call",
  "Actuals", "LValue", "Constant", 0
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
     295,   296,    61,    60,    62,    43,    45,    42,    47,    37,
      33,   297,    46,    91,   298,   299,   300,   301,   302,    59,
      94,    40,    41,   123,   125,    44,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    70,    71,    71,    71,    71,    71,
      72,    73,    74,    74,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    83,    84,    85,    85,    85,    85,    86,
      86,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   102,   103,   103,   104,   104,
     105,   105,   105,   106,   106,   106,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     5,     2,     0,     1,     1,     1,     1,
       1,     1,     2,     1,     7,     6,     2,     0,     2,     0,
       3,     1,     5,     2,     9,     2,     2,     1,     1,     1,
       3,     2,     5,     1,     0,     2,     1,     4,     3,     3,
       2,     2,     1,     2,     1,     2,     5,     2,     3,     2,
       5,     9,     1,     8,     1,     1,     0,     2,     1,     4,
       3,     3,     2,     5,     7,     3,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     3,     1,     3,
       3,     2,     6,     3,     1,     5,     4,     6,     1,     0,
       1,     3,     4,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,    17,    18,    19,    20,     0,     0,    23,     0,
       2,     4,     5,     0,     0,    12,    21,     6,     7,     8,
       9,     0,    27,     0,     1,     3,    10,    11,    22,     0,
       0,    66,    33,     0,    29,     0,    44,    15,     0,   117,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   116,   113,   114,   115,     0,     0,     0,
       0,    50,    54,     0,    12,    64,    66,    66,    52,     0,
      62,    65,   104,    78,    77,    79,    26,     0,     0,     0,
      46,     0,     0,    39,    43,     0,     0,     0,     0,    66,
       0,   110,    57,     0,    59,   101,     0,     0,     0,     0,
       0,   109,    93,    94,    44,     0,    11,    49,    51,    48,
      53,    66,    55,     0,     0,     0,     0,     0,     0,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,    28,     0,     0,    41,    32,    45,     0,    42,
      13,    14,     0,     0,     0,     0,    58,     0,     0,    76,
      99,   100,     0,   108,     0,     0,    97,    47,    85,    84,
      86,    87,    81,    80,    82,    83,    88,    89,    90,    91,
      92,   111,     0,   103,     0,    25,    37,    38,     0,    40,
      44,    66,     0,    66,     0,     0,     0,     0,   106,     0,
     109,   112,    30,    24,    35,    36,     0,    56,     0,    73,
       0,    60,    75,     0,   105,     0,     0,    66,    66,   102,
       0,     0,    68,   107,    34,     0,    74,     0,     0,    67,
       0,    66,    70,    66,    63,    61,    69,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    63,    86,    64,    16,
      17,    34,    78,   132,    18,    19,    20,   178,    84,    80,
      21,    85,    82,    65,    66,    67,    68,    69,   211,   212,
     220,    70,   153,    71,    72,    73,   154,    74,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -122
static const yytype_int16 yypact[] =
{
     948,  -122,  -122,  -122,  -122,  -122,   -31,   -24,  -122,    18,
     948,  -122,  -122,   -32,    -6,     1,  -122,  -122,  -122,  -122,
    -122,   -25,    31,   -14,  -122,  -122,  -122,    -9,  -122,    -7,
      10,   169,  -122,    13,    52,   131,   131,  -122,    36,  -122,
    -122,    14,    22,    35,   818,    38,    61,    39,    41,    50,
      57,    63,    -5,  -122,  -122,  -122,  -122,   844,   844,    64,
     844,  -122,  -122,    85,    -2,  -122,   549,   218,  -122,    70,
    -122,   877,  -122,  -122,    88,  -122,  -122,    90,    69,    94,
    -122,    80,    37,  -122,    76,    81,   109,    86,   844,   844,
     844,    91,  -122,   491,  -122,  -122,   844,   844,    89,    92,
     844,   844,   -16,   -16,   131,   311,  -122,  -122,  -122,  -122,
    -122,   598,  -122,   844,   844,   844,   844,   844,   844,  -122,
    -122,   844,   844,   844,   844,   844,   844,   844,   105,   844,
     844,  -122,    82,    62,    -9,  -122,  -122,  -122,   131,  -122,
    -122,   142,    95,   356,    99,   401,  -122,   296,   -40,   877,
    -122,  -122,   446,    96,   102,   104,  -122,  -122,   431,   431,
     341,   341,   386,   897,   431,   431,   -19,   -19,    68,    68,
      68,   116,   251,   877,   128,  -122,  -122,  -122,   103,  -122,
     131,   791,   844,   791,   131,   120,   844,   117,  -122,   -25,
     844,  -122,  -122,  -122,  -122,  -122,   119,  -122,   510,   158,
     121,  -122,   877,   153,  -122,   126,   130,   844,   791,  -122,
     154,    12,  -122,  -122,  -122,   140,  -122,   137,   138,  -122,
     141,   791,   745,   647,  -122,  -122,   745,   696
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -122,  -122,  -122,   201,   -28,   -10,     0,  -122,     9,   166,
    -122,  -122,  -122,  -122,  -122,  -121,  -122,  -122,  -122,   132,
     -11,   -89,  -122,   -20,   -63,  -122,   -64,   -84,  -122,     2,
    -122,  -122,   123,   -37,  -122,  -122,    26,  -122,  -122
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -73
static const yytype_int16 yytable[] =
{
      14,    32,   108,    62,   111,   144,    22,    93,   -23,    15,
      14,    28,   177,    23,    28,   155,   119,   120,    24,    15,
     102,   103,   185,   105,    81,   186,    83,    26,   125,   126,
     127,    27,   -23,   128,   129,    79,   128,   129,    31,   110,
       1,     2,     3,     4,     5,   210,   218,   108,    33,    35,
      76,   143,    36,   145,    37,   -23,   101,   195,    29,   147,
     149,    29,    30,   152,   149,     1,     2,     3,     4,     5,
      38,    81,    77,    87,     8,    88,   158,   159,   160,   161,
     162,   163,    79,    89,   164,   165,   166,   167,   168,   169,
     170,   196,   172,   173,    83,   141,    90,    94,     8,     8,
      96,   136,    97,   119,   120,   176,     1,     2,     3,     4,
       5,    98,     1,     2,     3,     4,     5,   197,    99,   199,
     128,   129,   106,   215,   100,   104,   175,   131,   179,   112,
     130,   134,   133,    14,     1,     2,     3,     4,     5,   135,
       8,   138,   171,   139,   216,   198,     8,   174,   142,   202,
     194,   150,   101,   149,   151,    28,   180,   225,   182,   226,
     227,   186,   108,   108,   188,   192,   189,   193,     8,   204,
      83,   140,     1,     2,     3,     4,     5,   190,    14,   201,
     203,   206,   208,   209,   200,    39,   210,    40,   213,   214,
      41,    42,    43,   217,    44,    45,    46,    47,    48,    49,
      50,    51,   221,   222,   223,   224,    52,    53,    54,    55,
      56,    25,    95,   219,   137,    57,   205,     0,     0,    58,
     148,     1,     2,     3,     4,     5,     0,     0,     0,    59,
      60,     0,    31,    61,    39,     0,    40,     0,     0,    41,
      42,    43,     0,    44,    45,    46,    47,    48,    49,    50,
      51,     0,     0,     0,     0,    52,    53,    54,    55,    56,
     113,   114,   115,   116,    57,   117,   118,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
       0,    31,   109,     0,     0,     0,   119,   120,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,   113,   114,   115,   116,     0,
     117,   118,     0,     0,     0,     0,     0,     0,   191,     0,
     113,   114,   115,   116,     0,   117,   118,     0,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   119,   120,   128,   129,
     113,   114,   -73,   -73,   121,   122,   123,   124,   125,   126,
     127,   184,     0,   128,   129,   113,   114,   115,   116,     0,
     117,   118,     0,   156,     0,     0,   119,   120,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   119,   120,   128,   129,   113,   114,   115,   116,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   128,   129,
     113,   114,   115,   116,     0,   117,   118,     0,   181,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   119,   120,   128,   129,
     -73,   -73,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,   113,   114,   115,   116,     0,
     117,   118,     0,   183,     0,     0,   119,   120,     0,     0,
       0,     0,     0,     0,   -73,   -73,   123,   124,   125,   126,
     127,   119,   120,   128,   129,     0,     0,     0,     0,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   128,   129,
     113,   114,   115,   116,     0,   117,   118,     0,   187,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,     0,   117,   118,   119,   120,     0,     0,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,   119,   120,     0,     0,     0,
     146,     0,     0,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,    39,     0,    40,     0,   207,
      41,    42,    43,     0,    44,    45,    46,    47,    48,    49,
      50,    51,     0,     0,     0,     0,    91,    53,    54,    55,
      56,     0,     0,     0,     0,    57,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,     0,    31,   107,    39,     0,    40,     0,     0,    41,
      42,    43,     0,    44,    45,    46,    47,    48,    49,    50,
      51,     0,     0,     0,     0,    91,    53,    54,    55,    56,
       0,     0,     0,     0,    57,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
       0,    31,   157,    39,     0,    40,     0,     0,    41,    42,
      43,     0,    44,    45,    46,    47,    48,    49,    50,    51,
       0,     0,     0,     0,    91,    53,    54,    55,    56,     0,
       0,     0,     0,    57,     0,     0,     0,    58,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,     0,
      31,   -72,    39,     0,    40,     0,     0,    41,    42,    43,
       0,    44,    45,    46,    47,    48,    49,    50,    51,     0,
       0,     0,     0,    91,    53,    54,    55,    56,     0,     0,
       0,     0,    57,     0,     0,     0,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,     0,    31,
     -71,    39,     0,    40,     0,     0,    41,    42,    43,     0,
      44,    45,    46,    47,    48,    49,    50,    51,     0,     0,
       0,     0,    91,    53,    54,    55,    56,     0,     0,     0,
       0,    57,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,   -66,    59,    60,    39,    31,    40,
       0,     0,    41,    42,    43,     0,    44,    45,    46,    47,
      48,    49,    50,    51,     0,     0,     0,     0,    91,    53,
      54,    55,    56,     0,    39,     0,    40,    57,     0,     0,
       0,    58,     0,     0,     0,    46,    47,     0,    49,    50,
       0,    59,    60,     0,    31,    91,    53,    54,    55,    56,
      39,     0,    40,     0,    57,     0,     0,     0,    58,     0,
       0,    46,    47,     0,    49,    50,     0,    92,    59,    60,
       0,    91,    53,    54,    55,    56,   113,   114,   115,   116,
      57,   117,   118,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,   113,   114,   115,   116,
       0,   117,   119,   120,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,     0,   128,
     129,     0,   119,   120,     0,     0,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,     0,     0,   128,
     129,     1,     2,     3,     4,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8
};

static const yytype_int16 yycheck[] =
{
       0,    21,    66,    31,    67,    89,    37,    44,    13,     0,
      10,    13,   133,    37,    13,   104,    35,    36,     0,    10,
      57,    58,    62,    60,    35,    65,    36,    59,    47,    48,
      49,    37,    37,    52,    53,    35,    52,    53,    63,    67,
       3,     4,     5,     6,     7,    33,    34,   111,    17,    63,
      37,    88,    61,    90,    61,    60,    61,   178,    60,    96,
      97,    60,    61,   100,   101,     3,     4,     5,     6,     7,
      60,    82,    20,    37,    37,    61,   113,   114,   115,   116,
     117,   118,    82,    61,   121,   122,   123,   124,   125,   126,
     127,   180,   129,   130,   104,    86,    61,    59,    37,    37,
      61,    64,    61,    35,    36,   133,     3,     4,     5,     6,
       7,    61,     3,     4,     5,     6,     7,   181,    61,   183,
      52,    53,    37,   207,    61,    61,    64,    37,   138,    59,
      42,    37,    63,   133,     3,     4,     5,     6,     7,    59,
      37,    65,    37,    62,   208,   182,    37,    65,    62,   186,
     178,    62,    61,   190,    62,    13,    61,   221,    59,   222,
     223,    65,   226,   227,    62,    37,    62,    64,    37,   189,
     180,    62,     3,     4,     5,     6,     7,    61,   178,    59,
      63,    62,    24,    62,   184,    16,    33,    18,    62,    59,
      21,    22,    23,    39,    25,    26,    27,    28,    29,    30,
      31,    32,    62,    66,    66,    64,    37,    38,    39,    40,
      41,    10,    46,   211,    82,    46,   190,    -1,    -1,    50,
      97,     3,     4,     5,     6,     7,    -1,    -1,    -1,    60,
      61,    -1,    63,    64,    16,    -1,    18,    -1,    -1,    21,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
       9,    10,    11,    12,    46,    14,    15,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    63,    64,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,     9,    10,    11,    12,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
       9,    10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    35,    36,    52,    53,
       9,    10,    11,    12,    43,    44,    45,    46,    47,    48,
      49,    65,    -1,    52,    53,     9,    10,    11,    12,    -1,
      14,    15,    -1,    62,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    35,    36,    52,    53,     9,    10,    11,    12,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    52,    53,
       9,    10,    11,    12,    -1,    14,    15,    -1,    62,    -1,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    35,    36,    52,    53,
       9,    10,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,     9,    10,    11,    12,    -1,
      14,    15,    -1,    62,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    35,    36,    52,    53,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    52,    53,
       9,    10,    11,    12,    -1,    14,    15,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    14,    15,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,    35,    36,    -1,    -1,    -1,
      59,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    52,    53,    -1,    16,    -1,    18,    -1,    59,
      21,    22,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    63,    64,    16,    -1,    18,    -1,    -1,    21,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    63,    64,    16,    -1,    18,    -1,    -1,    21,    22,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      63,    64,    16,    -1,    18,    -1,    -1,    21,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    63,
      64,    16,    -1,    18,    -1,    -1,    21,    22,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    16,    63,    18,
      -1,    -1,    21,    22,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    -1,    16,    -1,    18,    46,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    27,    28,    -1,    30,    31,
      -1,    60,    61,    -1,    63,    37,    38,    39,    40,    41,
      16,    -1,    18,    -1,    46,    -1,    -1,    -1,    50,    -1,
      -1,    27,    28,    -1,    30,    31,    -1,    59,    60,    61,
      -1,    37,    38,    39,    40,    41,     9,    10,    11,    12,
      46,    14,    15,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,     9,    10,    11,    12,
      -1,    14,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    52,
      53,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    52,
      53,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    37,    69,
      70,    71,    72,    73,    74,    76,    77,    78,    82,    83,
      84,    88,    37,    37,     0,    71,    59,    37,    13,    60,
      61,    63,    91,    17,    79,    63,    61,    61,    60,    16,
      18,    21,    22,    23,    25,    26,    27,    28,    29,    30,
      31,    32,    37,    38,    39,    40,    41,    46,    50,    60,
      61,    64,    72,    74,    76,    91,    92,    93,    94,    95,
      99,   101,   102,   103,   105,   106,    37,    20,    80,    74,
      87,    88,    90,    73,    86,    89,    75,    37,    61,    61,
      61,    37,    59,   101,    59,    77,    61,    61,    61,    61,
      61,    61,   101,   101,    61,   101,    37,    64,    94,    64,
      72,    92,    59,     9,    10,    11,    12,    14,    15,    35,
      36,    43,    44,    45,    46,    47,    48,    49,    52,    53,
      42,    37,    81,    63,    37,    59,    64,    87,    65,    62,
      62,    76,    62,   101,    95,   101,    59,   101,   100,   101,
      62,    62,   101,   100,   104,    89,    62,    64,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,    37,   101,   101,    65,    64,    72,    83,    85,    73,
      61,    62,    59,    62,    65,    62,    65,    62,    62,    62,
      61,    67,    37,    64,    72,    83,    89,    94,   101,    94,
      74,    59,   101,    63,    91,   104,    62,    59,    24,    62,
      33,    96,    97,    62,    59,    95,    94,    39,    34,    97,
      98,    62,    66,    66,    64,    94,    92,    92
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 153 "latte-parse.yy"
    {
      (yylsp[(1) - (1)]);
      /* pp2: The @1 is needed to convince 
       * yacc to set up yylloc. You can remove 
       * it once you have other uses of @n*/
      Program *program = new Program((yyvsp[(1) - (1)].declList));
      // if no errors, advance to next phase
      if (ReportError::NumErrors() == 0)
        {
          if (testFlag == TEST_PARSER)
            {
              program->Print(0);
            }
          else
            {
	      
              /*
               * pp3: if no errors, check program
               */
              program->Check();
            }
        }
    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 179 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 180 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].decl)); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 184 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].varDecl); }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 185 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].classDecl); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 186 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].interfaceDecl); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 187 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].fnDecl); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 188 "latte-parse.yy"
    { (yyval.decl) = (yyvsp[(1) - (1)].decl); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 194 "latte-parse.yy"
    { (yyval.varDecl) = (yyvsp[(1) - (2)].varDecl); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 199 "latte-parse.yy"
    {
      Identifier *i = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier)) ;
      (yyval.varDecl) = new VarDecl(i, (yyvsp[(1) - (2)].type)); 
    }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 206 "latte-parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 208 "latte-parse.yy"
    {
    
    }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 214 "latte-parse.yy"
    {}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 215 "latte-parse.yy"
    {}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 219 "latte-parse.yy"
    { (yyval.type) = Type::voidType; }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 220 "latte-parse.yy"
    { (yyval.type) = Type::boolType; }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 221 "latte-parse.yy"
    { (yyval.type) = Type::intType; }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 222 "latte-parse.yy"
    { (yyval.type) = Type::doubleType; }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 223 "latte-parse.yy"
    { (yyval.type) = Type::stringType; }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 224 "latte-parse.yy"
    { (yyval.type) = (yyvsp[(1) - (1)].namedType); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 225 "latte-parse.yy"
    { (yyval.type) = new ArrayType(Join((yylsp[(1) - (2)]), (yylsp[(2) - (2)])), (yyvsp[(1) - (2)].type)); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 230 "latte-parse.yy"
    { 
      Identifier *i = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
      (yyval.namedType) = new NamedType(i); 
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 238 "latte-parse.yy"
    {
      Identifier *i = new Identifier((yylsp[(2) - (7)]), (yyvsp[(2) - (7)].identifier));
      (yyval.classDecl) = new ClassDecl(i, (yyvsp[(3) - (7)].namedType), (yyvsp[(4) - (7)].implementsTypeList), (yyvsp[(6) - (7)].declList));
    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 243 "latte-parse.yy"
    {
      Identifier *i = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
      (yyval.classDecl) = new ClassDecl(i, (yyvsp[(3) - (6)].namedType), (yyvsp[(4) - (6)].implementsTypeList), new List<Decl*>);
    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 251 "latte-parse.yy"
    { 
      Identifier *i = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
      (yyval.namedType) = new NamedType(i); 
    }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 255 "latte-parse.yy"
    { (yyval.namedType) = NULL; }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 260 "latte-parse.yy"
    { 
      (yyval.implementsTypeList) = (yyvsp[(2) - (2)].implementsTypeList); 
    }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 263 "latte-parse.yy"
    { (yyval.implementsTypeList) = new List<NamedType*>; }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 268 "latte-parse.yy"
    { 
      Identifier *i = new Identifier((yylsp[(3) - (3)]), (yyvsp[(3) - (3)].identifier));
      NamedType *t = new NamedType(i);
      ((yyval.implementsTypeList) = (yyvsp[(1) - (3)].implementsTypeList))->Append(t); 
    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 274 "latte-parse.yy"
    { 
      Identifier *i = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
      NamedType *t = new NamedType(i);
      ((yyval.implementsTypeList) = new List<NamedType*>)->Append(t); 
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 283 "latte-parse.yy"
    {
      Identifier *i = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));
      (yyval.interfaceDecl) = new InterfaceDecl(i, (yyvsp[(4) - (5)].declList));
    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 291 "latte-parse.yy"
    { 
      FnDecl *f = (yyvsp[(1) - (2)].fnDecl);
      f->SetFunctionBody((yyvsp[(2) - (2)].stmtBlock));
    }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 299 "latte-parse.yy"
    {
    
    }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 305 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].varDecl)); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 306 "latte-parse.yy"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].fnDecl)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 307 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 308 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].fnDecl)); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 312 "latte-parse.yy"
    { ((yyval.varDeclList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 314 "latte-parse.yy"
    {
      ((yyval.varDeclList) = (yyvsp[(1) - (3)].varDeclList))->Append((yyvsp[(3) - (3)].varDecl));
    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 320 "latte-parse.yy"
    { (yyval.fnDecl) = (yyvsp[(1) - (2)].fnDecl); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 325 "latte-parse.yy"
    {
      Identifier *i = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));
      (yyval.fnDecl) = new FnDecl(i, (yyvsp[(1) - (5)].type), (yyvsp[(4) - (5)].varDeclList));
    }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 332 "latte-parse.yy"
    { (yyval.varDeclList) = (yyvsp[(1) - (1)].varDeclList); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 333 "latte-parse.yy"
    { (yyval.varDeclList) = new List<VarDecl*>; }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 338 "latte-parse.yy"
    {
      ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].fnDecl));
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 341 "latte-parse.yy"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].fnDecl)); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 346 "latte-parse.yy"
    {
      (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (4)].varDeclList), (yyvsp[(3) - (4)].stmtList));
    }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 349 "latte-parse.yy"
    { (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (3)].varDeclList), new List<Stmt*>); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 350 "latte-parse.yy"
    { (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>, (yyvsp[(2) - (3)].stmtList)); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 352 "latte-parse.yy"
    { 
      (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>,
      new List<Stmt*>);
    }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 359 "latte-parse.yy"
    { ((yyval.stmtList) = (yyvsp[(1) - (2)].stmtList))->Append((yyvsp[(2) - (2)].stmt)); }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 360 "latte-parse.yy"
    { ((yyval.stmtList) = new List<Stmt*>)->Append((yyvsp[(1) - (1)].stmt)); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 364 "latte-parse.yy"
    { ((yyval.varDeclList) = (yyvsp[(1) - (2)].varDeclList))->Append((yyvsp[(2) - (2)].varDecl)); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 365 "latte-parse.yy"
    { ((yyval.varDeclList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 369 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (2)].expr); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 371 "latte-parse.yy"
    {
      (yyval.stmt) = new WhileStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt));
    }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 374 "latte-parse.yy"
    { (yyval.stmt) = new ReturnStmt((yylsp[(1) - (2)]), new EmptyExpr); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 375 "latte-parse.yy"
    { (yyval.stmt) = new ReturnStmt((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].expr)); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 376 "latte-parse.yy"
    { (yyval.stmt) = new BreakStmt((yylsp[(1) - (2)])); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 378 "latte-parse.yy"
    {
      (yyval.stmt) = new PrintStmt((yyvsp[(3) - (5)].exprList));
    }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 382 "latte-parse.yy"
    {
      (yyval.stmt) = new ForStmt((yyvsp[(3) - (9)].expr), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].stmt));
    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 385 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].ifStmt); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 387 "latte-parse.yy"
    {
      (yyval.stmt) = new SwitchStmt((yyvsp[(3) - (8)].expr), (yyvsp[(6) - (8)].caseStmtList), (yyvsp[(7) - (8)].defaultStmt));
    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 390 "latte-parse.yy"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmtBlock); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 394 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 395 "latte-parse.yy"
    { (yyval.expr) = new EmptyExpr(); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 400 "latte-parse.yy"
    { ((yyval.caseStmtList) = (yyvsp[(1) - (2)].caseStmtList))->Append((yyvsp[(2) - (2)].caseStmt)); }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 401 "latte-parse.yy"
    { ((yyval.caseStmtList) = new List<CaseStmt*>)->Append((yyvsp[(1) - (1)].caseStmt)); }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 406 "latte-parse.yy"
    { 
      IntConstant *ic = new IntConstant((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].integerConstant));
      (yyval.caseStmt) = new CaseStmt(ic, (yyvsp[(4) - (4)].stmtList));
    }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 411 "latte-parse.yy"
    {
      IntConstant *ic = new IntConstant((yylsp[(2) - (3)]), (yyvsp[(2) - (3)].integerConstant));
      (yyval.caseStmt) = new CaseStmt(ic, new List<Stmt*>);
    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 419 "latte-parse.yy"
    { 
      (yyval.defaultStmt) = new DefaultStmt((yyvsp[(3) - (3)].stmtList));
    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 423 "latte-parse.yy"
    { 
      (yyval.defaultStmt) = new DefaultStmt(new List<Stmt*>);
    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 430 "latte-parse.yy"
    {
      (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt), NULL);
    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 434 "latte-parse.yy"
    {
      (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt));
    }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 440 "latte-parse.yy"
    { ((yyval.exprList) = (yyvsp[(1) - (3)].exprList))->Append((yyvsp[(3) - (3)].expr)); }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 441 "latte-parse.yy"
    { ((yyval.exprList) = new List<Expr*>)->Append((yyvsp[(1) - (1)].expr)); }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 445 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 446 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 447 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 449 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "||");
      (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 454 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "&&");
      (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 459 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "<");
      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 464 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), ">");
      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
   }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 469 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), ">=");
      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 474 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "<=");
      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
	}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 479 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "==");
      (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 484 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "!=");
      (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 489 "latte-parse.yy"
    {
       Operator *op = new Operator((yylsp[(2) - (3)]), "+");
       (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 494 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "-");
      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 499 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "*");
      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 504 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "/");
      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 509 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (3)]), "%");
      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 514 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(1) - (2)]), "-");
      (yyval.expr) = new ArithmeticExpr(op, (yyvsp[(2) - (2)].expr));
    }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 519 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(1) - (2)]), "!");
      (yyval.expr) = new LogicalExpr(op, (yyvsp[(2) - (2)].expr));
    }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 524 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (2)]), "++");
      (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr), op);
    }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 529 "latte-parse.yy"
    {
      Operator *op = new Operator((yylsp[(2) - (2)]), "--");
      (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr), op);
    }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 533 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 534 "latte-parse.yy"
    { (yyval.expr) = new This((yylsp[(1) - (1)])); }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 535 "latte-parse.yy"
    { (yyval.expr) = new ReadIntegerExpr(Join((yylsp[(1) - (3)]), (yylsp[(3) - (3)]))); }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 536 "latte-parse.yy"
    { (yyval.expr) = new ReadLineExpr(Join((yylsp[(1) - (3)]), (yylsp[(3) - (3)]))); }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 537 "latte-parse.yy"
    { (yyval.expr) = new NewExpr(Join((yylsp[(1) - (2)]), (yylsp[(2) - (2)])), (yyvsp[(2) - (2)].namedType)); }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 539 "latte-parse.yy"
    {
      (yyval.expr) = new NewArrayExpr(Join((yylsp[(1) - (6)]), (yylsp[(6) - (6)])), (yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].type));
    }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 543 "latte-parse.yy"
    {
    Operator *op = new Operator((yylsp[(2) - (3)]), "=");
    (yyval.expr) = new AssignExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
  }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 547 "latte-parse.yy"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 554 "latte-parse.yy"
    {
    
    }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 562 "latte-parse.yy"
    { 
      (yyval.expr) = new Call(Join((yylsp[(1) - (4)]),(yylsp[(4) - (4)])), NULL, new Identifier((yylsp[(1) - (4)]),(yyvsp[(1) - (4)].identifier)), (yyvsp[(3) - (4)].exprList)); 
    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 566 "latte-parse.yy"
    {
      (yyval.expr) = new Call(Join((yylsp[(1) - (6)]),(yylsp[(6) - (6)])), (yyvsp[(1) - (6)].expr), new Identifier((yylsp[(3) - (6)]),(yyvsp[(3) - (6)].identifier)), (yyvsp[(5) - (6)].exprList)); 
    }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 572 "latte-parse.yy"
    { (yyval.exprList) = (yyvsp[(1) - (1)].exprList); }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 573 "latte-parse.yy"
    { (yyval.exprList) = new List<Expr*>; }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 577 "latte-parse.yy"
    { (yyval.expr) = new FieldAccess(NULL, new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier))); }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 578 "latte-parse.yy"
    { (yyval.expr) = new FieldAccess((yyvsp[(1) - (3)].expr), new Identifier((yylsp[(3) - (3)]), (yyvsp[(3) - (3)].identifier))); }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 579 "latte-parse.yy"
    { (yyval.expr) = new ArrayAccess(Join((yylsp[(1) - (4)]), (yylsp[(4) - (4)])), (yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 584 "latte-parse.yy"
    { (yyval.expr) = new IntConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].integerConstant)); }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 585 "latte-parse.yy"
    { (yyval.expr) = new DoubleConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].doubleConstant)); }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 586 "latte-parse.yy"
    { (yyval.expr) = new BoolConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].boolConstant)); }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 587 "latte-parse.yy"
    { (yyval.expr) = new StringConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].stringConstant)); }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 588 "latte-parse.yy"
    { (yyval.expr) = new NullConstant((yylsp[(1) - (1)])); }
    break;



/* Line 1455 of yacc.c  */
#line 2836 "latte-parse.cc"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 591 "latte-parse.yy"


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

