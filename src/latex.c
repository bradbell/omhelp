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


/* Substitute the variable and function names.  */
#define yyparse         texparse
#define yylex           texlex
#define yyerror         texerror
#define yydebug         texdebug
#define yynerrs         texnerrs

#define yylval          texlval
#define yychar          texchar

/* Copy the first part of user declarations.  */
#line 18 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:339  */


# include <stdio.h>
# include <assert.h>
# include <string.h>
# include <ctype.h>

# include "texparse.h"
# include "output.h"
# include "int2str.h"
# include "fatalerr.h"
# include "TexStype.h"
# include "allocmem.h"
# include "str_alloc.h"
# include "convert.h"
# include "pending.h"

# include "TexStype.h"
# define YYSTYPE TexStype

# define YYDEBUG 1

// external function defined in omhelp.y
extern int PreviousOmhelpOutputWasHeading(void);

/*
----------------------------------------------------------------------------
$begin TexInitialNumberPending$$
$dollar @$$

$section Number of Commands Pending When @latex Command Started$$

$table
$bold Syntax$$
$cnext $syntax/TexInitialNumberPending()/$$
$tend

$end
----------------------------------------------------------------------------
*/

static int InitialNumberPending = 0;
int TexInitialNumberPending()
{	return InitialNumberPending; }

// ******************* Stype Functions (all Static ) *************************

static void OutputTexStype(TexStype *T)
{
	assert( T != NULL );
	while( T != NULL )
	{	assert( T->str != NULL );
		OutputString( T->str );

		// at point of output, extra pointer must be NULL
		assert( T->extra == NULL );

		T = T->next;
	}
	return;
}

static void FreeTexStype(TexStype *T)
{
	TexStype *N;

	assert( T != NULL );
	FreeMem( T->str );
	assert( T->extra == NULL );

	T = T->next;
	while( T != NULL )
	{
		FreeMem( T->str );

		// at point of removal, extra pointer must be NULL
		assert( T->extra == NULL );

		N = T->next;
		FreeMem(T);
		T = N;
	}
	return;
}

static void StypePlusStype(TexStype *Head, TexStype *Tail)
{	TexStype *S;

	S = Head;
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
	}

	S->next    = AllocMem(sizeof(TexStype), 1);
	*(S->next) = *Tail;

	return;
}

static void CharPlusStype(const char *head, TexStype *Head)
{	TexStype *S;

	assert( Head->str != NULL );

	S  = AllocMem(sizeof(TexStype), 1);
	*S = *Head;

	Head->next = S;
	Head->str  = str_alloc(head);

	return;
}

static void StypePlusChar(TexStype *Head, const char *tail)
{	TexStype *S;

	S = Head;
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
	}

	S->next        = AllocMem(sizeof(TexStype), 1);
	S->next->str   = str_alloc(tail);
	S->next->extra = NULL;
	S->next->next  = NULL;

	return;
}

static int LengthStype(TexStype *Head)
{	TexStype *S;
	int      count;

	S     = Head;
	count = 1;
	assert( S != NULL );
	while( S->next != NULL )
	{	assert( S->str != NULL );
		S = S->next;
		count++;
	}

	return count;
}

// *********************** Static Data **********************************

// Maximum number of columns in an array
# define MAX_ARRAY_COL      100

// Maximum number of levels that an array can nest inside another array
# define MAX_ARRAY_LEVEL    10

// if base.data has this value, and base has this length
// display (base sub/sup term) using (base under/over term)
# define SUBSUP_2_UNDEROVER_DATA    (MAX_ARRAY_COL+1)
# define SUBSUP_2_UNDEROVER_LENGTH  3

static int BlockDisplay = 0;
static int ArrayLevel   = 0;
static const char *ArrayAlign[MAX_ARRAY_LEVEL][MAX_ARRAY_COL];

// values for tracking the current grouping by braces level
# define MAX_FONT_LEVEL  20
static int FontLevel;

// stack used to track fonts at each level
static char *CurrentFont[MAX_FONT_LEVEL];

// *********************** Other Static Functions *************************

static void IncFontLevel()
{

	FontLevel++;
	if( FontLevel == MAX_FONT_LEVEL ) fataltex(
		"request to nest left braces \"{\" and arrays deeper than ",
		int2str(MAX_FONT_LEVEL),
		" levels",
		NULL
	);
	assert( FontLevel >= 0 );

	// start with no font at this level
	CurrentFont[FontLevel] = NULL;
}

static void DecFontLevel(TexStype *Head, int TerminateBeforeHead)
{
	// terminate font that is limited to this level
	assert( FontLevel >= 0 );
	if( CurrentFont[FontLevel] != NULL )
	{	// terminate current font
		FreeMem( CurrentFont[FontLevel] );
		if( TerminateBeforeHead )
		{	// check for special case where Head is empty
			if( Head->str == NULL )
			{	assert( Head->next == NULL );
				Head->str = str_alloc( "</mstyle>" );
			}
			else	CharPlusStype("</mstyle>", Head);
		}
		else	StypePlusChar(Head, "</mstyle>");
	}

	FontLevel--;
}

static const char *GetCurrentFont()
{	int i = FontLevel;

	while( i > 0 && CurrentFont[i] == NULL )
		i--;

	return CurrentFont[i];
}

