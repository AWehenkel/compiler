/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "vsop_grammar.y" /* yacc.c:339  */


#include <cstdio>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <utility>
#include "all_headers.hpp"
#include "yyerror_init.h"
#include "SemanticAnalysis/SemanticAnalyser.hpp"
#include "SemanticAnalysis/SemanticError.hpp"
#include "PairColLine.hpp"
#include "Visitors/CodeGenVisitor.hpp"

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" char *file_name;
extern "C" char *yytext;
extern "C" int yychar;
extern "C" int yylineno;

int semantic_error = 0;
int errors;
int start_token;
int syntax_error;

void yyerror(const char *s);


#line 99 "vsop_grammar.tab.c" /* yacc.c:339  */

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
   by #include "vsop_grammar.tab.h".  */
#ifndef YY_YY_VSOP_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_VSOP_GRAMMAR_TAB_H_INCLUDED
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
    T_AND = 258,
    T_BOOL = 259,
    T_CLASS = 260,
    T_DO = 261,
    T_ELSE = 262,
    T_EXTENDS = 263,
    T_FALSE = 264,
    T_IF = 265,
    T_IN = 266,
    T_INT32 = 267,
    T_ISNULL = 268,
    T_LET = 269,
    T_NEW = 270,
    T_NOT = 271,
    T_STRING = 272,
    T_THEN = 273,
    T_TRUE = 274,
    T_UNIT = 275,
    T_WHILE = 276,
    T_OBJ_ID = 277,
    T_INT_LIT = 278,
    T_TYPE_ID = 279,
    T_STRING_LIT = 280,
    T_L_BRACE = 281,
    T_R_BRACE = 282,
    T_R_PAR = 283,
    T_L_PAR = 284,
    T_COLON = 285,
    T_SEMI_COLON = 286,
    T_COMMA = 287,
    T_PLUS = 288,
    T_MINUS = 289,
    T_TIMES = 290,
    T_DIV = 291,
    T_POW = 292,
    T_DOT = 293,
    T_EQUAL = 294,
    T_LOWER = 295,
    T_LEQ = 296,
    T_ASSIGN = 297,
    T_COMMENTS = 298,
    START_SYNTAX = 299,
    START_LEXICAL = 300,
    START_SEMANTIC = 301,
    START_CODE_GEN = 302,
    T_ERROR = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 36 "vsop_grammar.y" /* yacc.c:355  */

	int ival;
  char *sval;
	class ProgramNode* program_node;
	class ClassNode* class_node;
	class ClassBodyNode* class_body_node;
	class FieldNode* field_node;
	class MethodNode* method_node;
	class AssignNode* assign_node;
	class FormalsNode* formals_node;
	class FormalNode* formal_node;
	class TypeIdentifierNode* type_identifier_node;
  class ObjectIdentifierNode* object_identifier_node;
	class BlockNode* block_node;
	class ExpressionNode* expression_node;
	class ArgsNode* args_node;
	class LiteralNode* literal_node;
	class PairColLine* col_lin;

#line 208 "vsop_grammar.tab.c" /* yacc.c:355  */
};
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

