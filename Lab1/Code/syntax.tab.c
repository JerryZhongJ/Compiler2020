/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./syntax.y"

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

#line 84 "./syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "./syntax.y"

	#include"common.h"

#line 131 "./syntax.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 260,
    FLOAT = 261,
    ID = 262,
    TYPE = 275,
    SEMI = 263,
    COMMA = 264,
    LC = 280,
    RC = 281,
    STRUCT = 282,
    RETURN = 283,
    IF = 284,
    ELSE = 285,
    WHILE = 286,
    ASSIGNOP = 265,
    OR = 272,
    AND = 271,
    RELOP = 266,
    PLUS = 267,
    MINUS = 268,
    STAR = 269,
    DIV = 270,
    NOT = 274,
    LP = 276,
    RP = 277,
    LB = 278,
    RB = 279,
    DOT = 273,
    UMINUS = 288,
    PRIOR = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "./syntax.y"

	int type_int;
	float type_float;
	char *type_str;
	bool type_bool;
	struct SynUnit* type_syn;

#line 182 "./syntax.tab.c"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

#define YYUNDEFTOK  2
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       3,     4,     5,     7,     8,    16,    19,    20,    21,    22,
      23,    18,    17,    29,    24,     6,    25,    26,    27,    28,
       9,    10,    11,    12,    13,    14,    15,     2,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    77,    82,    83,    86,    92,    97,   103,
     104,   106,   110,   119,   123,   128,   136,   142,   146,   148,
     155,   159,   167,   174,   181,   187,   191,   193,   200,   208,
     210,   215,   216,   217,   219,   224,   228,   234,   242,   252,
     260,   261,   262,   263,   267,   272,   273,   275,   285,   289,
     298,   302,   312,   318,   324,   330,   336,   342,   348,   354,
     360,   366,   371,   376,   383,   389,   396,   402,   406,   410,
     415,   421
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"interger\"", "\"float\"",
  "\"identifier\"", "TYPE", "\";\"", "\",\"", "\"{\"", "\"}\"",
  "\"struct\"", "\"return\"", "\"if\"", "\"else\"", "\"while\"", "\"=\"",
  "\"||\"", "\"&&\"", "\"relational operator\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"!\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\".\"", "UMINUS",
  "PRIOR", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec",
  "ParamList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   287,   260,   261,   262,   275,   263,   264,   280,
     281,   282,   283,   284,   285,   286,   265,   272,   271,   266,
     267,   268,   269,   270,   274,   276,   277,   278,   279,   273,
     288,   289
};
# endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-46)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     104,   388,   -69,    35,    42,   -69,   104,    17,   -69,   376,
     -69,    88,   -69,   -69,    46,    62,   -69,   -69,   -69,    65,
     -69,    95,     8,    16,   -69,    88,    90,   138,    88,   134,
       7,   -69,    90,   103,    97,   -69,   -69,   -69,     5,   114,
     119,   113,   -69,   -69,   105,    58,    13,    14,    58,    58,
      58,   -69,   121,   163,   237,   -69,   122,   118,   -69,    90,
     107,   128,   -69,   124,    58,   -69,    90,   -69,   -69,   226,
     254,   188,    58,   213,    58,    27,    27,   284,   -69,    63,
     -69,   -69,    58,    58,    58,    58,    58,    58,    58,    58,
      58,   141,   -69,   -69,   127,   -69,   118,   -69,   340,   -69,
     -69,   270,   123,   -69,   101,   213,   -69,   298,   -69,   312,
     -69,   138,   340,   352,   381,   219,   240,   240,    27,    27,
     326,   -69,   -69,    58,   -69,   -69,   213,   213,   -69,   -69,
     -69,   142,   -69,   213,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    13,    18,     0,     2,     0,     0,    14,     0,
       9,     0,     5,    10,    19,     0,    16,     1,     3,    20,
       7,     0,    11,     0,    29,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     8,    46,    20,    50,     0,
      48,     0,    68,    69,    67,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,    44,     0,     0,    23,     0,
       0,    25,    12,     0,     0,    47,     0,    40,    32,     0,
       0,     0,     0,     0,     0,    61,    62,     0,    28,     0,
      30,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,    26,    27,    22,     0,    21,    51,    49,
      64,    71,     0,    36,     0,     0,    41,     0,    43,     0,
      60,     0,    52,    54,    53,    55,    56,    57,    58,    59,
       0,    66,    24,     0,    63,    42,     0,     0,    33,    65,
      70,    37,    39,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,    23,   -69,   125,     0,   -69,   -69,   -69,    -6,
     -69,   -53,   -69,    18,   -25,   -68,    52,    76,    92,   -69,
     -38,    37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,    12,     6,    21,    26,     8,    15,    16,    22,
      23,    60,    61,    51,    68,    53,    27,    28,    39,    40,
      54,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,     7,    52,   106,    93,   108,     7,    70,    57,     7,
      75,    76,    77,     2,    71,    73,    32,    34,     3,    13,
      38,    64,    19,     5,    20,    11,    98,    13,    80,    18,
      59,   101,    33,    58,   107,    33,   109,   125,    72,    74,
      14,    35,    17,   122,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    94,    90,   -17,    91,    59,   131,   132,
      38,    42,    43,    44,    41,   134,    42,    43,    44,     2,
      67,    29,    11,   -31,     3,    45,    46,    36,    47,    48,
      55,    56,    49,    50,    48,   101,   128,    49,    50,    25,
      30,   -45,   -45,   -45,     2,    37,    59,   -45,   -45,     3,
     -45,   -45,    31,   -45,    -4,     1,    63,    24,    67,   -45,
       2,    24,   -45,   -45,    41,     3,    42,    43,    44,    57,
      67,    65,    11,   -31,     2,    45,    46,    66,    47,     3,
      69,    78,    92,    95,    48,    25,    96,    49,    50,    41,
       2,    42,    43,    44,   -45,     3,   121,    11,   -31,   124,
      45,    46,    97,    47,    33,   111,   133,    62,    99,    48,
     130,     0,    49,    50,    79,     0,    42,    43,    44,     0,
       0,     0,    11,   -31,     0,    45,    46,     0,    47,     0,
       0,     0,     0,     0,    48,     0,     0,    49,    50,   104,
       0,    42,    43,    44,     0,     0,     0,    11,     0,     0,
      45,    46,   105,    47,     0,     0,     0,     0,     0,    48,
       0,     0,    49,    50,   104,     0,    42,    43,    44,     0,
       0,     0,    11,     0,     0,    45,    46,     0,    47,    42,
      43,    44,     0,     0,    48,     0,     0,    49,    50,    86,
      87,    88,    89,     0,    81,     0,    90,    48,    91,     0,
      49,    50,   100,    82,    83,    84,    85,    86,    87,    88,
      89,   103,    88,    89,    90,     0,    91,    90,     0,    91,
      82,    83,    84,    85,    86,    87,    88,    89,   123,     0,
       0,    90,     0,    91,     0,     0,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    90,     0,    91,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
     110,    90,     0,    91,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,   126,    90,     0,    91,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,   127,    90,
       0,    91,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,    90,   129,    91,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    90,     0,    91,
      84,    85,    86,    87,    88,    89,    -4,     9,     0,    90,
       0,    91,     2,    10,     0,    11,    24,     3,    -4,     9,
       0,     0,     0,     0,     2,    10,     0,    11,     0,     3,
      85,    86,    87,    88,    89,     0,     0,     0,    90,     0,
      91
};