static void SetArrayAlign(char *str)
{	size_t len;
	size_t i;

	assert( ArrayLevel <= MAX_ARRAY_LEVEL );
	if( ArrayLevel == MAX_ARRAY_LEVEL ) fataltex(
		"request to nest arrays deeper than ",
		int2str(MAX_ARRAY_LEVEL),
		" levels",
		NULL
	);

	// number of columns in array
	len = strlen( str );
	assert( len > 0 );
	if( len >= MAX_ARRAY_COL ) fataltex(
		"request for more than ",
		int2str(MAX_ARRAY_COL - 1),
		" columns in an array",
		NULL
	);

	// NULL is used to mark last column is previous column
	ArrayAlign[ArrayLevel][len] = NULL;

	for(i = 0; i < len; i++)
	{	switch( str[i] )
		{
			case 'l':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"left\"";
			break;

			case 'c':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"center\"";
			break;

			case 'r':
			ArrayAlign[ArrayLevel][i] = "columnalign=\"right\"";
			break;

			default:
			fataltex(
				"Invalid column alignment character \"",
				str,
				"\".\n",
				"The valid column alignment characters are ",
				"l, c, and r.",
				NULL
			);
		}
	}
}


// ***********************************************************************

#line 350 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:339  */

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
   by #include "latex.h".  */
#ifndef YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED
# define YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int texdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR_AMPERSAND_lex = 258,
    CHAR_CARET_lex = 259,
    CHAR_ENDINPUT_lex = 260,
    CHAR_LEFTBRACE_lex = 261,
    CHAR_LEFTBRACKET_lex = 262,
    CHAR_LETTERS_lex = 263,
    CHAR_OPERATOR_lex = 264,
    CHAR_RIGHTBRACE_lex = 265,
    CHAR_RIGHTBRACKET_lex = 266,
    CHAR_UNDERBAR_lex = 267,
    CMD_BACKSLASH_lex = 268,
    CMD_BEGIN_ARRAY_lex = 269,
    CMD_DIACRITICAL_lex = 270,
    CMD_END_ARRAY_lex = 271,
    CMD_CHAR_lex = 272,
    CMD_COMMA_lex = 273,
    CMD_COLON_lex = 274,
    CMD_FONT_lex = 275,
    CMD_FRAC_lex = 276,
    CMD_HSPACE_lex = 277,
    CMD_LEFT_lex = 278,
    CMD_LEFTBRACKET_lex = 279,
    CMD_MATHML_lex = 280,
    CMD_OVERBRACE_lex = 281,
    CMD_OVERLINE_lex = 282,
    CMD_RIGHT_lex = 283,
    CMD_RIGHTBRACKET_lex = 284,
    CMD_SEMICOLON_lex = 285,
    CMD_SQRT_lex = 286,
    CMD_STACKREL_lex = 287,
    CMD_UNDERBRACE_lex = 288,
    CMD_UNDERLINE_lex = 289,
    CMD_WIDEHAT_lex = 290,
    CMD_WIDETILDE_lex = 291,
    NUMBER_lex = 292,
    STDFUN_lex = 293,
    STD_DISPLAY_lex = 294,
    SYM_ARROW_lex = 295,
    SYM_BINARYOP_lex = 296,
    SYM_DISPLAY_lex = 297,
    SYM_DOTS_lex = 298,
    SYM_ENCLOSE_lex = 299,
    SYM_GREEK_lex = 300,
    SYM_INTEGRAL_lex = 301,
    SYM_MISC_lex = 302,
    SYM_RELATION_lex = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE texlval;

int texparse (void);