#endif /* !YY_YY_VSOP_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 237 "vsop_grammar.tab.c" /* yacc.c:358  */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   344

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   122,   126,   134,   147,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   193,   194,
     198,   202,   206,   210,   214,   218,   222,   226,   230,   234,
     238,   242,   246,   250,   254,   258,   262,   266,   274,   275,
     279,   280,   281,   285,   290,   291,   295,   296,   300,   304,
     305,   306,   307,   308,   312,   313,   317,   318,   322,   326,
     330,   331,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   363,   364,   368,
     369,   373,   374,   375,   379,   380
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AND", "T_BOOL", "T_CLASS", "T_DO",
  "T_ELSE", "T_EXTENDS", "T_FALSE", "T_IF", "T_IN", "T_INT32", "T_ISNULL",
  "T_LET", "T_NEW", "T_NOT", "T_STRING", "T_THEN", "T_TRUE", "T_UNIT",
  "T_WHILE", "T_OBJ_ID", "T_INT_LIT", "T_TYPE_ID", "T_STRING_LIT",
  "T_L_BRACE", "T_R_BRACE", "T_R_PAR", "T_L_PAR", "T_COLON",
  "T_SEMI_COLON", "T_COMMA", "T_PLUS", "T_MINUS", "T_TIMES", "T_DIV",
  "T_POW", "T_DOT", "T_EQUAL", "T_LOWER", "T_LEQ", "T_ASSIGN",
  "T_COMMENTS", "START_SYNTAX", "START_LEXICAL", "START_SEMANTIC",
  "START_CODE_GEN", "T_ERROR", "$accept", "start", "Input", "program",
  "t_type_id", "t_obj_id", "t_if", "t_while", "t_let", "t_not", "t_isnull",
  "t_plus", "t_and", "t_equal", "t_leq", "t_lower", "t_minus", "t_times",
  "t_div", "t_pow", "t_new", "class", "extend", "class-body", "field",
  "assign", "method", "type", "formals", "virgul-formals", "formal",
  "block", "sc-expr", "expr", "args", "comma-arg", "literal",
  "boolean-literal", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -31,     0,   -83,     0,     0,    11,    -4,     0,   -83,   147,
       0,     0,   -83,   -83,    16,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,    -4,     4,   -83,
     -83,     6,    25,   -83,   -83,    10,   -83,   -83,    91,    12,
      74,   -83,   -83,   -83,   -83,   -83,    15,    28,    18,    36,
      38,    15,    22,    41,    91,    43,    12,   -83,   -83,    51,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
      22,   310,   -83,   -21,    22,    22,    12,    22,    22,    22,
      -4,   -83,   277,   -83,   -83,   -83,   -83,    91,    36,   -83,
     188,   -83,   202,    22,    22,   213,   252,    44,   277,   277,
     277,   -83,   -83,   -83,   -83,   -83,   -83,    12,   -83,   -83,
     -83,    22,    22,    22,    22,    22,    22,    22,    22,    22,
      57,   -83,    22,    63,   -83,   229,    68,   277,    22,    22,
      91,    70,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   -83,   188,   -83,    22,   -83,   -83,   268,   277,    15,
      22,   -83,   229,    22,    86,    76,   -83,   277,    22,   -83,
     277
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     6,     0,     0,     0,     0,     3,    48,     2,
       4,     5,     1,    50,    68,    49,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,    69,
      70,     0,     0,    51,    67,     0,    71,    72,     0,    84,
       0,    81,    80,    82,    83,    79,    76,     0,     0,    86,
       0,    76,     0,     0,     0,     0,     0,    85,    74,     0,
     125,    52,    56,    54,    66,    55,   124,    53,   121,   122,
       0,     0,    62,   112,     0,     0,     0,     0,     0,     0,
       0,   116,    77,   113,   123,    75,    88,     0,    86,    73,
      90,   114,     0,   117,     0,     0,     0,     0,    97,    99,
      98,   111,    58,    57,    63,    64,    65,     0,    59,    61,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,     0,     0,   115,   119,     0,    96,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,    78,    90,    89,     0,   118,   109,    92,    94,    76,
     117,    91,   119,     0,     0,     0,   120,    93,     0,   110,
      95
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -83,   -83,   -83,    50,    -5,   -57,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -41,   -83,   -83,   -83,
     -83,    -1,   -83,   -83,   -83,   -79,   -83,   -67,   -83,   -16,
      21,   -40,   -63,   -82,   -68,   -69,   -83,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     9,     7,    75,   103,   104,   105,   106,   107,
     108,   141,   142,   143,   144,   145,   109,   147,   148,   149,
     110,     8,    58,    61,    66,    83,    67,    76,    78,    87,
      79,   111,   153,   155,   156,   175,   113,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     112,    14,    89,    81,    65,     6,    15,    62,   123,    15,
      15,    12,    77,     1,     2,     3,     4,   116,   120,   122,
      13,   124,   125,   126,    57,   128,   129,   130,    63,    77,
      60,    90,    91,    64,    63,    92,    93,    94,    95,    69,
      70,    96,   157,    97,    63,    98,    85,    99,   100,   127,
     150,   101,    59,    10,    11,    68,   102,    82,    84,   162,
     163,   164,   165,   166,   167,   168,   169,   170,    86,    88,
     172,   146,   115,   117,   160,    80,   177,   178,    71,   146,
     161,   146,   119,   100,   146,   146,    72,   146,   146,   146,
     173,    73,   182,   179,    74,    71,   176,   188,    13,   180,
     184,   187,   151,    72,   189,   131,   190,   118,    73,   181,
     171,    74,   185,   186,   146,    13,   146,     0,     0,     0,
       0,   146,   146,   146,   146,   146,   146,   146,   146,   146,
       0,   146,     0,     0,     0,     0,   146,   146,     0,     0,
       0,   146,     0,     0,     0,     0,   146,     0,     0,   146,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,     0,     0,   152,
       0,   133,   102,   134,   135,   136,   137,   138,   139,   140,
     154,   158,   132,     0,     0,   133,   102,   134,   135,   136,
     137,   138,   139,   140,     0,     0,   133,   102,   134,   135,
     136,   137,   138,   139,   140,   132,     0,     0,   159,     0,
       0,   174,   133,   102,   134,   135,   136,   137,   138,   139,
     140,   132,     0,     0,     0,   183,     0,     0,     0,     0,
     132,     0,     0,     0,     0,   133,   102,   134,   135,   136,
     137,   138,   139,   140,     0,     0,     0,     0,     0,     0,
       0,   133,   102,   134,   135,   136,   137,   138,   139,   140,
     133,   102,   134,   135,   136,   137,   138,   139,   140,    90,
      91,     0,     0,    92,    93,    94,    95,     0,     0,    96,
       0,    97,    63,    98,     0,    99,   100,     0,   121,   101,
       0,     0,     0,     0,   102
};