static const yytype_int16 yycheck[] =
{
       0,     1,    27,    71,    57,    73,     6,    45,     1,     9,
      48,    49,    50,     6,     1,     1,     8,     1,    11,     1,
      26,    16,     5,     0,     7,     9,    64,     9,    53,     6,
      30,    69,    27,    26,    72,    27,    74,   105,    25,    25,
       5,    23,     0,    96,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    59,    27,     9,    29,    57,   126,   127,
      66,     3,     4,     5,     1,   133,     3,     4,     5,     6,
       7,     9,     9,    10,    11,    12,    13,    25,    15,    21,
      28,    29,    24,    25,    21,   123,   111,    24,    25,     1,
      25,     3,     4,     5,     6,     5,    96,     9,    10,    11,
      12,    13,     7,    15,     0,     1,     3,    10,     7,    21,
       6,    10,    24,    25,     1,    11,     3,     4,     5,     1,
       7,     7,     9,    10,     6,    12,    13,     8,    15,    11,
      25,    10,    10,    26,    21,     1,     8,    24,    25,     1,
       6,     3,     4,     5,    10,    11,     5,     9,    10,    26,
      12,    13,    28,    15,    27,    79,    14,    32,    66,    21,
     123,    -1,    24,    25,     1,    -1,     3,     4,     5,    -1,
      -1,    -1,     9,    10,    -1,    12,    13,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    25,     1,
      -1,     3,     4,     5,    -1,    -1,    -1,     9,    -1,    -1,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    24,    25,     1,    -1,     3,     4,     5,    -1,
      -1,    -1,     9,    -1,    -1,    12,    13,    -1,    15,     3,
       4,     5,    -1,    -1,    21,    -1,    -1,    24,    25,    20,
      21,    22,    23,    -1,     7,    -1,    27,    21,    29,    -1,
      24,    25,    26,    16,    17,    18,    19,    20,    21,    22,
      23,     7,    22,    23,    27,    -1,    29,    27,    -1,    29,
      16,    17,    18,    19,    20,    21,    22,    23,     8,    -1,
      -1,    27,    -1,    29,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    27,    -1,    29,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    -1,    29,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    -1,    29,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    29,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    27,    28,    29,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    27,    -1,    29,
      18,    19,    20,    21,    22,    23,     0,     1,    -1,    27,
      -1,    29,     6,     7,    -1,     9,    10,    11,     0,     1,
      -1,    -1,    -1,    -1,     6,     7,    -1,     9,    -1,    11,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    27,    -1,
      29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    11,    33,    34,    35,    37,    38,     1,
       7,     9,    34,    45,     5,    39,    40,     0,    34,     5,
       7,    36,    41,    42,    10,     1,    37,    48,    49,     9,
      25,     7,     8,    27,     1,    45,    48,     5,    41,    50,
      51,     1,     3,     4,     5,    12,    13,    15,    21,    24,
      25,    45,    46,    47,    52,    48,    48,     1,    26,    37,
      43,    44,    36,     3,    16,     7,     8,     7,    46,    25,
      52,     1,    25,     1,    25,    52,    52,    52,    10,     1,
      46,     7,    16,    17,    18,    19,    20,    21,    22,    23,
      27,    29,    10,    43,    41,    26,     8,    28,    52,    50,
      26,    52,    53,     7,     1,    14,    47,    52,    47,    52,
      26,    49,    52,    52,    52,    52,    52,    52,    52,    52,
      52,     5,    43,     8,    26,    47,    26,    26,    46,    28,
      53,    47,    47,    14,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    34,    35,    35,    35,    35,
      35,    36,    36,    37,    37,    38,    38,    39,    39,    40,
      41,    41,    42,    42,    43,    43,    43,    44,    45,    45,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    48,    49,    50,    50,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     3,     2,     3,     2,
       2,     1,     3,     1,     1,     5,     2,     1,     0,     1,
       1,     4,     4,     3,     3,     1,     2,     2,     4,     2,
       2,     0,     2,     4,     2,     1,     3,     5,     7,     5,
       2,     3,     4,     3,     2,     0,     2,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
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
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
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
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[+*yyesp];
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
        YYPTRDIFF_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
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
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
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
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyesa, yy_state_t **yyes,
                YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

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

    YYPTRDIFF_T yystacksize;

    yy_state_t yyesa[20];
    yy_state_t *yyes;
    YYPTRDIFF_T yyes_capacity;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
  yyes_capacity = 20;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2:
#line 70 "./syntax.y"
                     {
		(yyval.type_syn) = init(Program, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
		start = (yyval.type_syn);
}
#line 1856 "./syntax.tab.c"
    break;

  case 3:
#line 77 "./syntax.y"
                               {
		(yyval.type_syn) = init(ExtDefList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1866 "./syntax.tab.c"
    break;

  case 4:
#line 82 "./syntax.y"
          {(yyval.type_syn) = NULL;}
#line 1872 "./syntax.tab.c"
    break;

  case 5:
#line 83 "./syntax.y"
                           {/*yyerrok;*/(yyval.type_syn) = (yyvsp[0].type_syn);}
#line 1878 "./syntax.tab.c"
    break;

  case 6:
#line 86 "./syntax.y"
                                   {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 1889 "./syntax.tab.c"
    break;

  case 7:
#line 92 "./syntax.y"
                         {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 1899 "./syntax.tab.c"
    break;

  case 8:
#line 97 "./syntax.y"
                                  {
		(yyval.type_syn) = init(ExtDef, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1910 "./syntax.tab.c"
    break;

  case 9:
#line 103 "./syntax.y"
                     {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 1916 "./syntax.tab.c"
    break;

  case 10:
#line 104 "./syntax.y"
                       {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 1922 "./syntax.tab.c"
    break;

  case 11:
#line 106 "./syntax.y"
                    {
		(yyval.type_syn) = init(ExtDecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1931 "./syntax.tab.c"
    break;

  case 12:
#line 110 "./syntax.y"
                                  {
		(yyval.type_syn) = init(ExtDecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1942 "./syntax.tab.c"
    break;

  case 13:
#line 119 "./syntax.y"
                 {
		(yyval.type_syn) = init(Specifier, (yyloc).first_line);
		appendLexTYPE((yyval.type_syn), TYPE, (yyvsp[0].type_bool));
	}
#line 1951 "./syntax.tab.c"
    break;

  case 14:
#line 123 "./syntax.y"
                          {
		(yyval.type_syn) = init(Specifier, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1960 "./syntax.tab.c"
    break;

  case 15:
#line 128 "./syntax.y"
                                              {
		(yyval.type_syn) = init(StructSpecifier, (yyloc).first_line);
		appendLex((yyval.type_syn), STRUCT);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LC);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RC);
}
#line 1973 "./syntax.tab.c"
    break;

  case 16:
#line 136 "./syntax.y"
                     {
		(yyval.type_syn) = init(StructSpecifier, (yyloc).first_line);
		appendLex((yyval.type_syn), STRUCT);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 1983 "./syntax.tab.c"
    break;

  case 17:
#line 142 "./syntax.y"
            {
		(yyval.type_syn) = init(OptTag, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 1992 "./syntax.tab.c"
    break;

  case 18:
#line 146 "./syntax.y"
          {(yyval.type_syn) = NULL;}
#line 1998 "./syntax.tab.c"
    break;

  case 19:
#line 148 "./syntax.y"
         {
		(yyval.type_syn) = init(Tag, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2007 "./syntax.tab.c"
    break;

  case 20:
#line 155 "./syntax.y"
            {
		(yyval.type_syn) = init(VarDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2016 "./syntax.tab.c"
    break;

  case 21:
#line 159 "./syntax.y"
                           {
		(yyval.type_syn) = init(VarDec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LB);
		appendLexINT((yyval.type_syn), INT, (yyvsp[-1].type_int));
		appendLex((yyval.type_syn), RB);
	}
#line 2028 "./syntax.tab.c"
    break;

  case 22:
#line 167 "./syntax.y"
                            {
		(yyval.type_syn) = init(FunDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-3].type_str));
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 2040 "./syntax.tab.c"
    break;

  case 23:
#line 174 "./syntax.y"
                   {
		(yyval.type_syn) = init(FunDec, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-2].type_str));
		appendLex((yyval.type_syn), LP);
		appendLex((yyval.type_syn), RP);
	}
#line 2051 "./syntax.tab.c"
    break;

  case 24:
#line 181 "./syntax.y"
                                     {
		(yyval.type_syn) = init(ParamList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2062 "./syntax.tab.c"
    break;

  case 25:
#line 187 "./syntax.y"
                   {
		(yyval.type_syn) = init(ParamList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2071 "./syntax.tab.c"
    break;

  case 26:
#line 191 "./syntax.y"
                          {/*yyerrok;*/(yyval.type_syn)=(yyvsp[0].type_syn);}
#line 2077 "./syntax.tab.c"
    break;

  case 27:
#line 193 "./syntax.y"
                            {
		(yyval.type_syn) = init(ParamDec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2087 "./syntax.tab.c"
    break;

  case 28:
#line 200 "./syntax.y"
                                {
		(yyval.type_syn) = init(CompSt, (yyloc).first_line);
		appendLex((yyval.type_syn), LC);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RC);
		
	}
#line 2100 "./syntax.tab.c"
    break;

  case 29:
#line 208 "./syntax.y"
                   {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 2106 "./syntax.tab.c"
    break;

  case 30:
#line 210 "./syntax.y"
                         {
		(yyval.type_syn) = init(StmtList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2116 "./syntax.tab.c"
    break;

  case 31:
#line 215 "./syntax.y"
          {(yyval.type_syn) = NULL;}
#line 2122 "./syntax.tab.c"
    break;

  case 32:
#line 216 "./syntax.y"
                         {/*yyerrok;*/(yyval.type_syn) = (yyvsp[0].type_syn);}
#line 2128 "./syntax.tab.c"
    break;

  case 33:
#line 217 "./syntax.y"
                                  {/*yyerrok;*/(yyval.type_syn) = NULL;}
#line 2134 "./syntax.tab.c"
    break;

  case 34:
#line 219 "./syntax.y"
                {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 2144 "./syntax.tab.c"
    break;

  case 35:
#line 224 "./syntax.y"
                 {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2153 "./syntax.tab.c"
    break;

  case 36:
#line 228 "./syntax.y"
                          {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), RETURN);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
	}
#line 2164 "./syntax.tab.c"
    break;

  case 37:
#line 234 "./syntax.y"
                            {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), IF);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2177 "./syntax.tab.c"
    break;

  case 38:
#line 242 "./syntax.y"
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
#line 2192 "./syntax.tab.c"
    break;

  case 39:
#line 252 "./syntax.y"
                               {
		(yyval.type_syn) = init(Stmt, (yyloc).first_line);
		appendLex((yyval.type_syn), WHILE);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2205 "./syntax.tab.c"
    break;

  case 40:
#line 260 "./syntax.y"
                     {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 2211 "./syntax.tab.c"
    break;

  case 41:
#line 261 "./syntax.y"
                        {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 2217 "./syntax.tab.c"
    break;

  case 42:
#line 262 "./syntax.y"
                              {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 2223 "./syntax.tab.c"
    break;

  case 43:
#line 263 "./syntax.y"
                            {/*yyerrok;*/(yyval.type_syn)=NULL;}
#line 2229 "./syntax.tab.c"
    break;

  case 44:
#line 267 "./syntax.y"
                      {
		(yyval.type_syn) = init(DefList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2239 "./syntax.tab.c"
    break;

  case 45:
#line 272 "./syntax.y"
          {(yyval.type_syn) = NULL;}
#line 2245 "./syntax.tab.c"
    break;

  case 46:
#line 273 "./syntax.y"
                        {/*yyerrok;*/(yyval.type_syn) = (yyvsp[0].type_syn);}
#line 2251 "./syntax.tab.c"
    break;

  case 47:
#line 275 "./syntax.y"
                             {
		(yyval.type_syn) = init(Def, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), SEMI);
		
	}
#line 2263 "./syntax.tab.c"
    break;

  case 48:
#line 285 "./syntax.y"
              {
		(yyval.type_syn) = init(DecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2272 "./syntax.tab.c"
    break;

  case 49:
#line 289 "./syntax.y"
                            {
		(yyval.type_syn) = init(DecList, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2283 "./syntax.tab.c"
    break;

  case 50:
#line 298 "./syntax.y"
             {
		(yyval.type_syn) = init(Dec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2292 "./syntax.tab.c"
    break;

  case 51:
#line 302 "./syntax.y"
                             {
		(yyval.type_syn) = init(Dec, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), ASSIGNOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2303 "./syntax.tab.c"
    break;

  case 52:
#line 312 "./syntax.y"
                       {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), ASSIGNOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2314 "./syntax.tab.c"
    break;

  case 53:
#line 318 "./syntax.y"
                      {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), AND);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2325 "./syntax.tab.c"
    break;

  case 54:
#line 324 "./syntax.y"
                     {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), OR);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2336 "./syntax.tab.c"
    break;

  case 55:
#line 330 "./syntax.y"
                        {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), RELOP);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2347 "./syntax.tab.c"
    break;

  case 56:
#line 336 "./syntax.y"
                       {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), PLUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2358 "./syntax.tab.c"
    break;

  case 57:
#line 342 "./syntax.y"
                        {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), MINUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2369 "./syntax.tab.c"
    break;

  case 58:
#line 348 "./syntax.y"
                       {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), STAR);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2380 "./syntax.tab.c"
    break;

  case 59:
#line 354 "./syntax.y"
                      {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), DIV);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2391 "./syntax.tab.c"
    break;

  case 60:
#line 360 "./syntax.y"
                    {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 2402 "./syntax.tab.c"
    break;

  case 61:
#line 366 "./syntax.y"
                                 {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), MINUS);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2412 "./syntax.tab.c"
    break;

  case 62:
#line 371 "./syntax.y"
                  {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLex((yyval.type_syn), NOT);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2422 "./syntax.tab.c"
    break;

  case 63:
#line 376 "./syntax.y"
                        {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-3].type_str));
		appendLex((yyval.type_syn), LP);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RP);
	}
#line 2434 "./syntax.tab.c"
    break;

  case 64:
#line 383 "./syntax.y"
                   {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[-2].type_str));
		appendLex((yyval.type_syn), LP);
		appendLex((yyval.type_syn), RP);
	}
#line 2445 "./syntax.tab.c"
    break;

  case 65:
#line 389 "./syntax.y"
                        {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-3].type_syn));
		appendLex((yyval.type_syn), LB);
		appendSyn((yyval.type_syn), (yyvsp[-1].type_syn));
		appendLex((yyval.type_syn), RB);
	}
#line 2457 "./syntax.tab.c"
    break;

  case 66:
#line 396 "./syntax.y"
                     {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), DOT);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2468 "./syntax.tab.c"
    break;

  case 67:
#line 402 "./syntax.y"
             {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexID((yyval.type_syn), ID, (yyvsp[0].type_str));
	}
#line 2477 "./syntax.tab.c"
    break;

  case 68:
#line 406 "./syntax.y"
              {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexINT((yyval.type_syn), INT, (yyvsp[0].type_int));
	}
#line 2486 "./syntax.tab.c"
    break;

  case 69:
#line 410 "./syntax.y"
                {
		(yyval.type_syn) = init(Exp, (yyloc).first_line);
		appendLexFLOAT((yyval.type_syn), FLOAT, (yyvsp[0].type_float));
	}
#line 2495 "./syntax.tab.c"
    break;

  case 70:
#line 415 "./syntax.y"
                     {
		(yyval.type_syn) = init(Args, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[-2].type_syn));
		appendLex((yyval.type_syn), COMMA);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2506 "./syntax.tab.c"
    break;

  case 71:
#line 421 "./syntax.y"
             {
		(yyval.type_syn) = init(Args, (yyloc).first_line);
		appendSyn((yyval.type_syn), (yyvsp[0].type_syn));
	}
#line 2515 "./syntax.tab.c"
    break;


#line 2519 "./syntax.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 428 "./syntax.y"

void yyerror(char const *s){
	printf("Error type B at Line %d:%d: %s\n", yylloc.first_line, yylloc.first_column ,s);
}