#endif /* !YY_TEX_HOME_BRADBELL_OMHELP_GIT_SRC_LATEX_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 450 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

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
       0,   344,   344,   376,   416,   433,   453,   472,   495,   528,
     542,   556,   571,   578,   647,   654,   706,   716,   752,   766,
     779,   796,   810,   816,   849,   855,   870,   879,   881,   883,
     885,   887,   889,   891,   893,   895,   897,   899,   901,   903,
     905,   907,   909,   911,   913,   915,   917,   919,   921,   923,
     925,   927,   929,   931,   933,   938,   963,   977,  1006,  1031,
    1046,  1058,  1096,  1124,  1128,  1132,  1140,  1152,  1159,  1164,
    1196,  1210,  1223,  1256,  1269,  1279,  1290,  1301,  1316,  1330,
    1339,  1348,  1357,  1369,  1405,  1415,  1428,  1457,  1481,  1507,
    1517,  1533,  1551,  1566,  1587,  1610,  1624,  1637,  1655
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_AMPERSAND_lex", "CHAR_CARET_lex",
  "CHAR_ENDINPUT_lex", "CHAR_LEFTBRACE_lex", "CHAR_LEFTBRACKET_lex",
  "CHAR_LETTERS_lex", "CHAR_OPERATOR_lex", "CHAR_RIGHTBRACE_lex",
  "CHAR_RIGHTBRACKET_lex", "CHAR_UNDERBAR_lex", "CMD_BACKSLASH_lex",
  "CMD_BEGIN_ARRAY_lex", "CMD_DIACRITICAL_lex", "CMD_END_ARRAY_lex",
  "CMD_CHAR_lex", "CMD_COMMA_lex", "CMD_COLON_lex", "CMD_FONT_lex",
  "CMD_FRAC_lex", "CMD_HSPACE_lex", "CMD_LEFT_lex", "CMD_LEFTBRACKET_lex",
  "CMD_MATHML_lex", "CMD_OVERBRACE_lex", "CMD_OVERLINE_lex",
  "CMD_RIGHT_lex", "CMD_RIGHTBRACKET_lex", "CMD_SEMICOLON_lex",
  "CMD_SQRT_lex", "CMD_STACKREL_lex", "CMD_UNDERBRACE_lex",
  "CMD_UNDERLINE_lex", "CMD_WIDEHAT_lex", "CMD_WIDETILDE_lex",
  "NUMBER_lex", "STDFUN_lex", "STD_DISPLAY_lex", "SYM_ARROW_lex",
  "SYM_BINARYOP_lex", "SYM_DISPLAY_lex", "SYM_DOTS_lex", "SYM_ENCLOSE_lex",
  "SYM_GREEK_lex", "SYM_INTEGRAL_lex", "SYM_MISC_lex", "SYM_RELATION_lex",
  "$accept", "start", "start_inline", "start_block", "argument", "array",
  "array_begin", "array_colalign_list", "array_colalign", "array_col_next",
  "array_cols", "array_rowalign", "array_rows", "arrow", "binary",
  "diacritical", "dots", "encloser", "encloser_check", "element", "font",
  "frac", "greek", "group", "group_begin", "left_right_begin",
  "left_right", "letter", "list", "list_or_empty", "mathml", "misc",
  "number", "operator", "over", "over_cases", "relation", "space",
  "special_char", "sub_element_sup_element", "subsup", "sqrt", "stackrel",
  "stdfun", "std_display", "sym_display", "sym_enclose", "sym_integral",
  "underbrace", "underline", YY_NULLPTR
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

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -18,   -96,    12,   124,   124,   -96,   -96,   -96,   -96,    14,
      16,   -96,   -96,   -96,   -96,    16,   -96,   -96,   -96,   -96,
     -96,   -96,    13,    16,    16,    16,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   124,   -96,   -96,   -96,   -96,     6,   -96,   -96,   -96,
     -96,   124,    -4,   -96,   -96,   124,    18,   -96,   -96,   -96,
     -96,   -96,    16,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,    -2,    17,    20,   -96,
      16,   124,    16,   -96,    16,   -96,   -96,    21,    -5,   -96,
     124,   124,   -96,    19,   -96,   -96,   -96,   -96,   124,   -96,
       6,   -96,   -96,   -96,    23,    22,    24,   -96,   -96,    25,
     -96,   -96,   -96,   124,   124,   -96,    26,    27,   -96,    81,
     -96,   -96,   -96,    29,   -96,   -96,    21,   124,   124,    -4,
     -96,   -96,   -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     5,     0,    67,    67,     1,    59,    62,    72,    14,
       0,    83,    79,    80,    55,     0,    82,    60,    69,    74,
      75,    81,     0,     0,     0,     0,    76,    77,    71,    92,
      93,    18,    19,    94,    21,    95,    57,    96,    70,    78,
      27,    67,    28,    29,    30,    31,    63,    32,    33,    34,
      35,    67,     0,    36,    37,    68,     0,    38,    39,    40,
      41,    42,     0,    43,    44,    45,    64,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     0,     0,     0,    20,
       0,    67,     0,    89,     0,    97,    98,    16,     0,    12,
       0,     0,    86,     0,    25,    24,    26,    22,     0,    23,
      65,    66,     2,    73,     0,     0,     0,     8,    56,     0,
      90,    91,    11,    67,    67,     7,    88,    87,    58,     0,
       3,    15,     9,     0,     6,    13,    17,     0,     0,     0,
      10,    85,    84,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -84,   -96,   -96,   -96,   -96,   -96,   -96,   -95,   -96,   -46,
     -96,   -96,   -96,    -8,   -96,   -96,   -96,   -96,   -63,    -3,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -52,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    82,    40,    41,   123,   107,   113,
      87,    78,    88,    42,    43,    44,    45,    98,    99,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    89,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    92,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,    76,    79,   101,    94,    95,     1,    80,   114,   100,
      90,   115,     5,    96,    83,    84,    85,    86,    91,     6,
      81,    77,     6,   102,   112,   105,   106,   104,   120,   118,
     126,   128,   122,   121,   133,   119,   124,     0,   127,   130,
      97,     0,     0,     0,   116,   117,     0,     0,    93,     0,
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
       0,     0,   108,   100,   110,     0,   111,     0,   109,     0,
       0,   131,   132,     0,     0,     0,     0,     6,     0,     7,
       8,     0,     0,     0,     0,     9,    10,     0,    11,    12,
      13,    14,    15,    16,    17,     0,    18,    19,    20,   129,
     125,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       6,     0,     7,     8,     0,     0,     0,     0,     9,    10,
       0,    11,    12,    13,    14,    15,    16,    17,     0,    18,
      19,    20,     0,     0,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39
};

static const yytype_int16 yycheck[] =
{
       3,     4,    10,    55,     8,     9,    24,    15,    13,    55,
       4,    16,     0,    17,    22,    23,    24,    25,    12,     6,
       7,     7,     6,     5,     3,     8,     6,    29,     5,    10,
     114,     4,     8,    11,   129,    98,    11,    -1,    12,    10,
      44,    -1,    -1,    -1,    90,    91,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,
      -1,    -1,    80,   119,    82,    -1,    84,    -1,    81,    -1,
      -1,   127,   128,    -1,    -1,    -1,    -1,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    26,    27,    28,
     113,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    14,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    50,    51,    52,     0,     6,     8,     9,    14,
      15,    17,    18,    19,    20,    21,    22,    23,    25,    26,
      27,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      54,    55,    62,    63,    64,    65,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    78,     7,    60,    72,
      72,     7,    53,    72,    72,    72,    72,    59,    61,    78,
       4,    12,    88,    78,     8,     9,    17,    44,    66,    67,
      68,    89,     5,    72,    29,     8,     6,    57,    72,    78,
      72,    72,     3,    58,    13,    16,    68,    68,    10,    77,
       5,    11,     8,    56,    11,    78,    59,    12,     4,    28,
      10,    68,    68,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    59,    60,    60,    61,    61,    62,    63,
      64,    65,    66,    66,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    77,    77,    77,    78,    78,    79,
      80,    81,    82,    83,    84,    84,    84,    84,    85,    86,
      86,    86,    86,    87,    88,    88,    89,    89,    89,    90,
      90,    91,    92,    93,    94,    95,    96,    97,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     4,     0,     1,     3,     3,     3,     1,
       3,     1,     1,     3,     0,     3,     1,     3,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     1,
       1,     5,     1,     1,     1,     2,     2,     0,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     2,     3,     3,     2,
       3,     3,     1,     1,     1,     1,     1,     2,     2
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
#line 345 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		assert( (yyvsp[-1]).str != NULL || (yyvsp[-1]).line == 0 );
		assert( (yyvsp[-1]).str != NULL || LengthStype(& (yyvsp[-1])) == 1 );

		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( (yyvsp[-1]).str == NULL )
			return BlockDisplay;

		// close font command at this level
		assert( FontLevel == 0 );
		DecFontLevel(& (yyvsp[-1]), 0);

		// need a newline after heading in the inline case
		if( PreviousOmhelpOutputWasHeading() )
			ConvertForcedNewline(1);

		OutputString(
			"\n<math xmlns=\"http://www.w3.org/1998/Math/MathML\""
			" display=\"inline\"><mrow>\n"
		);
		OutputTexStype(& (yyvsp[-1]));
		OutputString("</mrow></math>\n\n");

		FreeTexStype(& (yyvsp[-1]));

		return BlockDisplay;
	}
