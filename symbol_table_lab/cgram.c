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
#line 1 "cgram.y" /* yacc.c:339  */

  /* grammar for subset of C. The grammar does not recognize all C syntax:
     For example:
     1. Character literals
     2. Structres
     3. Double constants
     4. Nested paraenthesis of the form "if((x == 1))"
     5. etc.
  */
# include <stdio.h>
# include <stdlib.h>
# include "cc.h"
# include "scan.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

#line 84 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    CON = 259,
    STR = 260,
    CHAR = 261,
    ELSE = 262,
    FLOAT = 263,
    DOUBLE = 264,
    FOR = 265,
    IF = 266,
    INT = 267,
    RESERVED = 268,
    RETURN = 269,
    WHILE = 270,
    DO = 271,
    CONTINUE = 272,
    BREAK = 273,
    GOTO = 274,
    LVAL = 275,
    SET = 276,
    SETOR = 277,
    SETXOR = 278,
    SETAND = 279,
    SETLSH = 280,
    SETRSH = 281,
    SETADD = 282,
    SETSUB = 283,
    SETMUL = 284,
    SETDIV = 285,
    SETMOD = 286,
    OR = 287,
    AND = 288,
    BITOR = 289,
    BITXOR = 290,
    BITAND = 291,
    EQ = 292,
    NE = 293,
    GT = 294,
    GE = 295,
    LT = 296,
    LE = 297,
    LSH = 298,
    RSH = 299,
    ADD = 300,
    SUB = 301,
    MUL = 302,
    DIV = 303,
    MOD = 304,
    UNARY = 305,
    NOT = 306,
    COM = 307
  };
#endif
/* Tokens.  */
#define ID 258
#define CON 259
#define STR 260
#define CHAR 261
#define ELSE 262
#define FLOAT 263
#define DOUBLE 264
#define FOR 265
#define IF 266
#define INT 267
#define RESERVED 268
#define RETURN 269
#define WHILE 270
#define DO 271
#define CONTINUE 272
#define BREAK 273
#define GOTO 274
#define LVAL 275
#define SET 276
#define SETOR 277
#define SETXOR 278
#define SETAND 279
#define SETLSH 280
#define SETRSH 281
#define SETADD 282
#define SETSUB 283
#define SETMUL 284
#define SETDIV 285
#define SETMOD 286
#define OR 287
#define AND 288
#define BITOR 289
#define BITXOR 290
#define BITAND 291
#define EQ 292
#define NE 293
#define GT 294
#define GE 295
#define LT 296
#define LE 297
#define LSH 298
#define RSH 299
#define ADD 300
#define SUB 301
#define MUL 302
#define DIV 303
#define MOD 304
#define UNARY 305
#define NOT 306
#define COM 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "cgram.y" /* yacc.c:355  */

   int inttype;
   char *str_ptr;
   struct sem_rec *rec_ptr;
   struct id_entry *id_ptr;

#line 235 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 252 "y.tab.c" /* yacc.c:358  */

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   395

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  209

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,    60,     2,     2,    54,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    53,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    57,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    45,    45,    48,    49,    52,    53,    56,    57,    60,
      61,    64,    65,    66,    69,    70,    71,    72,    75,    78,
      81,    82,    85,    86,    89,    90,    93,    95,    98,    99,
     102,   103,   106,   107,   110,   113,   116,   119,   122,   124,
     126,   128,   130,   132,   134,   136,   138,   140,   142,   144,
     146,   150,   151,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   166,   167,   170,   171,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   197,
     198,   199,   200,   201,   202,   203,   204,   207,   208
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CON", "STR", "CHAR", "ELSE",
  "FLOAT", "DOUBLE", "FOR", "IF", "INT", "RESERVED", "RETURN", "WHILE",
  "DO", "CONTINUE", "BREAK", "GOTO", "LVAL", "SET", "SETOR", "SETXOR",
  "SETAND", "SETLSH", "SETRSH", "SETADD", "SETSUB", "SETMUL", "SETDIV",
  "SETMOD", "OR", "AND", "BITOR", "BITXOR", "BITAND", "EQ", "NE", "GT",
  "GE", "LT", "LE", "LSH", "RSH", "ADD", "SUB", "MUL", "DIV", "MOD",
  "UNARY", "NOT", "COM", "';'", "','", "'['", "']'", "'}'", "'{'", "'('",
  "')'", "':'", "$accept", "prog", "externs", "extern", "dcls", "dcl",
  "dclr", "type", "func", "fhead", "fname", "fargs", "args", "bhead",
  "block", "stmts", "lblstmt", "labels", "s", "m", "n", "b", "stmt",
  "cexpro", "cexpr", "exprs", "expro", "expr", "lval", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    59,    44,    91,    93,   125,   123,    40,
      41,    58
};
# endif

