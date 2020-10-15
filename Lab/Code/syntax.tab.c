/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "./syntax.y" /* yacc.c:339  */

	#include"common.h"
	#include<stdio.h>
	extern SynUnit* init(LexType, int);
	extern void appendSyn(SynUnit*, SynUnit*);
	extern void appendLex(SynUnit*, LexType);
	extern void appendLexINT(SynUnit*, LexType, int);
	extern void appendLexFLOAT(SynUnit*, LexType, float);
	extern void appendLexTYPE(SynUnit*, LexType, bool);
	extern void appendLexID(SynUnit*, LexType, char*);
	#include"lex.yy.c"
	void yyerror(char const *s);

#line 80 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "./syntax.y" /* yacc.c:355  */

	#include"common.h"

#line 114 "./syntax.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 0,
    FLOAT = 1,
    ID = 2,
    TYPE = 15,
    SEMI = 3,
    COMMA = 4,
    LC = 20,
    RC = 21,
    STRUCT = 22,
    RETURN = 23,
    IF = 24,
    ELSE = 25,
    WHILE = 26,
    ASSIGNOP = 5,
    OR = 12,
    AND = 11,
    RELOP = 6,
    PLUS = 7,
    MINUS = 8,
    STAR = 9,
    DIV = 10,
    NOT = 14,
    LP = 16,
    RP = 17,
    LB = 18,
    RB = 19,
    DOT = 13,
    UMINUS = 258
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "./syntax.y" /* yacc.c:355  */

	int type_int;
	float type_float;
	char *type_str;
	bool type_bool;
	struct SynUnit* type_syn;