#line 1684 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 3:
#line 377 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-3]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		assert( (yyvsp[-2]).str != NULL || (yyvsp[-2]).line == 0 );
		assert( (yyvsp[-2]).str != NULL || LengthStype(& (yyvsp[-2])) == 1 );

		assert( LengthStype(& (yyvsp[-3])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( (yyvsp[-2]).str == NULL ) fataltex(
			"empty $latex command between \\[ and \\]",
			NULL
		);

		// close font command that at this level
		assert( FontLevel == 0 );
		DecFontLevel(& (yyvsp[-2]), 0);

		OutputString(
			"\n<math xmlns=\"http://www.w3.org/1998/Math/MathML\""
			" display=\"block\"><mrow>\n"
		);
		OutputTexStype(& (yyvsp[-2]));
		OutputString("</mrow></math>\n\n");

		FreeTexStype(& (yyvsp[-2]));

		PopPending((yyvsp[-1]).line, "\\[");

		assert( NumberPending() == InitialNumberPending );

		return BlockDisplay;
	}
#line 1724 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 4:
#line 416 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	yydebug      = 0;
		BlockDisplay = 0;
		FontLevel    = -1;
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		InitialNumberPending = NumberPending();

		(yyval).line  = 0;
		(yyval).data  = 0;
		(yyval).str   = NULL;
		(yyval).next  = NULL;
		(yyval).extra = NULL;
	}
#line 1743 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 5:
#line 434 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	yydebug      = 0;
		BlockDisplay = 1;
		FontLevel    = -1;
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		InitialNumberPending = NumberPending();

		PushPending((yyvsp[0]).line, "\\[");

		(yyval).line  = 0;
		(yyval).data  = 0;
		(yyval).str   = NULL;
		(yyval).next  = NULL;
		(yyval).extra = NULL;
	}
#line 1764 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 6:
#line 454 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL || (yyvsp[-1]).line == 0 );
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( (yyvsp[-1]).str == NULL )
			(yyvsp[-1]).str = str_alloc(" ");

		CharPlusStype("<mrow>", & (yyvsp[-1]));
		StypePlusChar(& (yyvsp[-1]), "</mrow>");

		(yyval)      = (yyvsp[-1]);
		(yyval).line = (yyvsp[-2]).line;
	}
#line 1784 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 7:
#line 473 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[-1]).str != NULL || (yyvsp[-1]).line == 0 );
		assert( (yyvsp[-1]).str != NULL || LengthStype(& (yyvsp[-1])) == 1 );
		assert( (yyvsp[0]).str == NULL );
		assert( ArrayLevel > 0 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( (yyvsp[-1]).str != NULL )
			StypePlusStype(& (yyvsp[-2]), & (yyvsp[-1]));

		DecFontLevel(& (yyvsp[-2]), 0);
		StypePlusChar(& (yyvsp[-2]), "</mtd></mtr></mtable>\n");

		--ArrayLevel;

		PopPending((yyvsp[-2]).line , "\\begin{array}" );

		(yyval) = (yyvsp[-2]);
	}
#line 1808 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 8:
#line 496 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		(yyvsp[-2]).str  = StrCat(
			__FILE__,
			__LINE__,
			"<mtable ",
			(yyvsp[-1]).str,
			" ><mtr><mtd ",
			ArrayAlign[ArrayLevel][0],
			" >\n",
			NULL
		);
		++ArrayLevel;

		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		FreeMem((yyvsp[-1]).str);

		PushPending((yyvsp[-2]).line , "\\begin{array}" );

		(yyval) = (yyvsp[-2]);
	}
#line 1842 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 9:
#line 529 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		SetArrayAlign((yyvsp[0]).str);
		FreeMem((yyvsp[0]).str);

		(yyvsp[0]).str  = NULL;
		(yyval)      = (yyvsp[0]);
	}
#line 1857 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 10:
#line 543 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		(yyval) = (yyvsp[-2]);
	}
#line 1871 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 11:
#line 557 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// done with previous column when this is reduced
		DecFontLevel(& (yyvsp[0]), 1);
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		(yyval)      = (yyvsp[0]);
	}
#line 1887 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 12:
#line 572 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL || (yyvsp[0]).line == 0 );
		assert( ArrayLevel > 0 );

		(yyval)      = (yyvsp[0]);
		(yyval).data = 1;    // first column of the array
	}