#define YYPACT_NINF -183

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-183)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -183,     8,   138,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
      42,     7,  -183,  -183,   -46,  -183,    15,    43,  -183,   -36,
     108,   -25,   -11,  -183,    -2,  -183,  -183,   160,  -183,    15,
     -32,  -183,    -9,  -183,    27,  -183,  -183,   -29,    49,   179,
      56,  -183,    74,    92,   145,   148,   187,   187,  -183,  -183,
     187,  -183,  -183,   184,  -183,   247,   357,  -183,    33,  -183,
      33,  -183,   187,    45,  -183,   187,    48,    51,  -183,   263,
    -183,  -183,  -183,  -183,    99,    98,  -183,  -183,  -183,   213,
      33,    28,  -183,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,  -183,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,    15,    65,    15,   231,  -183,
     -14,   299,   102,   299,    48,   -28,   283,  -183,    48,  -183,
    -183,  -183,   101,  -183,   314,   328,   346,    77,    77,    88,
      88,  -183,  -183,  -183,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,  -183,  -183,  -183,   187,  -183,
    -183,  -183,  -183,  -183,  -183,   187,   187,   187,   187,   187,
     187,   -26,   141,  -183,   299,    48,    48,    48,  -183,   299,
     299,   299,   299,   299,   299,  -183,   110,   114,   106,   128,
    -183,   165,  -183,  -183,  -183,  -183,  -183,  -183,    48,   187,
    -183,  -183,   -17,  -183,  -183,  -183,   120,   121,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    21,    14,    15,    16,    17,     4,
       0,     0,     6,    28,     0,     5,     0,    11,     9,    37,
       0,     0,    11,    10,     0,    18,    29,     0,    22,     0,
       0,     7,     0,    12,    97,    95,    96,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,    50,    26,
       0,     7,    49,     0,    30,     0,    91,    24,     0,    23,
      19,    13,     0,     0,    32,    65,     0,    97,    47,     0,
      35,    34,    44,    45,     0,    97,    88,    89,    90,     0,
      28,    97,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,    63,     0,    66,     0,     0,    62,    48,     0,    37,
      46,    94,    37,    33,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    25,     8,    98,     0,    93,
      35,    61,    35,    35,    35,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    64,    51,     0,     0,    37,    53,
      54,    58,    56,    57,    55,    35,     0,     0,    52,    60,
      59,    35,    34,    35,    35,    36,    39,    37,     0,    65,
      35,    36,     0,    36,    37,    35,     0,     0,    35,    41,
      35,    35,    40,    42,    34,    37,    36,    35,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,  -183,   129,   183,   -15,    35,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,   113,  -102,  -183,  -179,   -41,
    -182,  -183,   133,  -183,   -87,  -183,    16,   -27,   152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     9,    60,   106,    18,   107,    12,    13,
      14,    21,    30,    51,    52,    19,    26,    53,   119,    71,
     190,    27,    54,   177,   115,   110,   112,   116,    56
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    23,    32,   187,   152,   153,   152,   153,     3,   195,
      17,   197,    69,    20,    57,   152,   153,   162,    22,    77,
      78,    25,    58,    79,   207,   205,    55,   151,    59,   118,
      65,   161,   154,    31,   175,   108,   111,    11,   113,     5,
     148,     6,     7,   196,    24,     8,   149,    61,    67,    35,
      36,    67,    35,    36,    33,    29,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   181,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   178,   179,
     180,    45,    62,    62,    45,   191,    63,    63,    64,   123,
     145,    46,   198,   105,    46,    15,    16,    47,    24,   114,
      47,   192,   -20,   206,    50,   109,    62,    50,    66,   165,
      63,   166,   167,   168,     5,    70,     6,     7,   146,    16,
       8,   164,    88,    89,    90,    91,    92,    72,   169,   170,
     171,   172,   173,   174,   182,    90,    91,    92,   152,   153,
     186,     4,   188,   189,     5,    73,     6,     7,    74,   194,
       8,    75,   120,    62,   199,   150,   176,   202,   163,   203,
     204,   153,   113,    34,    35,    36,   208,   184,    28,   183,
      37,    38,   185,   200,    39,    40,    41,    42,    43,    44,
      80,   201,    67,    35,    36,    10,    82,    81,    35,    36,
      67,    35,    36,   122,    37,    38,    45,    76,    39,    40,
      41,    42,    43,    44,     0,   193,    46,     0,     0,     0,
       0,     0,    47,    48,     0,    45,     0,     0,    49,    50,
      45,     0,     0,    45,     0,    46,     0,     0,     0,     0,
      46,    47,    68,    46,     0,     0,    47,    48,    50,    47,
       0,     0,    49,    50,     0,     0,    50,    83,    84,    85,
       0,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    92,     0,     0,    83,    84,    85,     0,     0,
       0,     0,     0,   121,    86,    87,    88,    89,    90,    91,
      92,    83,    84,    85,     0,     0,     0,   147,     0,     0,
      86,    87,    88,    89,    90,    91,    92,    83,    84,    85,
      93,     0,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    92,     0,     0,     0,   117,    83,    84,    85,
     155,   156,   157,   158,   159,   160,    86,    87,    88,    89,
      90,    91,    92,    83,    84,    85,     0,     0,     0,     0,
       0,     0,    86,    87,    88,    89,    90,    91,    92,    84,
      85,     0,     0,     0,     0,     0,     0,    86,    87,    88,
      89,    90,    91,    92,    85,     0,     0,     0,     0,     0,
       0,    86,    87,    88,    89,    90,    91,    92,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    86,
      87,    88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
      27,    16,     4,   182,    32,    33,    32,    33,     0,   191,
       3,   193,    39,    59,    29,    32,    33,   119,     3,    46,
      47,    57,    54,    50,   206,   204,    53,   114,    60,    70,
      59,   118,    60,    58,    60,    62,    63,     2,    65,     6,
      54,     8,     9,    60,    55,    12,    60,    56,     3,     4,
       5,     3,     4,     5,    56,    20,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,   168,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   165,   166,
     167,    36,    55,    55,    36,   187,    59,    59,    61,    61,
     105,    46,   194,    58,    46,    53,    54,    52,    55,    51,
      52,   188,    59,   205,    59,    60,    55,    59,    59,   150,
      59,   152,   153,   154,     6,    59,     8,     9,    53,    54,
      12,   148,    45,    46,    47,    48,    49,    53,   155,   156,
     157,   158,   159,   160,   175,    47,    48,    49,    32,    33,
     181,     3,   183,   184,     6,    53,     8,     9,     3,   190,
      12,     3,    53,    55,   195,    53,    15,   198,    57,   200,
     201,    33,   189,     3,     4,     5,   207,    53,    60,    59,
      10,    11,     7,    53,    14,    15,    16,    17,    18,    19,
      51,    60,     3,     4,     5,     2,    53,     3,     4,     5,
       3,     4,     5,    80,    10,    11,    36,    45,    14,    15,
      16,    17,    18,    19,    -1,   189,    46,    -1,    -1,    -1,
      -1,    -1,    52,    53,    -1,    36,    -1,    -1,    58,    59,
      36,    -1,    -1,    36,    -1,    46,    -1,    -1,    -1,    -1,
      46,    52,    53,    46,    -1,    -1,    52,    53,    59,    52,
      -1,    -1,    58,    59,    -1,    -1,    59,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    60,    43,    44,    45,    46,    47,    48,
      49,    34,    35,    36,    -1,    -1,    -1,    56,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    34,    35,    36,
      53,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    53,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    43,
      44,    45,    46,    47,    48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    63,    64,     0,     3,     6,     8,     9,    12,    65,
      67,    69,    70,    71,    72,    53,    54,     3,    68,    77,
      59,    73,     3,    68,    55,    57,    78,    83,    60,    69,
      74,    58,     4,    56,     3,     4,     5,    10,    11,    14,
      15,    16,    17,    18,    19,    36,    46,    52,    53,    58,
      59,    75,    76,    79,    84,    89,    90,    68,    54,    60,
      66,    56,    55,    59,    61,    59,    59,     3,    53,    89,
      59,    81,    53,    53,     3,     3,    90,    89,    89,    89,
      66,     3,    84,    34,    35,    36,    43,    44,    45,    46,
      47,    48,    49,    53,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    69,    67,    69,    89,    60,
      87,    89,    88,    89,    51,    86,    89,    53,    81,    80,
      53,    60,    77,    61,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    68,    53,    56,    54,    60,
      53,    86,    32,    33,    60,    37,    38,    39,    40,    41,
      42,    86,    78,    57,    89,    81,    81,    81,    81,    89,
      89,    89,    89,    89,    89,    60,    15,    85,    86,    86,
      86,    78,    81,    59,    53,     7,    81,    80,    81,    81,
      82,    78,    86,    88,    81,    82,    60,    82,    78,    81,
      53,    60,    81,    81,    81,    80,    78,    82,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    70,    71,
      72,    72,    73,    73,    74,    74,    75,    76,    77,    77,
      78,    78,    79,    79,    80,    81,    82,    83,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     0,     3,     2,
       3,     1,     3,     4,     1,     1,     1,     1,     3,     4,
       2,     1,     2,     3,     2,     4,     1,     4,     0,     2,
       2,     3,     2,     3,     0,     0,     0,     0,     2,     7,
      11,    10,    11,    16,     2,     2,     3,     2,     3,     1,
       1,     0,     1,     3,     3,     3,     3,     3,     3,     4,
       4,     2,     1,     1,     3,     0,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     3,     4,     3,     1,     1,     1,     4
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 45 "cgram.y" /* yacc.c:1646  */
    {}
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 48 "cgram.y" /* yacc.c:1646  */
    {}
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 49 "cgram.y" /* yacc.c:1646  */
    {}
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 52 "cgram.y" /* yacc.c:1646  */
    {}
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 53 "cgram.y" /* yacc.c:1646  */
    {}
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 56 "cgram.y" /* yacc.c:1646  */
    {}
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 57 "cgram.y" /* yacc.c:1646  */
    {}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 60 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), 0); }
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 61 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = dcl((yyvsp[0].id_ptr), (yyvsp[-2].id_ptr)->i_type&~T_ARRAY, 0); }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 64 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = dclr((yyvsp[0].str_ptr), 0, 1); }
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 65 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = dclr((yyvsp[-2].str_ptr), T_ARRAY, 1); }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 66 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = dclr((yyvsp[-3].str_ptr), T_ARRAY, atoi((yyvsp[-1].str_ptr))); }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 69 "cgram.y" /* yacc.c:1646  */
    { (yyval.inttype) = T_INT; }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 70 "cgram.y" /* yacc.c:1646  */
    { (yyval.inttype) = T_DOUBLE; }
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 71 "cgram.y" /* yacc.c:1646  */
    { (yyval.inttype) = T_DOUBLE; }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 72 "cgram.y" /* yacc.c:1646  */
    { (yyval.inttype) = T_INT; }
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 75 "cgram.y" /* yacc.c:1646  */
    { ftail(); }
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 78 "cgram.y" /* yacc.c:1646  */
    { fhead((yyvsp[-3].id_ptr)); }
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 81 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = fname((yyvsp[-1].inttype), (yyvsp[0].str_ptr)); }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 82 "cgram.y" /* yacc.c:1646  */
    { (yyval.id_ptr) = fname(T_INT, (yyvsp[0].str_ptr)); }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 85 "cgram.y" /* yacc.c:1646  */
    { enterblock(); }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 86 "cgram.y" /* yacc.c:1646  */
    { enterblock(); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 89 "cgram.y" /* yacc.c:1646  */
    { dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), PARAM); }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 90 "cgram.y" /* yacc.c:1646  */
    { dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), PARAM); }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 93 "cgram.y" /* yacc.c:1646  */
    { blockdcl(); }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 95 "cgram.y" /* yacc.c:1646  */
    { btail(); }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 98 "cgram.y" /* yacc.c:1646  */
    { }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 99 "cgram.y" /* yacc.c:1646  */
    { }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 102 "cgram.y" /* yacc.c:1646  */
    { }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 103 "cgram.y" /* yacc.c:1646  */
    { }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 106 "cgram.y" /* yacc.c:1646  */
    { labeldcl((yyvsp[-1].str_ptr)); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 107 "cgram.y" /* yacc.c:1646  */
    { labeldcl((yyvsp[-1].str_ptr)); }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 110 "cgram.y" /* yacc.c:1646  */
    { startloopscope(); }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "cgram.y" /* yacc.c:1646  */
    { (yyval.inttype) = m(); }
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 116 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = n(); }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 119 "cgram.y" /* yacc.c:1646  */
    { bgnstmt(); }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 123 "cgram.y" /* yacc.c:1646  */
    { }
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 125 "cgram.y" /* yacc.c:1646  */
    { doif((yyvsp[-4].rec_ptr), (yyvsp[-2].inttype), (yyvsp[0].inttype)); }
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 127 "cgram.y" /* yacc.c:1646  */
    { doifelse((yyvsp[-8].rec_ptr), (yyvsp[-6].inttype), (yyvsp[-3].rec_ptr), (yyvsp[-2].inttype), (yyvsp[0].inttype)); }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 129 "cgram.y" /* yacc.c:1646  */
    { dowhile((yyvsp[-7].inttype), (yyvsp[-6].rec_ptr), (yyvsp[-4].inttype), (yyvsp[-1].rec_ptr), (yyvsp[0].inttype)); }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 131 "cgram.y" /* yacc.c:1646  */
    { dodo((yyvsp[-9].inttype), (yyvsp[-4].inttype), (yyvsp[-3].rec_ptr), (yyvsp[0].inttype)); }
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 133 "cgram.y" /* yacc.c:1646  */
    { dofor((yyvsp[-11].inttype), (yyvsp[-10].rec_ptr), (yyvsp[-8].inttype), (yyvsp[-6].rec_ptr), (yyvsp[-4].inttype), (yyvsp[-1].rec_ptr), (yyvsp[0].inttype)); }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 135 "cgram.y" /* yacc.c:1646  */
    { docontinue(); }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 137 "cgram.y" /* yacc.c:1646  */
    { dobreak(); }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 139 "cgram.y" /* yacc.c:1646  */
    { dogoto((yyvsp[-1].str_ptr)); }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 141 "cgram.y" /* yacc.c:1646  */
    { doret((struct sem_rec *) NULL); }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 143 "cgram.y" /* yacc.c:1646  */
    { doret((yyvsp[-1].rec_ptr)); }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 145 "cgram.y" /* yacc.c:1646  */
    { }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 147 "cgram.y" /* yacc.c:1646  */
    { }
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 150 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = node(0, 0, n(), 0); }
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 151 "cgram.y" /* yacc.c:1646  */
    {}
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 154 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel("==", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 155 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel("!=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 156 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel("<=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 157 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel(">=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 158 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel("<",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 159 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = rel(">",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 160 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = ccand((yyvsp[-3].rec_ptr), (yyvsp[-1].inttype), (yyvsp[0].rec_ptr)); }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 161 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = ccor((yyvsp[-3].rec_ptr), (yyvsp[-1].inttype), (yyvsp[0].rec_ptr)); }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 162 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = ccnot((yyvsp[0].rec_ptr)); }
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 163 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = ccexpr((yyvsp[0].rec_ptr)); }
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 166 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = (yyvsp[0].rec_ptr); }
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 167 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = exprs((yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 170 "cgram.y" /* yacc.c:1646  */
    {}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 171 "cgram.y" /* yacc.c:1646  */
    {}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 174 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("",   (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 175 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("|",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 176 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("^",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 177 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("&",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 178 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("<<", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 179 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set(">>", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 180 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("+",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 181 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("-",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 182 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("*",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 183 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("/",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 184 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = set("%",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 185 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = opb("|",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 186 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = opb("^",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 187 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = opb("&",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 188 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = opb("<<", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 189 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = opb(">>", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 190 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op2("+",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 191 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op2("-",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 192 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op2("*",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 193 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op2("/",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 194 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op2("%",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 196 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = (yyvsp[0].rec_ptr); }
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 197 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op1("-",      (yyvsp[0].rec_ptr)); }
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 198 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op1("~",      (yyvsp[0].rec_ptr)); }
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 199 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = op1("@",      (yyvsp[0].rec_ptr)); }
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 200 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = call((yyvsp[-2].str_ptr), (struct sem_rec *) NULL); }
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 201 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = call((yyvsp[-3].str_ptr), (yyvsp[-1].rec_ptr)); }
#line 2052 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 202 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = (yyvsp[-1].rec_ptr); }
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 203 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = con((yyvsp[0].str_ptr)); }
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 204 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = string((yyvsp[0].str_ptr)); }
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 207 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = id((yyvsp[0].str_ptr)); }
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 208 "cgram.y" /* yacc.c:1646  */
    { (yyval.rec_ptr) = index1(id((yyvsp[-3].str_ptr)), (yyvsp[-1].rec_ptr)); }
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2086 "y.tab.c" /* yacc.c:1646  */
      default: break;
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
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 210 "cgram.y" /* yacc.c:1906  */

# include <stdio.h>

extern int lineno;

/*
 * main - read a program, and parse it
 */
int main(int argc, char **argv)
{

   enterblock();
   initlex();
   enterblock();
   if (yyparse())
      yyerror("syntax error");
   leaveblock();
   leaveblock();
   exit(0);
}

/*
 * yyerror - issue error message
 */
void yyerror(char msg[])
{
   fprintf(stderr, " %s.  Line %d\n", msg, lineno);
}