#line 165 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "./syntax.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   258

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     3,     4,     6,     7,    15,    18,    19,    20,    21,
      22,    17,    16,    28,    23,     5,    24,    25,    26,    27,
       8,     9,    10,    11,    12,    13,    14,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    65,    65,    72,    77,    80,    86,    91,    97,    98,
     100,   104,   110,   114,   118,   123,   131,   136,   138,   142,
     144,   151,   155,   162,   164,   171,   178,   184,   188,   190,
     197,   204,   206,   211,   213,   218,   222,   228,   236,   246,
     254,   255,   256,   257,   261,   266,   268,   274,   276,   280,
     286,   287,   289,   293,   299,   303,   309,   315,   321,   327,
     333,   339,   345,   351,   357,   362,   367,   374,   380,   387,
     393,   397,   401,   406,   412,   416,   417
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"interger\"", "error", "$undefined", "\"float\"", "\"identifier\"",
  "TYPE", "\";\"", "\",\"", "\"{\"", "\"}\"", "\"struct\"", "\"return\"",
  "\"if\"", "\"else\"", "\"while\"", "\"=\"", "\"||\"", "\"&&\"",
  "\"relational operator\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"!\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\".\"", "UMINUS", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "ParamList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,     1,     2,    15,     3,     4,    20,    21,
      22,    23,    24,    25,    26,     5,    12,    11,     6,     7,
       8,     9,    10,    14,    16,    17,    18,    19,    13,   258
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -75

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     180,     4,   -73,    97,    19,   -73,   180,   183,   -73,    71,
     -73,    56,    87,    20,    43,   -73,   -73,   -73,    83,    71,
     -73,   100,    16,    56,    58,   102,    44,   -73,   -73,    44,
     -73,   -73,   -73,   103,    83,   124,   -73,    42,   -73,   130,
     119,   155,   -73,   141,   117,    44,   157,   -73,   -73,   143,
     -73,    90,   -73,    42,   190,     5,   176,   126,   -73,   154,
     -73,   150,   175,     8,    24,   175,   175,   175,   -73,   185,
     117,   187,   -73,   -73,   -73,   -73,   -73,   182,    99,   -73,
     182,   182,   -73,    89,   204,   135,   175,   153,   175,   186,
     186,   218,   -73,   -73,   -73,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   196,   194,   -73,   -73,   274,   -73,
     -73,   209,   -73,    60,   192,   -73,   153,   -73,   232,   -73,
     246,   -73,   274,   286,   297,   307,    34,    34,   186,   186,
     260,   -73,   168,   168,   168,   -73,   -73,   153,   153,   -73,
     -73,   -73,   -73,   198,   -73,   153,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    13,     0,     0,     2,     0,     0,    14,     0,
       8,     0,     0,    20,     0,    16,     1,     3,     0,    21,
       6,     0,     0,     0,     0,     0,    45,     9,    17,    45,
      21,    12,     5,     0,     0,     0,     7,     0,    25,     0,
       0,    27,    31,     0,     0,    45,     0,    23,    11,     0,
      28,     0,    24,     0,     0,     0,     0,     0,    71,     0,
      72,    70,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    44,    15,    22,    26,    47,     0,     0,    46,
       0,     0,    40,     0,     0,     0,     0,     0,     0,    64,
      65,     0,    30,    32,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    54,    53,    51,
      49,     0,    67,     0,     0,    36,     0,    41,     0,    43,
       0,    63,    55,    57,    56,    58,    59,    60,    61,    62,
       0,    69,     0,     0,     0,    66,    42,     0,     0,    68,
      75,    76,    73,    37,    39,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   212,   -73,    35,     1,   -73,   -73,   -73,    11,
     220,    21,   -73,    -9,   158,   -72,    65,   -73,    27,   -73,
     -62,    18
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    21,    39,     8,    14,    15,    55,
      11,    40,    41,    68,    69,    70,    44,    45,    56,    57,
      71,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,     7,    27,    89,    90,    91,    33,     7,     9,    85,
      10,   -52,   -52,   117,    36,   119,   108,    33,    22,    16,
      78,   113,   -10,    34,   118,    87,   120,    43,   -18,    22,
      43,    35,    86,   122,   123,   124,   125,   126,   127,   128,
     129,   130,    35,    37,   136,    22,    43,     2,    88,     2,
      51,    29,     3,    31,     3,   101,   102,    25,    50,    37,
     103,   133,   104,     2,    26,   143,   144,   134,     3,    48,
     113,   113,   113,   146,    75,    95,    96,    97,    98,    99,
     100,   101,   102,    38,    18,   -74,   103,    30,   104,    58,
     111,    33,    60,    61,    46,    24,    28,   -29,    12,    58,
     107,    13,    60,    61,   106,   -19,    32,   109,   110,    65,
      72,    42,    66,    67,   112,   -29,    35,    58,    59,    65,
      60,    61,    66,    67,    49,    26,   -33,    80,    62,    63,
      47,    64,   -48,    81,    30,    58,    59,    65,    60,    61,
      66,    67,    54,    26,    52,    30,    62,    63,   116,    64,
     140,   141,   142,    58,    59,    65,    60,    61,    66,    67,
      82,    26,    53,    42,    62,    63,    73,    64,    58,   111,
      74,    60,    61,    65,    83,    58,    66,    67,    60,    61,
      -4,     1,    79,   105,    18,     2,    30,    19,    65,    20,
       3,    66,    67,    94,    92,    65,    76,    77,    66,    67,
     131,    77,    95,    96,    97,    98,    99,   100,   101,   102,
     115,   145,   103,   103,   104,   104,   132,   135,    17,    95,
      96,    97,    98,    99,   100,   101,   102,    23,    93,     0,
     103,     0,   104,    95,    96,    97,    98,    99,   100,   101,
     102,     0,     0,   121,   103,     0,   104,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,   137,   103,     0,
     104,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   138,   103,     0,   104,    95,    96,    97,    98,    99,
     100,   101,   102,     0,     0,     0,   103,   139,   104,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
     103,     0,   104,    97,    98,    99,   100,   101,   102,     0,
       0,     0,   103,     0,   104,    98,    99,   100,   101,   102,
       0,     0,     0,   103,     0,   104,    99,   100,   101,   102,
       0,     0,     0,   103,     0,   104
};