#line 1898 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 13:
#line 579 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	char *str;

		int col;

		assert( (yyvsp[-2]).str != NULL || (yyvsp[-2]).line == 0 );
		assert( (yyvsp[-2]).str != NULL || LengthStype(& (yyvsp[-2])) == 1);

		// $2.str == NULL if no font is pending
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		assert( (yyvsp[0]).str != NULL || (yyvsp[0]).line == 0 );
		assert( (yyvsp[0]).str != NULL || LengthStype(& (yyvsp[0])) == 1);

		assert( ArrayLevel > 0 );
		assert( (yyval).data > 0 );

		col   = (yyvsp[-2]).data;

		if( ArrayAlign[ArrayLevel-1][col] == NULL ) fataltex(
			"to many columns of data in array",
			NULL
		);

		str = StrCat(
			__FILE__,
			__LINE__,
			"</mtd><mtd ",
			ArrayAlign[ArrayLevel-1][col],
			" >\n",
			NULL
		);

		if( (yyvsp[-2]).str != NULL )
		{	if( (yyvsp[-1]).str != NULL )
				StypePlusStype(& (yyvsp[-2]), & (yyvsp[-1]));

			StypePlusChar(& (yyvsp[-2]), str);
			FreeMem( str );

			if( (yyvsp[0]).str != NULL )
				StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));
		}
		else
		{	if( (yyvsp[-1]).str != NULL )
			{	(yyvsp[-2]) = (yyvsp[-1]);

				StypePlusChar(& (yyvsp[-2]), str);
				FreeMem( str );

				if( (yyvsp[0]).str != NULL )
					StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));
			}
			else
			{	(yyvsp[-2]).str = str;
				// do not want to free str in this case

				if( (yyvsp[0]).str != NULL )
					StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));
			}
		}

		(yyval)      = (yyvsp[-2]);
		(yyval).data = col + 1;   // next column of the array
	}
#line 1967 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 14:
#line 647 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// center is the default row alignment
		(yyval).line  = 0;
		(yyval).data  = 0;
		(yyval).str   = str_alloc("rowalign=\"center\"");
		(yyval).next  = NULL;
		(yyval).extra = NULL;
	}
#line 1979 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 15:
#line 655 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	size_t len;

		char *str;

		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		str = (yyvsp[-1]).str;
		len = strlen(str);

		if( len > 1 ) fataltex(
			"The row alignment specification \"",
			str,
			"\"\ncontains more than one character.",
			NULL
		);
		switch( str[0] )
		{	case 'b':
			(yyvsp[-2]).str = str_alloc("rowalign=\"bottom\"");
			break;

			case 'c':
			(yyvsp[-2]).str = str_alloc("rowalign=\"center\"");
			break;

			case 't':
			(yyvsp[-2]).str = str_alloc("rowalign=\"top\"");
			break;

			default:
			fataltex(
				"The row alignment character \"",
				str,
				"\" is not valid.\n",
				"The valid row alignment characters are ",
				"b, c, and t.",
				NULL
			);
		}
		FreeMem(str);

		(yyval) = (yyvsp[-2]);
	}
#line 2031 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 16:
#line 707 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL || (yyvsp[0]).line == 0 );
		assert( (yyvsp[0]).str != NULL || LengthStype(& (yyvsp[0])) == 1 );

		assert( ArrayLevel > 0 );
		(yyval)      = (yyvsp[0]);

		// no longer counting columns
		(yyval).data = 0;
	}
#line 2045 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 17:
#line 717 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str != NULL || (yyvsp[-2]).line == 0 );
		assert( (yyvsp[-2]).str != NULL || LengthStype(& (yyvsp[-2])) == 1 );

		assert( (yyvsp[0]).str != NULL || (yyvsp[0]).line == 0 );
		assert( (yyvsp[0]).str != NULL || LengthStype(& (yyvsp[0])) == 1 );

		assert( (yyvsp[-1]).str == NULL );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		// no longer counting columns
		(yyvsp[0]).data = 0;

		(yyvsp[-1]).str = StrCat(
			__FILE__,
			__LINE__,
			"</mtd></mtr><mtr><mtd ",
			ArrayAlign[ArrayLevel-1][0],
			" >\n",
			NULL
		);
		DecFontLevel(& (yyvsp[-1]), 1);
		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		if( (yyvsp[-2]).str != NULL )
			StypePlusStype(& (yyvsp[-2]), & (yyvsp[-1]));
		else	(yyvsp[-2]) = (yyvsp[-1]);
		if( (yyvsp[0]).str != NULL )
			StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));

		(yyval) = (yyvsp[-2]);
	}
#line 2082 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 18:
#line 753 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 2097 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 19:
#line 767 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">" , & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2111 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 20:
#line 780 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		CharPlusStype("<mover accent='false'>", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "<mo stretchy='false'>");
		StypePlusStype(& (yyvsp[0]), & (yyvsp[-1]));
		StypePlusChar(& (yyvsp[0]), "</mo></mover>\n");

		(yyval)      = (yyvsp[0]);
		(yyval).line = (yyvsp[-1]).line;
	}
#line 2128 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 21:
#line 797 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2142 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 22:
#line 811 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		(yyval) = (yyvsp[0]);
	}
#line 2152 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 23:
#line 817 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		switch( (yyvsp[0]).str[0] )
		{
			case '{':
			case '}':
			case ')':
			case '(':
			case '[':
			case ']':
			case '/':
			case '|':
			case '.':
			break;

			default:
			fataltex(
				"The character ",
				(yyvsp[0]).str,
				"\ncannot be used directly after ",
				"\\left or \\right",
				"\nbecause it is not an enclosing character",
				NULL
			);
		}

		(yyval) = (yyvsp[0]);
	}
#line 2186 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 24:
#line 850 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		(yyval) = (yyvsp[0]);
	}
#line 2196 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 25:
#line 856 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		fataltex(
			"The text ",
			(yyvsp[0]).str,
			"\ncannot be used directly after ",
			"\\left or \\right",
			"\nbecause it does not begin with ",
			"an enclosing character",
			NULL
		);

	}
#line 2215 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 26:
#line 871 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		(yyval) = (yyvsp[0]);
	}