static const yytype_int16 yycheck[] =
{
      82,     6,    81,    70,    61,     5,     7,     1,    29,    10,
      11,     0,    69,    44,    45,    46,    47,    84,   100,   101,
      24,    42,   104,   105,     8,   107,   108,   109,    22,    86,
      26,     9,    10,    27,    22,    13,    14,    15,    16,    29,
      30,    19,   124,    21,    22,    23,    28,    25,    26,   106,
     117,    29,    57,     3,     4,    30,    34,    42,    30,   141,
     142,   143,   144,   145,   146,   147,   148,   149,    32,    31,
     152,   112,    31,    30,    30,     1,   158,   159,     4,   120,
     137,   122,    31,    26,   125,   126,    12,   128,   129,   130,
      27,    17,   174,   160,    20,     4,    28,    11,    24,    29,
     179,   183,   118,    12,    28,   110,   188,    86,    17,   172,
     150,    20,   180,   182,   155,    24,   157,    -1,    -1,    -1,
      -1,   162,   163,   164,   165,   166,   167,   168,   169,   170,
      -1,   172,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,
      -1,   182,    -1,    -1,    -1,    -1,   187,    -1,    -1,   190,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      28,    18,     3,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     3,    -1,    -1,     6,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     3,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,    19,
      -1,    21,    22,    23,    -1,    25,    26,    -1,    28,    29,
      -1,    -1,    -1,    -1,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    45,    46,    47,    50,     5,    52,    70,    51,
      52,    52,     0,    24,    53,    70,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,     8,    71,    53,
      26,    72,     1,    22,    27,    54,    73,    75,    30,    29,
      30,     4,    12,    17,    20,    53,    76,    54,    77,    79,
       1,    76,    42,    74,    30,    28,    32,    78,    31,    74,
       9,    10,    13,    14,    15,    16,    19,    21,    23,    25,
      26,    29,    34,    54,    55,    56,    57,    58,    59,    65,
      69,    80,    82,    85,    86,    31,    76,    30,    79,    31,
      82,    28,    82,    29,    42,    82,    82,    54,    82,    82,
      82,    53,     3,    33,    35,    36,    37,    38,    39,    40,
      41,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      76,    78,    31,    81,    28,    82,    83,    82,    18,     6,
      30,    54,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    80,    82,    27,    32,    84,    28,    82,    82,    76,
      29,    81,    82,     7,    74,    83,    84,    82,    11,    28,
      82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    71,
      72,    72,    72,    73,    73,    73,    74,    74,    75,    76,
      76,    76,    76,    76,    77,    77,    78,    78,    79,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    83,    83,    84,
      84,    85,    85,    85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     0,     2,
       0,     2,     2,     5,     4,     5,     0,     2,     7,     1,
       1,     1,     1,     1,     0,     2,     0,     3,     3,     4,
       0,     3,     4,     6,     4,     7,     3,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       6,     2,     1,     1,     2,     3,     1,     0,     2,     0,
       3,     1,     1,     1,     1,     1
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
int yystate;

int
yyparse (void)
{
    //int yystate;
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
  switch (yyn)
    {
        case 3:
#line 122 "vsop_grammar.y" /* yacc.c:1646  */
    {	if(!syntax_error)
																											cout << *(yyvsp[0].program_node);
																										delete (yyvsp[0].program_node);
																									 }
#line 1589 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 126 "vsop_grammar.y" /* yacc.c:1646  */
    {
																										if(!syntax_error){
																											semantic_error = SemanticAnalyser::semanticAnalysis((yyvsp[0].program_node));
																											if(!semantic_error)
																												cout << (yyvsp[0].program_node)->getLiteral(true);
																										}
																										delete (yyvsp[0].program_node);
																									}
#line 1602 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 134 "vsop_grammar.y" /* yacc.c:1646  */
    {
																										if(!syntax_error){
																											semantic_error = SemanticAnalyser::semanticAnalysis((yyvsp[0].program_node));
																											if(!semantic_error){
																												CodeGenVisitor* generator = new CodeGenVisitor();
																												(yyvsp[0].program_node)->accept(generator);
																												delete generator;
																											}
																										}
																										delete (yyvsp[0].program_node);
																									}
#line 1618 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 149 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",and" << endl; }
#line 1624 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 150 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",bool" << endl; }
#line 1630 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 151 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",class" << endl; }
#line 1636 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",do" << endl; }
#line 1642 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",else" << endl; }
#line 1648 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 154 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",extends" << endl; }
#line 1654 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",false" << endl; }
#line 1660 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",if" << endl; }
#line 1666 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 157 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",in" << endl; }
#line 1672 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 158 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",int32" << endl; }
#line 1678 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 159 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",isnull" << endl; }
#line 1684 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 160 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",let" << endl; }
#line 1690 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 161 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",new" << endl; }
#line 1696 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",not" << endl; }
#line 1702 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 163 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",string" << endl; }
#line 1708 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 164 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",then" << endl; }
#line 1714 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 165 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",true" << endl; }
#line 1720 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 166 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",unit" << endl; }
#line 1726 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 167 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",while" << endl; }
#line 1732 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 168 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",object-identifier," << yylval.sval << endl; free(yylval.sval);}
#line 1738 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",integer-literal," << yylval.ival << endl; }
#line 1744 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 170 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",type-identifier," << yylval.sval << endl; free(yylval.sval);}
#line 1750 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 171 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",string-literal," << yylval.sval << endl; free(yylval.sval);}
#line 1756 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 172 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",lbrace" << endl; }
#line 1762 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 173 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",rbrace" << endl; }
#line 1768 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 174 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",rpar" << endl; }
#line 1774 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 175 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",lpar" << endl; }
#line 1780 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 176 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",colon" << endl; }
#line 1786 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 177 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",semicolon" << endl; }
#line 1792 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 178 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",comma" << endl; }
#line 1798 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 179 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",plus" << endl; }
#line 1804 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 180 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",minus" << endl; }
#line 1810 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 181 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",times" << endl; }
#line 1816 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 182 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",div" << endl; }
#line 1822 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 183 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",pow" << endl; }
#line 1828 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 184 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",dot" << endl; }
#line 1834 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 185 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",equal" << endl; }
#line 1840 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 186 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",lower" << endl; }
#line 1846 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 187 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",lower-equal" << endl; }
#line 1852 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 188 "vsop_grammar.y" /* yacc.c:1646  */
    { cout << yylloc.first_line << "," << yylloc.first_column << ",assign" << endl; }
#line 1858 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 193 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.program_node) = new ProgramNode((yyvsp[0].class_node));}
#line 1864 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 194 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[-1].program_node)->addClass((yyvsp[0].class_node)); (yyval.program_node) = (yyvsp[-1].program_node);}
#line 1870 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 198 "vsop_grammar.y" /* yacc.c:1646  */
    {string tmp = (yyvsp[0].sval); free((yyvsp[0].sval)); (yyval.type_identifier_node) = new TypeIdentifierNode(tmp, yylloc.first_column, yylloc.first_line);}
#line 1876 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 202 "vsop_grammar.y" /* yacc.c:1646  */
    {string tmp = (yyvsp[0].sval); free((yyvsp[0].sval)); (yyval.object_identifier_node) = new ObjectIdentifierNode(tmp, yylloc.first_column, yylloc.first_line);}
#line 1882 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 206 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1888 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 210 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1894 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 214 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1900 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 218 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1906 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 222 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1912 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 226 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1918 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 230 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1924 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 234 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1930 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 238 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1936 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 242 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1942 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 246 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1948 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 250 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1954 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 254 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1960 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 258 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1966 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 262 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.col_lin) = new PairColLine(yylloc.first_column, yylloc.first_line);}
#line 1972 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 266 "vsop_grammar.y" /* yacc.c:1646  */
    {if((yyvsp[-3].type_identifier_node)){
																														(yyval.class_node) = new ClassNode((yyvsp[-4].type_identifier_node), (yyvsp[-1].class_body_node), (yyvsp[-3].type_identifier_node), (yyvsp[-4].type_identifier_node)->getCol(), (yyvsp[-4].type_identifier_node)->getLine());
																													 }else
																														(yyval.class_node) = new ClassNode((yyvsp[-4].type_identifier_node), (yyvsp[-1].class_body_node), NULL, (yyvsp[-4].type_identifier_node)->getCol(), (yyvsp[-4].type_identifier_node)->getLine());
																													}
#line 1982 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 274 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = NULL;}
#line 1988 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 275 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = (yyvsp[0].type_identifier_node);}
#line 1994 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 279 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.class_body_node) = new ClassBodyNode();}
#line 2000 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 280 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[-1].class_body_node)->addField((yyvsp[0].field_node)); (yyval.class_body_node) = (yyvsp[-1].class_body_node);}
#line 2006 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 281 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[-1].class_body_node)->addMethod((yyvsp[0].method_node)); (yyval.class_body_node) = (yyvsp[-1].class_body_node);}
#line 2012 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 285 "vsop_grammar.y" /* yacc.c:1646  */
    {if((yyvsp[-1].expression_node))
																								(yyval.field_node) = new FieldNode((yyvsp[-4].object_identifier_node), (yyvsp[-2].type_identifier_node), (yyvsp[-1].expression_node), (yyvsp[-4].object_identifier_node)->getCol(), (yyvsp[-4].object_identifier_node)->getLine());
																							 else
																								(yyval.field_node) = new FieldNode((yyvsp[-4].object_identifier_node), (yyvsp[-2].type_identifier_node), (yyvsp[-4].object_identifier_node)->getCol(), (yyvsp[-4].object_identifier_node)->getLine());
																							}
#line 2022 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 290 "vsop_grammar.y" /* yacc.c:1646  */
    {delete (yyvsp[-3].object_identifier_node);(yyval.field_node) = NULL;cout << "recovery" << endl;syntax_error++;}
#line 2028 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 291 "vsop_grammar.y" /* yacc.c:1646  */
    {delete (yyvsp[-2].type_identifier_node); delete (yyvsp[-1].expression_node);(yyval.field_node) = NULL;cout << "recovery" << endl;syntax_error++;}
#line 2034 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 295 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = NULL;}
#line 2040 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 296 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = (yyvsp[0].expression_node);}
#line 2046 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 300 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.method_node) = new MethodNode((yyvsp[-6].object_identifier_node), (yyvsp[-4].formals_node), (yyvsp[-1].type_identifier_node), (yyvsp[0].block_node), (yyvsp[-6].object_identifier_node)->getCol(), (yyvsp[-6].object_identifier_node)->getLine());}
#line 2052 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 304 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = (yyvsp[0].type_identifier_node);}
#line 2058 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 305 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = new TypeIdentifierNode("int32", yylloc.first_column, yylloc.first_line);}
#line 2064 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 306 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = new TypeIdentifierNode("bool", yylloc.first_column, yylloc.first_line);}
#line 2070 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 307 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = new TypeIdentifierNode("string", yylloc.first_column, yylloc.first_line);}
#line 2076 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 308 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.type_identifier_node) = new TypeIdentifierNode("unit", yylloc.first_column, yylloc.first_line);}
#line 2082 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 312 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.formals_node) = new FormalsNode();}
#line 2088 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 313 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[0].formals_node)->insertFormal((yyvsp[-1].formal_node)); (yyval.formals_node) = (yyvsp[0].formals_node);}
#line 2094 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 317 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.formals_node) = new FormalsNode();}
#line 2100 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 318 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[0].formals_node)->insertFormal((yyvsp[-1].formal_node)); (yyval.formals_node) = (yyvsp[0].formals_node);}
#line 2106 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 322 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.formal_node) = new FormalNode((yyvsp[-2].object_identifier_node), (yyvsp[0].type_identifier_node), (yyvsp[-2].object_identifier_node)->getCol(), (yyvsp[-2].object_identifier_node)->getLine());}
#line 2112 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 326 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[-1].block_node)->insertExpr((yyvsp[-2].expression_node)); (yyval.block_node) = (yyvsp[-1].block_node);}
#line 2118 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 330 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.block_node) = new BlockNode();}
#line 2124 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 331 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[0].block_node)->insertExpr((yyvsp[-1].expression_node)); (yyval.block_node) = (yyvsp[0].block_node);}
#line 2130 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 335 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new ConditionalNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), NULL, (yyvsp[-3].col_lin)->getCol(), (yyvsp[-3].col_lin)->getLine());}
#line 2136 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 336 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new ConditionalNode((yyvsp[-4].expression_node), (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-5].col_lin)->getCol(), (yyvsp[-5].col_lin)->getLine());}
#line 2142 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 337 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new WhileNode((yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-3].col_lin)->getCol(), (yyvsp[-3].col_lin)->getLine());}
#line 2148 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 338 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new LetNode((yyvsp[-5].object_identifier_node), (yyvsp[-3].type_identifier_node), (yyvsp[0].expression_node), (yyvsp[-2].expression_node), (yyvsp[-6].col_lin)->getCol(), (yyvsp[-6].col_lin)->getLine());}
#line 2154 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 339 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new AssignNode((yyvsp[-2].object_identifier_node), (yyvsp[0].expression_node), (yyvsp[-2].object_identifier_node)->getCol(), (yyvsp[-2].object_identifier_node)->getLine());}
#line 2160 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 340 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new UnaryOperatorNode(UnaryOperator::u_op_not, (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2166 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 341 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new UnaryOperatorNode(UnaryOperator::u_op_minus, (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2172 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 342 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new UnaryOperatorNode(UnaryOperator::u_op_isnull, (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2178 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 343 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_plus, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2184 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 344 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_and, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2190 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 345 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_equal, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2196 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 346 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_leq, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2202 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 347 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_less, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2208 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 348 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_minus, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2214 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 349 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_times, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2220 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 350 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_div, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2226 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 351 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BinaryOperatorNode(BinaryOperator::b_op_pow, (yyvsp[-2].expression_node), (yyvsp[0].expression_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2232 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 352 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new CallNode((yyvsp[-3].object_identifier_node), (yyvsp[-1].args_node), NULL, (yyvsp[-3].object_identifier_node)->getCol(), (yyvsp[-3].object_identifier_node)->getLine());}
#line 2238 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 353 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new CallNode((yyvsp[-3].object_identifier_node), (yyvsp[-1].args_node), (yyvsp[-5].expression_node), (yyvsp[-3].object_identifier_node)->getCol(), (yyvsp[-3].object_identifier_node)->getLine());}
#line 2244 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 354 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new NewNode((yyvsp[0].type_identifier_node), (yyvsp[-1].col_lin)->getCol(), (yyvsp[-1].col_lin)->getLine());}
#line 2250 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 355 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = (yyvsp[0].object_identifier_node);}
#line 2256 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 356 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = (yyvsp[0].literal_node);}
#line 2262 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 357 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = new BraceNode(NULL, yylloc.first_column, yylloc.first_line);}
#line 2268 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 358 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = (yyvsp[-1].expression_node);}
#line 2274 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 359 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.expression_node) = (yyvsp[0].block_node);}
#line 2280 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 363 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.args_node) = new ArgsNode();}
#line 2286 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 364 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[0].args_node)->insertExpr((yyvsp[-1].expression_node)); (yyval.args_node) = (yyvsp[0].args_node);}
#line 2292 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 368 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.args_node) = new ArgsNode();}
#line 2298 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 369 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyvsp[0].args_node)->insertExpr((yyvsp[-1].expression_node)); (yyval.args_node) = (yyvsp[0].args_node);}
#line 2304 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 373 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.literal_node) = new LiteralNode((yyvsp[0].ival), "int32", yylloc.first_column, yylloc.first_line);}
#line 2310 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 374 "vsop_grammar.y" /* yacc.c:1646  */
    {string tmp = (yyvsp[0].sval); free (yyvsp[0].sval); (yyval.literal_node) = new LiteralNode(tmp, "string", yylloc.first_column, yylloc.first_line);}
#line 2316 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 375 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.literal_node) = (yyvsp[0].literal_node);}
#line 2322 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 379 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.literal_node) = new LiteralNode("true", "bool", yylloc.first_column, yylloc.first_line);}
#line 2328 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 380 "vsop_grammar.y" /* yacc.c:1646  */
    {(yyval.literal_node) = new LiteralNode("false", "bool", yylloc.first_column, yylloc.first_line);}
#line 2334 "vsop_grammar.tab.c" /* yacc.c:1646  */
    break;


#line 2338 "vsop_grammar.tab.c" /* yacc.c:1646  */
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
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 385 "vsop_grammar.y" /* yacc.c:1906  */


int main (int argc, char *argv[]){

	if(argc != 3){
		cerr << "Usage for only lexer: ./main -lex <Source_File>" << endl;
		cerr << "Usage for both lexer and parse: ./main <Source_File>" << endl;
		cerr << "Usage for lexer, parse and semantic: ./main -check <Source_File" << endl;
		return -1;
	}

	if(!strcmp(argv[1], "-lex"))
		start_token = START_LEXICAL;
	else if(!strcmp(argv[1], "-check"))
    start_token = START_SEMANTIC;
  else if(!strcmp(argv[1], "-parse"))
		start_token = START_SYNTAX;
	else if(!strcmp(argv[1], "-llvm"))
		start_token = START_CODE_GEN;
	else{
		cerr << "Usage for only lexer: ./main -lex <Source_File>" << endl;
		cerr << "Usage for both lexer and parse: ./main -parse <Source_File>" << endl;
		cerr << "Usage for lexer, parse and semantic: ./main -check <Source_File" << endl;
		return -1;
	}


	FILE *myfile = fopen(argv[argc-1], "r");
	file_name = argv[argc-1];
	if (!myfile) {
	 	cerr << "Could not open " << file_name << endl;
		return -1;
	}
	SemanticError::FILE_NAME = file_name;
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	syntax_error = 0;
	do {
		if(yyparse() == 1){
			syntax_error++;
		}
	} while (!feof(yyin));

	if(syntax_error)
		return -1;

	//if(semantic_error)
	//	cerr << file_name<< ":0:0: semantic error(s) in the file: " << endl;
	//fclose(myfile);
	//free(myfile);
	return semantic_error;
}

void yyerror(const char *s)
{

  int i;
  char sbuf[128];

  if (! yyerror_isinitialized++) yyerror_init();

  if (!strcmp(s, "stack")) return;

  if (errors++ > 10) {
    fprintf(stderr, "Too many errors, aborting");
    exit(errors);
	}

  if ((!strcmp(s, "syntax error") || !strcmp(s, "parse error")) && (yystate>=0 && yystate<=yymaxstate && errtab[yystate].i != 0)){
      if (errtab[yystate].i == 1)
        s = errtab[yystate].u.msg;
      else {
        for(i=1; i <= errtab[yystate].i; i++)
            if(yychar == errtab[yystate].u.p[i].i){
              s = errtab[yystate].u.p[i].u.msg;
              break;
            }

        if(i > errtab[yystate].i)
          s = errtab[yystate].u.p[0].u.msg;
       }
    }

   // Lines to comment after error generation
	 /*if(file_name) fprintf(stderr, "%s:", file_name);
   if (!strcmp(s, "syntax error") || !strcmp(s,"parse error")){
      sprintf(sbuf,"%s (%d;%d)", s, yystate, yychar);
      s = sbuf;
   }
   fprintf(stderr, "%d: # \"%s\": %s\n", yylineno, yytext, s);
   */

   // Lines to comment when doing error generation
	 cerr << file_name << ":" << yylloc.first_line << ":" << yylloc.first_column << ": syntax error" << endl;
	 cerr << s << endl;
}