static const yytype_int16 yycheck[] =
{
      62,     0,    11,    65,    66,    67,     1,     6,     4,     1,
       6,     6,     7,    85,    23,    87,    78,     1,     7,     0,
      15,    83,     6,     7,    86,     1,    88,    26,     8,    18,
      29,    26,    24,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    26,     1,   116,    34,    45,     5,    24,     5,
      39,     8,    10,    18,    10,    21,    22,     1,    37,     1,
      26,     1,    28,     5,     8,   137,   138,     7,    10,    34,
     132,   133,   134,   145,    53,    15,    16,    17,    18,    19,
      20,    21,    22,    25,     1,    25,    26,     4,    28,     0,
       1,     1,     3,     4,    29,    24,     9,     7,     1,     0,
       1,     4,     3,     4,    77,     8,     6,    80,    81,    20,
      45,     9,    23,    24,    25,    25,    26,     0,     1,    20,
       3,     4,    23,    24,     0,     8,     9,     1,    11,    12,
      27,    14,     6,     7,     4,     0,     1,    20,     3,     4,
      23,    24,     1,     8,    25,     4,    11,    12,    13,    14,
     132,   133,   134,     0,     1,    20,     3,     4,    23,    24,
       6,     8,     7,     9,    11,    12,     9,    14,     0,     1,
      27,     3,     4,    20,    24,     0,    23,    24,     3,     4,
       0,     1,     6,     1,     1,     5,     4,     4,    20,     6,
      10,    23,    24,     6,     9,    20,     6,     7,    23,    24,
       4,     7,    15,    16,    17,    18,    19,    20,    21,    22,
       6,    13,    26,    26,    28,    28,     7,    25,     6,    15,
      16,    17,    18,    19,    20,    21,    22,     7,    70,    -1,
      26,    -1,    28,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    25,    26,    -1,    28,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    -1,
      28,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    -1,    28,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    26,    27,    28,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      26,    -1,    28,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    26,    -1,    28,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    26,    -1,    28,    19,    20,    21,    22,
      -1,    -1,    -1,    26,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,    10,    31,    32,    33,    35,    36,     4,
       6,    40,     1,     4,    37,    38,     0,    32,     1,     4,
       6,    34,    39,    40,    24,     1,     8,    43,     9,     8,
       4,    34,     6,     1,     7,    26,    43,     1,    25,    35,
      41,    42,     9,    35,    46,    47,    46,    27,    34,     0,
      41,    39,    25,     7,     1,    39,    48,    49,     0,     1,
       3,     4,    11,    12,    14,    20,    23,    24,    43,    44,
      45,    50,    46,     9,    27,    41,     6,     7,    15,     6,
       1,     7,     6,    24,    50,     1,    24,     1,    24,    50,
      50,    50,     9,    44,     6,    15,    16,    17,    18,    19,
      20,    21,    22,    26,    28,     1,    48,     1,    50,    48,
      48,     1,    25,    50,    51,     6,    13,    45,    50,    45,
      50,    25,    50,    50,    50,    50,    50,    50,    50,    50,
      50,     4,     7,     1,     7,    25,    45,    25,    25,    27,
      51,    51,    51,    45,    45,    13,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    33,
      34,    34,    34,    35,    35,    36,    36,    36,    37,    37,
      38,    39,    39,    39,    40,    40,    41,    41,    41,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    46,    46,    47,    47,    48,    48,
      48,    48,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     3,
       1,     3,     2,     1,     1,     5,     2,     3,     1,     0,
       1,     1,     4,     3,     4,     3,     3,     1,     2,     2,
       4,     2,     2,     0,     2,     1,     3,     5,     7,     5,
       2,     3,     4,     3,     2,     0,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     3,     1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
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
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 65 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Program, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
		start = (yyval.type_syn);
}
#line 1735 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 72 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDefList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1745 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 77 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_syn) = NULL;}
#line 1751 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 80 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 1762 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 86 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 1772 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 91 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1783 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 97 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1789 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 98 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1795 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 100 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1804 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 104 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ExtDecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1815 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 110 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1821 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 114 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Specifier, (yyloc).first_line);
		appendLexTYPE((yyval.type_syn), TYPE, (yyvsp[0].type_bool));
	}