#line 2225 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 27:
#line 880 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2231 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 28:
#line 882 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2237 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 29:
#line 884 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2243 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 30:
#line 886 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2249 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 31:
#line 888 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2255 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 32:
#line 890 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2261 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 33:
#line 892 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2267 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 34:
#line 894 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2273 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 35:
#line 896 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2279 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 36:
#line 898 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2285 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 37:
#line 900 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2291 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 38:
#line 902 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2297 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 39:
#line 904 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2303 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 40:
#line 906 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2309 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 41:
#line 908 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2315 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 42:
#line 910 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2321 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 43:
#line 912 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2327 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 44:
#line 914 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2333 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 45:
#line 916 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2339 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 46:
#line 918 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2345 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 47:
#line 920 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2351 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 48:
#line 922 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2357 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 49:
#line 924 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2363 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 50:
#line 926 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2369 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 51:
#line 928 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2375 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 52:
#line 930 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2381 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 53:
#line 932 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2387 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 54:
#line 934 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2393 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 55:
#line 939 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );


		// close previous font command and start new one
		assert( FontLevel >= 0 );
		if( CurrentFont[FontLevel] != NULL )
		{	FreeMem( CurrentFont[FontLevel] );
			CurrentFont[FontLevel] = str_alloc( (yyvsp[0]).str );

			// terminate previous font command
			CharPlusStype("</mstyle>", & (yyvsp[0]));
		}
		else	CurrentFont[FontLevel] = str_alloc( (yyvsp[0]).str );

		// $1 contains the <mstyle mathvariant='$1'> argument
		CharPlusStype("<mstyle mathvariant='", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "'>");

		(yyval) = (yyvsp[0]);
	}
#line 2419 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 56:
#line 964 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );

		CharPlusStype("<mfrac>", & (yyvsp[-1]));
		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));
		StypePlusChar(& (yyvsp[-1]), "</mfrac>\n");

		(yyval)      = (yyvsp[-1]);
		(yyval).line = (yyvsp[-2]).line;
	}
#line 2434 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 57:
#line 978 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	char *s;

		// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( GetCurrentFont() != NULL )
		{	s = StrCat(
				__FILE__,
				__LINE__,
				"<mi mathvariant='",
				GetCurrentFont(),
				"'>",
				NULL
			);
			CharPlusStype(s, & (yyvsp[0]));
			FreeMem(s);
		}
		else	CharPlusStype("<mi mathvariant='normal'>", & (yyvsp[0]));

		StypePlusChar(& (yyvsp[0]), "</mi>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2463 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1007 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// done processing this group
		assert( LengthStype(& (yyvsp[-2])) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );
		assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[0]).str == NULL );

		if( (yyvsp[-1]).str == NULL )
			(yyvsp[-1]).str = str_alloc(" ");

		// terminate font that is limited to this group
		DecFontLevel(& (yyvsp[-1]), 0);
		assert( FontLevel >= 0 );

		CharPlusStype("<mrow>", & (yyvsp[-1]));
		StypePlusChar(& (yyvsp[-1]), "</mrow>\n");

		PopPending((yyvsp[0]).line, "{");

		(yyval)      = (yyvsp[-1]);
		(yyval).line = (yyvsp[-2]).line;
	}
#line 2489 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1032 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// begin a group
		assert( LengthStype(& (yyvsp[0])) == 1 );
		assert( (yyvsp[0]).str == NULL );

		IncFontLevel();
		assert( CurrentFont[FontLevel] == NULL );

		PushPending((yyvsp[0]).line, "{");

		(yyval) = (yyvsp[0]);
	}
#line 2505 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1047 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[0]).str == NULL );
		assert( LengthStype( & (yyvsp[0]) ) == 1 );

		PushPending((yyvsp[0]).line, "\\left");

		(yyval) = (yyvsp[0]);
	}
#line 2518 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1059 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		assert( (yyvsp[-4]).str == NULL );
		assert( (yyvsp[-3]).str != NULL );
		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str != NULL );

		assert( LengthStype( & (yyvsp[-4]) ) == 1 );
		assert( LengthStype( & (yyvsp[-3]) ) == 1 );
		assert( LengthStype( & (yyvsp[-1]) ) == 1 );
		assert( LengthStype( & (yyvsp[0]) ) == 1 );

		if( strcmp((yyvsp[-3]).str, ".") == 0 )
		{	FreeMem((yyvsp[-3]).str);
			(yyvsp[-3]).str = str_alloc(" "); // replace . by nothing
		}
		if( strcmp((yyvsp[0]).str, ".") == 0 )
		{	FreeMem((yyvsp[0]).str);
			(yyvsp[0]).str = str_alloc(" "); // replace . by nothing
		}

		CharPlusStype("<mrow><mo stretchy=\"true\">", & (yyvsp[-3]));
		StypePlusChar(& (yyvsp[-3]), "</mo><mrow>");
		StypePlusStype(& (yyvsp[-3]), & (yyvsp[-2]));
		StypePlusChar(& (yyvsp[-3]), "</mrow><mo stretchy=\"true\">");
		StypePlusStype(& (yyvsp[-3]), & (yyvsp[0]));
		StypePlusChar(& (yyvsp[-3]), "</mo></mrow>\n");

		PopPending((yyvsp[-1]).line, "\\left");

		(yyval)      = (yyvsp[-3]);
		(yyval).line = (yyvsp[-4]).line;

	}
#line 2557 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1097 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	char *s;

		// str is the single letter
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( GetCurrentFont() != NULL )
		{	s = StrCat(
				__FILE__,
				__LINE__,
				"<mi mathvariant='",
				GetCurrentFont(),
				"'>",
				NULL
			);
			CharPlusStype(s, & (yyvsp[0]));
			FreeMem(s);
		}
		else	CharPlusStype("<mi mathvariant='italic'>", & (yyvsp[0]));

		StypePlusChar(& (yyvsp[0]), "</mi>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2586 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1125 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		(yyval) = (yyvsp[0]);
	}
#line 2594 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1129 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		(yyval) = (yyvsp[0]);
	}
#line 2602 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1133 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );

		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));

		(yyval) = (yyvsp[-1]);
	}
#line 2614 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1141 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );

		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));

		(yyval) = (yyvsp[-1]);
	}
#line 2626 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1152 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {
		(yyval).line  = 0;
		(yyval).data  = 0;
		(yyval).str   = NULL;
		(yyval).next  = NULL;
		(yyval).extra = NULL;
	}
#line 2638 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1160 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2644 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1165 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	int i;
		int j;
		int escape;
		char *str;

		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0]) ) == 1 );

		// replace escape sequences used for macros
		i      = 0;
		j      = 0;
		escape = 0;
		str    = (yyvsp[0]).str;
		while( str[i] != '\0' )
		{	if( escape )
			{	if( str[i] == '#' )
					--j;
				escape = 0;
			}
			else	escape = (str[i] == '\\');
			str[j] = str[i];
			++j;
			++i;
		}
		str[j] = '\0';

		(yyval) = (yyvsp[0]);
	}
#line 2677 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1197 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 2692 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1211 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str contains the number
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mn>", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mn>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 2706 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1224 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is one character and equal to operator
		char *str = (yyvsp[0]).str;

		assert( str != NULL );
		assert( strlen(str) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		switch( str[0] )
		{
			case '<':
			FreeMem(str);
			(yyvsp[0]).str = str = str_alloc("&lt;"); // lt = x0003C
			break;

			case '>':
			FreeMem(str);
			(yyvsp[0]).str = str = str_alloc("&gt;"); // gt = x0003E
			break;

			default:
			;
		}

		CharPlusStype("<mo stretchy=\"false\">" , & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 2740 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1257 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );

		CharPlusStype("<mover>", & (yyvsp[0]));
		StypePlusStype(& (yyvsp[0]), & (yyvsp[-1]));

		(yyval)      = (yyvsp[0]);
		(yyval).line = (yyvsp[-1]).line;
	}
#line 2754 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1270 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// OverBrace = #x0FE37
		(yyvsp[0]).str = str_alloc(
		"<mo stretchy=\"true\">&#x0FE37;</mo></mover>\n"
		);
		(yyval) = (yyvsp[0]);
	}
#line 2768 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1280 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// OverBar = #x000AF
		(yyvsp[0]).str = str_alloc(
		"<mo stretchy=\"true\">&#x000AF;</mo></mover>\n"
		);

		(yyval) = (yyvsp[0]);
	}
#line 2783 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1291 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// Hat = #x00302
		(yyvsp[0]).str = str_alloc(
		"<mo stretchy=\"true\">&#x00302;</mo></mover>\n"
		);

		(yyval) = (yyvsp[0]);
	}
#line 2798 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1302 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// DiacriticalTilde = x002DC
		(yyvsp[0]).str = str_alloc(
		"<mo stretchy=\"true\">&#x002DC;</mo></mover>\n"
		);

		(yyval) = (yyvsp[0]);
	}
#line 2813 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1317 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 2828 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1331 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// .9/5 because \hspace{.9em} is same as \, \, \, \, \,
		(yyvsp[0]).str = str_alloc("<mspace width='.18em'/>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2841 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1340 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// .9/4 because \hspace{.9em} is same as \: \: \: \:
		(yyvsp[0]).str = str_alloc("<mspace width='.225em'/>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2854 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1349 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str == NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		// .9/3 because \hspace{.9em} is same as \; \; \;
		(yyvsp[0]).str = str_alloc("<mspace width='.3em'/>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2867 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1358 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mspace width='", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "'/>\n");

		(yyval) = (yyvsp[0]);
	}
#line 2880 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1370 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is the entire command
		char *str = (yyvsp[0]).str;
		assert( strlen((yyvsp[0]).str) == 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		assert( str != NULL );

		switch( str[0] )
		{
			case '&':
			// convert raw ampersand to Unicode
			FreeMem(str);
			(yyvsp[0]).str = str = str_alloc("&amp;"); // amp = x00026
			// now drop same as the cases below

			case '#':
			case '$':
			case '%':
			case '_':
			case '{':
			case '}':
			CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
			StypePlusChar(& (yyvsp[0]), "</mo>\n");
			break;

			default:
			assert(0);
		}
		assert( LengthStype( & (yyvsp[0]) ) == 3 );

		(yyval) = (yyvsp[0]);
	}
#line 2917 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1406 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( LengthStype(& (yyvsp[-3])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		(yyval)       = (yyvsp[-2]);
		(yyval).line  = (yyvsp[-3]).line;
		(yyval).extra = AllocMem(sizeof(TexStype), 1);
		*((yyval).extra) = (yyvsp[0]);

	}
#line 2931 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1416 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( LengthStype(& (yyvsp[-3])) == 1 );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		(yyval)       = (yyvsp[0]);
		(yyval).line  = (yyvsp[-3]).line;
		(yyval).extra = AllocMem(sizeof(TexStype), 1);
		*((yyval).extra) = (yyvsp[-2]);

	}
#line 2945 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1429 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	TexStype *E;
		int munderover;

		assert( (yyvsp[-1]).str != NULL );
		assert(   (yyvsp[0]).str != NULL );
		assert( (yyvsp[0]).extra != NULL );

		E        = (yyvsp[0]).extra;
		(yyvsp[0]).extra = NULL;

		munderover = ( (yyvsp[-1]).data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& (yyvsp[-1])) == SUBSUP_2_UNDEROVER_LENGTH )
		;

		if( munderover )
			CharPlusStype("<munderover>", & (yyvsp[-1]));
		else	CharPlusStype("<msubsup>", & (yyvsp[-1]));

		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));
		StypePlusStype(& (yyvsp[-1]), E);

		if( munderover )
			StypePlusChar(& (yyvsp[-1]), "</munderover>\n");
		else	StypePlusChar(& (yyvsp[-1]), "</msubsup>\n");

		FreeMem(E);
		(yyval) = (yyvsp[-1]);
	}