#line 1830 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 118 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Specifier, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1839 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(StructSpecifier, (yyloc).first_line);
		appendLex((yyval.type_syn), STRUCT);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LC);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RC);
}
#line 1852 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 131 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(StructSpecifier, (yyloc).first_line);
		appendLex((yyval.type_syn), STRUCT);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1862 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 136 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1868 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 138 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(OptTag, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 1877 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 142 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_syn) = NULL;}
#line 1883 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 144 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Tag, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 1892 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 151 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(VarDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 1901 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 155 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(VarDec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LB);
		appendLexINT((yyval.type_syn), INT, (yyvsp[-1].type_int));
		appendLex((yyval.type_syn), RB);
	}
#line 1913 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 162 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1919 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 164 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(FunDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-3].type_str));
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 1931 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 171 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(FunDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-2].type_str));
		appendLex((yyval.type_syn), LP);
		appendLex((yyval.type_syn), RP);
	}
#line 1942 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 178 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ParamList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1953 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 184 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ParamList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1962 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 188 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1968 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 190 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(ParamDec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1978 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 197 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(CompSt, (yyloc).first_line);
		appendLex((yyval.type_syn), LC);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RC);
	}
#line 1990 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 204 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 1996 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 206 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(StmtList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2006 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 211 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_syn) = NULL;}
#line 2012 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 213 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 2022 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 218 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2031 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 222 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), RETURN);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 2042 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 228 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), IF);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2055 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 236 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), IF);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-4].type_syn));
		appendLex((yyval.type_syn), RP);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), ELSE);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2070 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 246 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), WHILE);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2083 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 254 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2089 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 255 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2095 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 256 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2101 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 257 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2107 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 261 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(DefList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2117 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 266 "./syntax.y" /* yacc.c:1646  */
    {(yyval.type_syn) = NULL;}
#line 2123 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 268 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Def, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 2134 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 274 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2140 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 276 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(DecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2149 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 280 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(DecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2160 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 286 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2166 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 287 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2172 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 289 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Dec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2181 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 293 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Dec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), ASSIGNOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2192 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 299 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2198 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 303 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), ASSIGNOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2209 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 309 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), AND);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2220 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 315 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), OR);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2231 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 321 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RELOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2242 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 327 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), PLUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2253 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 333 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), MINUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2264 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 339 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), STAR);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2275 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 345 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), DIV);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2286 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 351 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 2297 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 357 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), MINUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2307 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 362 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), NOT);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2317 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 367 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-3].type_str));
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 2329 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 374 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-2].type_str));
		appendLex((yyval.type_syn), LP);
		appendLex((yyval.type_syn), RP);
	}
#line 2340 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 380 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LB);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RB);
	}
#line 2352 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 387 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), DOT);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2363 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 393 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2372 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 397 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexINT((yyval.type_syn), INT, (yyvsp[0].type_int));
	}
#line 2381 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 401 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexFLOAT((yyval.type_syn), FLOAT, (yyvsp[0].type_float));
	}
#line 2390 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 406 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Args, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2401 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 412 "./syntax.y" /* yacc.c:1646  */
    {
		(yyval.type_syn) = init(Args, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2410 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 416 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2416 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 417 "./syntax.y" /* yacc.c:1646  */
    {yyclearin;}
#line 2422 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2426 "./syntax.tab.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if 1
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 419 "./syntax.y" /* yacc.c:1906  */

void yyerror(char const *s){
	printf("Error type B at Line %d:%d: %s\n", yylloc.first_line, yylloc.first_column ,s);
}