#line 2978 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1458 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	int munder;

		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[-1])) == 1 );


		munder = ( (yyvsp[-2]).data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& (yyvsp[-2])) == SUBSUP_2_UNDEROVER_LENGTH )
		;

		if( munder )
			CharPlusStype("<munder>", & (yyvsp[-2]));
		else	CharPlusStype("<msub>", & (yyvsp[-2]));

		StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));

		if( munder )
			StypePlusChar(& (yyvsp[-2]), "</munder>\n");
		else	StypePlusChar(& (yyvsp[-2]), "</msub>\n");

		(yyval) = (yyvsp[-2]);
	}
#line 3006 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1482 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	int mover;

		assert( (yyvsp[-2]).str != NULL );
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		mover = ( (yyvsp[-2]).data == SUBSUP_2_UNDEROVER_DATA )
		           && ( LengthStype(& (yyvsp[-2])) == SUBSUP_2_UNDEROVER_LENGTH )
		;

		if( mover )
			CharPlusStype("<mover>", & (yyvsp[-2]));
		else	CharPlusStype("<msup>", & (yyvsp[-2]));

		StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));

		if( mover )
			StypePlusChar(& (yyvsp[-2]), "</mover>\n");
		else	StypePlusChar(& (yyvsp[-2]), "</msup>\n");

		(yyval) = (yyvsp[-2]);
	}
#line 3033 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1508 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str == NULL );
		assert( LengthStype(& (yyvsp[-1])) == 1 );

		CharPlusStype("<msqrt>", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</msqrt>\n");

		(yyval)      = (yyvsp[0]);
		(yyval).line = (yyvsp[-1]).line;
	}
#line 3047 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1518 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[-2])) == 1 );

		CharPlusStype("<mroot>", & (yyvsp[0]));
		StypePlusStype(& (yyvsp[0]), & (yyvsp[-1]));
		StypePlusChar(& (yyvsp[0]), "</mroot>\n");

		(yyval)      = (yyvsp[0]);
		(yyval).line = (yyvsp[-2]).line;
	}
#line 3064 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1534 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-2]).str == NULL );
		assert( (yyvsp[-1]).str != NULL );
		assert( (yyvsp[0]).str != NULL );

		assert( LengthStype(& (yyvsp[-2])) == 1 );

		(yyvsp[-2]).str = str_alloc("<mover>");
		StypePlusStype(& (yyvsp[-2]), & (yyvsp[0]));
		StypePlusStype(& (yyvsp[-2]), & (yyvsp[-1]));
		StypePlusChar(& (yyvsp[-2]), "</mover>\n");

		(yyval) = (yyvsp[-2]);
	}
#line 3082 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1552 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is the name of the standard function
		assert( (yyvsp[0]).str != NULL );
		assert( strlen((yyvsp[0]).str) > 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mi>", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mi>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 3098 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1567 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is the name of the standard function
		assert( (yyvsp[0]).str != NULL );
		assert( strlen((yyvsp[0]).str) > 1 );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mi>", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mi>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);

		// if BlockDisplay is true, use under/over inplace of sub/sup
		assert( LengthStype( & (yyval) ) == SUBSUP_2_UNDEROVER_LENGTH );
		if( BlockDisplay )
			(yyval).data = SUBSUP_2_UNDEROVER_DATA;
	}
#line 3119 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1588 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	char *s;

		// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		if( BlockDisplay )
			s = "<mo displaystyle='true' largeop='true'>";
		else	s = "<mo displaystyle='false' largeop='true' >";
		CharPlusStype(s, & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		(yyval) = (yyvsp[0]);

		// if BlockDisplay is true, use under/over inplace of sub/sup
		assert( LengthStype( & (yyval) ) == SUBSUP_2_UNDEROVER_LENGTH );
		if( BlockDisplay )
			(yyval).data = SUBSUP_2_UNDEROVER_DATA;
	}
#line 3143 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1611 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		assert( LengthStype( & (yyvsp[0]) ) == 3 );
		(yyval) = (yyvsp[0]);
	}
#line 3158 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1625 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	// str is unicode for this symbol
		assert( (yyvsp[0]).str != NULL );
		assert( LengthStype(& (yyvsp[0])) == 1 );

		CharPlusStype("<mo stretchy=\"false\">", & (yyvsp[0]));
		StypePlusChar(& (yyvsp[0]), "</mo>\n");

		(yyval) = (yyvsp[0]);
	}
#line 3172 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1638 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str != NULL );

		assert( LengthStype(& (yyvsp[-1])) == 1 );

		(yyvsp[-1]).str = str_alloc("<munder>");
		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));

		// UnderBrace = x0FE38
		StypePlusChar(& (yyvsp[-1]),
		"<mo stretchy=\"true\">&#x0FE38;</mo></munder>\n");

		(yyval) = (yyvsp[-1]);
	}
#line 3191 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1656 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1646  */
    {	assert( (yyvsp[-1]).str == NULL );
		assert( (yyvsp[0]).str != NULL );

		assert( LengthStype(& (yyvsp[-1])) == 1 );

		(yyvsp[-1]).str = str_alloc("<munder>");
		StypePlusStype(& (yyvsp[-1]), & (yyvsp[0]));

		// UnderBar (x00332) does not work in Mozilla
		// so we use OverBar (x000AF) in its place
		StypePlusChar(& (yyvsp[-1]),
		"<mo stretchy=\"true\">&#x000AF;</mo></munder>\n");

		(yyval) = (yyvsp[-1]);
	}
#line 3211 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
    break;


#line 3215 "/home/bradbell/omhelp.git/src/latex.c" /* yacc.c:1646  */
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
#line 1674 "/home/bradbell/omhelp.git/src/latex.y" /* yacc.c:1906  */

