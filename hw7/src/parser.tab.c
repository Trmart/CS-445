/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW7
Dr. Wilder
DUE: 5/5/2023

FILE: parser.y
DESC: Holds the grammar for the c- language. 
*/

#include "scanType.h"  
#include "AST.h"
#include "semantic.h"
#include "IOinit.h"
#include "yyerror.h"
#include "codeGeneration.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  
#include <getopt.h>
#include <iostream>
#include <string>

extern int yylex();
extern FILE *yyin;
extern int line;       
extern int numErrors;  
int numWarnings;       
bool isPrintingTreeTypes = false;

//memeory information
bool isPrintingMemoryOffset = false;
bool isPrintingMemorySize = false;
extern int globalOffset;

bool isOnlyPrintingMemoryInfo = false;


static TreeNode* ROOT;

extern SymbolTable symbolTable;

// #define YYERROR_VERBOSE


#line 124 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUMCONST = 4,                   /* NUMCONST  */
  YYSYMBOL_CHARCONST = 5,                  /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 6,                /* STRINGCONST  */
  YYSYMBOL_ASGN = 7,                       /* ASGN  */
  YYSYMBOL_ADDASGN = 8,                    /* ADDASGN  */
  YYSYMBOL_SUBASS = 9,                     /* SUBASS  */
  YYSYMBOL_INC = 10,                       /* INC  */
  YYSYMBOL_DEC = 11,                       /* DEC  */
  YYSYMBOL_GEQ = 12,                       /* GEQ  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_NEQ = 14,                       /* NEQ  */
  YYSYMBOL_MULASS = 15,                    /* MULASS  */
  YYSYMBOL_DIVASS = 16,                    /* DIVASS  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_BY = 21,                        /* BY  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_THEN = 23,                      /* THEN  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_BREAK = 25,                     /* BREAK  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_BOOL = 27,                      /* BOOL  */
  YYSYMBOL_CHAR = 28,                      /* CHAR  */
  YYSYMBOL_STATIC = 29,                    /* STATIC  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_BEGN = 31,                      /* BEGN  */
  YYSYMBOL_FINISH = 32,                    /* FINISH  */
  YYSYMBOL_DO = 33,                        /* DO  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_TO = 35,                        /* TO  */
  YYSYMBOL_BOOLCONST = 36,                 /* BOOLCONST  */
  YYSYMBOL_QUESTION = 37,                  /* QUESTION  */
  YYSYMBOL_LESS = 38,                      /* LESS  */
  YYSYMBOL_GREAT = 39,                     /* GREAT  */
  YYSYMBOL_PLUS = 40,                      /* PLUS  */
  YYSYMBOL_EQUAL = 41,                     /* EQUAL  */
  YYSYMBOL_MULT = 42,                      /* MULT  */
  YYSYMBOL_DIV = 43,                       /* DIV  */
  YYSYMBOL_MOD = 44,                       /* MOD  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_OBRACKET = 46,                  /* OBRACKET  */
  YYSYMBOL_CBRACKET = 47,                  /* CBRACKET  */
  YYSYMBOL_MINUS = 48,                     /* MINUS  */
  YYSYMBOL_COLON = 49,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 50,                 /* SEMICOLON  */
  YYSYMBOL_OPAREN = 51,                    /* OPAREN  */
  YYSYMBOL_CPAREN = 52,                    /* CPAREN  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_declarationList = 55,           /* declarationList  */
  YYSYMBOL_declaration = 56,               /* declaration  */
  YYSYMBOL_varDeclaration = 57,            /* varDeclaration  */
  YYSYMBOL_scopedtypespecificer = 58,      /* scopedtypespecificer  */
  YYSYMBOL_vardeclarationList = 59,        /* vardeclarationList  */
  YYSYMBOL_varDeclarationInit = 60,        /* varDeclarationInit  */
  YYSYMBOL_varDeclarationId = 61,          /* varDeclarationId  */
  YYSYMBOL_typespec = 62,                  /* typespec  */
  YYSYMBOL_funDeclaration = 63,            /* funDeclaration  */
  YYSYMBOL_parameters = 64,                /* parameters  */
  YYSYMBOL_parameterList = 65,             /* parameterList  */
  YYSYMBOL_parameterTypeList = 66,         /* parameterTypeList  */
  YYSYMBOL_parameterIdList = 67,           /* parameterIdList  */
  YYSYMBOL_parameterId = 68,               /* parameterId  */
  YYSYMBOL_statement = 69,                 /* statement  */
  YYSYMBOL_matched = 70,                   /* matched  */
  YYSYMBOL_unmatched = 71,                 /* unmatched  */
  YYSYMBOL_expstatement = 72,              /* expstatement  */
  YYSYMBOL_statementEnd = 73,              /* statementEnd  */
  YYSYMBOL_compoundstatement = 74,         /* compoundstatement  */
  YYSYMBOL_localdeclaration = 75,          /* localdeclaration  */
  YYSYMBOL_statementList = 76,             /* statementList  */
  YYSYMBOL_iterRange = 77,                 /* iterRange  */
  YYSYMBOL_returnstatement = 78,           /* returnstatement  */
  YYSYMBOL_breakstatement = 79,            /* breakstatement  */
  YYSYMBOL_asgnop = 80,                    /* asgnop  */
  YYSYMBOL_exp = 81,                       /* exp  */
  YYSYMBOL_simpleExp = 82,                 /* simpleExp  */
  YYSYMBOL_andExp = 83,                    /* andExp  */
  YYSYMBOL_relExp = 84,                    /* relExp  */
  YYSYMBOL_unaryRelExp = 85,               /* unaryRelExp  */
  YYSYMBOL_operator = 86,                  /* operator  */
  YYSYMBOL_sumExp = 87,                    /* sumExp  */
  YYSYMBOL_sumop = 88,                     /* sumop  */
  YYSYMBOL_mulExp = 89,                    /* mulExp  */
  YYSYMBOL_mulop = 90,                     /* mulop  */
  YYSYMBOL_unaryExp = 91,                  /* unaryExp  */
  YYSYMBOL_unaryop = 92,                   /* unaryop  */
  YYSYMBOL_mutable = 93,                   /* mutable  */
  YYSYMBOL_immutable = 94,                 /* immutable  */
  YYSYMBOL_factor = 95,                    /* factor  */
  YYSYMBOL_call = 96,                      /* call  */
  YYSYMBOL_args = 97,                      /* args  */
  YYSYMBOL_argList = 98,                   /* argList  */
  YYSYMBOL_constant = 99                   /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   666

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    84,    85,    88,    89,    90,    94,    95,
      96,   100,   107,   111,   112,   113,   114,   118,   119,   120,
     124,   128,   135,   136,   139,   140,   141,   147,   156,   161,
     162,   163,   164,   167,   168,   173,   174,   175,   176,   180,
     181,   185,   186,   187,   188,   191,   194,   200,   201,   204,
     205,   210,   215,   223,   224,   225,   226,   227,   228,   229,
     232,   237,   241,   246,   254,   255,   258,   259,   260,   263,
     264,   265,   266,   271,   279,   280,   283,   284,   287,   291,
     296,   297,   298,   301,   304,   310,   314,   319,   323,   327,
     331,   335,   341,   346,   348,   353,   358,   359,   360,   361,
     364,   370,   371,   374,   380,   381,   384,   388,   389,   392,
     397,   398,   401,   405,   410,   414,   419,   423,   429,   433,
     434,   437,   441,   447,   451,   452,   455,   459,   463,   469,
     472,   473,   476,   480,   484,   490,   493,   502,   503,   504,
     505,   508,   509,   513,   517,   520,   521,   524,   525,   526,
     528,   532,   537,   543
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUMCONST",
  "CHARCONST", "STRINGCONST", "ASGN", "ADDASGN", "SUBASS", "INC", "DEC",
  "GEQ", "LEQ", "NEQ", "MULASS", "DIVASS", "INT", "IF", "OR", "NOT", "BY",
  "ELSE", "THEN", "FOR", "BREAK", "RETURN", "BOOL", "CHAR", "STATIC",
  "AND", "BEGN", "FINISH", "DO", "WHILE", "TO", "BOOLCONST", "QUESTION",
  "LESS", "GREAT", "PLUS", "EQUAL", "MULT", "DIV", "MOD", "COMMA",
  "OBRACKET", "CBRACKET", "MINUS", "COLON", "SEMICOLON", "OPAREN",
  "CPAREN", "$accept", "program", "declarationList", "declaration",
  "varDeclaration", "scopedtypespecificer", "vardeclarationList",
  "varDeclarationInit", "varDeclarationId", "typespec", "funDeclaration",
  "parameters", "parameterList", "parameterTypeList", "parameterIdList",
  "parameterId", "statement", "matched", "unmatched", "expstatement",
  "statementEnd", "compoundstatement", "localdeclaration", "statementList",
  "iterRange", "returnstatement", "breakstatement", "asgnop", "exp",
  "simpleExp", "andExp", "relExp", "unaryRelExp", "operator", "sumExp",
  "sumop", "mulExp", "mulop", "unaryExp", "unaryop", "mutable",
  "immutable", "factor", "call", "args", "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-147)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,   614,    24,  -183,  -183,  -183,    84,   632,  -183,  -183,
     179,  -183,   170,    51,   103,  -183,    56,     9,  -183,  -183,
     236,   120,   134,  -183,   304,   131,   253,  -183,   304,   181,
     256,    64,    70,  -183,  -183,    11,  -183,    55,   140,  -183,
    -183,  -183,   317,  -183,  -183,  -183,  -183,   324,   105,   106,
    -183,  -183,   239,   180,  -183,   549,  -183,  -183,  -183,  -183,
    -183,  -183,   102,   170,  -183,   105,   107,   110,   138,  -183,
      10,    90,   181,   124,  -183,   344,    89,    55,  -183,   154,
     141,   105,   230,   373,   393,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   562,   602,  -183,  -183,  -183,   615,    55,
    -183,  -183,   153,   261,  -183,  -183,  -183,  -183,  -183,   163,
     154,   160,  -183,   151,   166,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,   344,  -183,  -183,  -183,   400,    55,   106,    55,
    -183,    55,   -21,    55,   180,    55,  -183,  -183,  -183,  -183,
      94,  -183,  -183,  -183,   413,  -183,   154,  -183,    40,  -183,
     270,   184,   154,  -183,   270,   147,    14,   453,   290,   162,
     109,  -183,   466,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,   186,   156,  -183,  -183,    20,    21,  -183,   240,
    -183,    38,  -183,   193,   -19,    53,  -183,  -183,   224,   264,
     264,   473,  -183,  -183,   224,   264,   493,   291,   466,  -183,
    -183,   241,  -183,   254,    45,   263,    -2,  -183,  -183,  -183,
      76,    85,   295,    54,   264,   264,   302,   224,   264,   522,
     224,   224,   473,   224,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,    55,   278,   282,   289,   280,   542,   224,   224,
     224,    55,   105
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    24,    26,    25,     0,     0,     4,     6,
       0,     5,    16,    20,     0,    15,    17,     0,     1,     3,
      29,    20,     0,    23,     0,     0,     0,     9,     0,    31,
       0,     0,    33,    36,    10,     0,     8,     0,   135,   150,
     151,   153,     0,   152,   134,   133,   132,     0,    19,   101,
     110,   104,   108,   119,   124,     0,   141,   142,   130,   138,
     139,    22,     0,    14,    13,    18,    40,    45,    39,    42,
       0,     0,    30,     0,   144,     0,     0,   111,   109,   140,
       0,    93,   141,     0,     0,   113,   115,   117,   114,   112,
     121,   116,   122,     0,     0,   126,   127,   128,     0,   131,
     129,    21,     0,     0,    32,    75,    28,    37,    35,     0,
       0,     0,   148,     0,   145,    87,    88,    89,    98,    99,
      90,    91,     0,   137,    94,    95,     0,   102,   100,   105,
     103,   107,   106,   120,   118,   125,   123,    46,    43,    41,
      77,    27,   136,   143,     0,    96,    97,    92,     0,    74,
       0,     0,   149,   147,     0,     0,     0,     0,     0,     0,
       0,    73,     0,    67,    76,    47,    48,    69,    49,    70,
      72,    71,     0,     0,    12,    68,    53,     0,    59,     0,
      86,     0,    83,     0,    57,     0,    66,    11,     0,     0,
       0,     0,    85,    84,     0,     0,     0,     0,     0,    54,
      64,    47,    61,    47,     0,     0,     0,    56,    51,    62,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    65,    50,    60,    81,    58,
      52,    63,    80,    78,     0,     0,     0,     0,     0,     0,
       0,    82,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,   309,  -183,  -183,    -7,   293,  -183,     2,
    -183,   296,  -183,   246,  -183,   223,  -182,  -138,   -37,  -183,
    -183,   -54,  -183,  -183,   111,  -183,  -183,   250,   -41,   -23,
     251,  -183,   -22,  -183,   242,  -183,   244,  -183,   -40,  -183,
     -24,  -183,  -183,  -183,  -183,  -183,  -183
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,     8,     9,   149,    14,    15,    16,    30,
      11,    31,    32,    33,    68,    69,   164,   208,   166,   167,
     168,   169,   140,   151,   205,   170,   171,   122,   172,    81,
      49,    50,    51,    93,    52,    94,    53,    98,    54,    55,
      82,    57,    58,    59,   113,   114,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    48,    10,    22,    56,    65,    80,   200,   202,    10,
      29,   104,    72,   165,   194,   100,   106,    83,    56,    90,
      78,   115,   116,   117,   118,   119,     3,    92,     3,   120,
     121,    56,    74,   219,   111,   112,     4,     5,     4,     5,
      83,   105,   188,   189,   190,   115,   116,   117,   118,   119,
     199,   201,   203,   120,   121,   141,   207,     3,   136,    56,
      56,   -34,   130,   -34,   175,    74,   216,     4,     5,    56,
      56,    74,    83,    83,    56,    17,   224,   226,   217,   229,
     230,   145,   234,   235,    18,   147,   195,   223,   192,    74,
     110,   107,    38,    39,    40,    41,    74,    25,   188,   220,
     224,   226,   230,   153,    83,    28,    74,     3,   221,    42,
     181,     3,    38,    39,    40,    41,    70,     4,     5,   183,
      71,     4,     5,   148,    83,    43,    44,    74,     1,    42,
       2,    45,    61,    56,   177,    62,    84,    46,    56,   185,
      47,  -146,   150,   155,     3,    43,    44,   173,    26,   101,
     154,    45,   -44,    27,     4,     5,   102,    46,   209,   182,
      47,   115,   116,   117,   118,   119,    25,    56,   206,   120,
     121,    35,    56,   211,    56,   213,   109,   225,   227,    26,
      20,   231,    21,   103,    36,   156,    75,    38,    39,    40,
      41,    76,    26,   123,   105,    56,   233,   174,    56,   206,
     137,    26,   157,   143,    42,    74,   187,   142,   158,   159,
     160,   144,   180,    56,   242,   105,   161,    23,   162,    24,
      43,    44,    95,    96,    97,   156,    45,    38,    39,    40,
      41,   -38,    46,   -38,   163,    47,   186,   115,   116,   117,
     124,   125,   196,   193,    42,   120,   121,   191,   197,   159,
     160,    85,    86,    87,    63,   105,    13,    66,   198,    67,
      43,    44,   138,   214,    67,   156,    45,    38,    39,    40,
      41,    12,    46,    13,   163,    47,   215,    88,    89,    90,
      91,   -16,   157,    23,    42,    24,    34,    92,   158,   159,
     160,   178,   178,   179,   212,   105,   218,    83,   162,   237,
      43,    44,   222,   228,   238,    37,    45,    38,    39,    40,
      41,   239,    46,   240,   163,    47,    19,   108,    77,    64,
      38,    39,    40,    41,    42,    79,   139,    38,    39,    40,
      41,    73,   126,   236,   128,   132,     0,    42,   134,     0,
      43,    44,     0,     0,    42,   110,    45,    38,    39,    40,
      41,     0,    46,    43,    44,    47,     0,     0,     0,    45,
      43,    44,     0,     0,    42,    46,    45,     0,    47,     0,
       0,     0,    46,     0,   127,    47,    38,    39,    40,    41,
      43,    44,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,    46,    42,   129,    47,    38,    39,    40,    41,
       0,   146,     0,    38,    39,    40,    41,     0,     0,    43,
      44,     0,     0,    42,   152,    45,    38,    39,    40,    41,
      42,    46,     0,     0,    47,     0,     0,     0,     0,    43,
      44,     0,     0,    42,     0,    45,    43,    44,     0,     0,
       0,    46,    45,     0,    47,     0,     0,     0,    46,    43,
      44,    47,     0,     0,   176,    45,    38,    39,    40,    41,
       0,    46,     0,     0,    47,     0,     0,   184,     0,    38,
      39,    40,    41,    42,   204,     0,    38,    39,    40,    41,
       0,     0,     0,     0,     0,     0,    42,     0,     0,    43,
      44,     0,     0,    42,   210,    45,    38,    39,    40,    41,
       0,    46,    43,    44,    47,     0,     0,     0,    45,    43,
      44,     0,     0,    42,    46,    45,     0,    47,     0,     0,
       0,    46,     0,   232,    47,    38,    39,    40,    41,    43,
      44,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,    46,    42,   241,    47,    38,    39,    40,    41,     0,
      99,     0,    38,    39,    40,    41,     0,     0,    43,    44,
       0,     0,    42,   131,    45,    38,    39,    40,    41,     0,
      46,     0,     0,    47,     0,     0,     0,     0,    43,    44,
       0,     0,     0,     0,    45,    43,    44,     0,     0,     0,
      46,    45,     0,    47,     0,     0,     0,    46,    43,    44,
      47,     0,     0,   133,    45,    38,    39,    40,    41,     0,
      46,     0,     0,    47,    -7,    12,   135,    13,    38,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    -7,    -2,     1,     0,     2,     0,     0,    43,    44,
       0,    -7,    -7,     0,    45,     0,     0,     0,     0,     3,
      46,    43,    44,    47,     0,     0,     0,    45,     0,     4,
       5,     0,     0,    46,     0,     0,    47
};

static const yytype_int16 yycheck[] =
{
      24,    24,     0,    10,    28,    28,    47,   189,   190,     7,
       1,     1,     1,   151,    33,    55,    70,    19,    42,    40,
      42,     7,     8,     9,    10,    11,    17,    48,    17,    15,
      16,    55,    51,    35,    75,    76,    27,    28,    27,    28,
      19,    31,    22,    23,    23,     7,     8,     9,    10,    11,
     188,   189,   190,    15,    16,   109,   194,    17,    98,    83,
      84,    52,    84,    52,    50,    51,    21,    27,    28,    93,
      94,    51,    19,    19,    98,    51,   214,   215,    33,   217,
     218,   122,   220,   221,     0,   126,    33,    33,    50,    51,
       1,     1,     3,     4,     5,     6,    51,    46,    22,    23,
     238,   239,   240,   144,    19,    49,    51,    17,    23,    20,
       1,    17,     3,     4,     5,     6,    52,    27,    28,   160,
      50,    27,    28,    29,    19,    36,    37,    51,     1,    20,
       3,    42,     1,   157,   157,     4,    30,    48,   162,   162,
      51,    52,   140,   150,    17,    36,    37,   154,    45,    47,
     148,    42,    45,    50,    27,    28,    46,    48,   195,    50,
      51,     7,     8,     9,    10,    11,    46,   191,   191,    15,
      16,    51,   196,   196,   198,   198,    52,   214,   215,    45,
       1,   218,     3,    45,    50,     1,    46,     3,     4,     5,
       6,    51,    45,    52,    31,   219,   219,    50,   222,   222,
      47,    45,    18,    52,    20,    51,    50,    47,    24,    25,
      26,    45,    50,   237,   237,    31,    32,    47,    34,    49,
      36,    37,    42,    43,    44,     1,    42,     3,     4,     5,
       6,    50,    48,    52,    50,    51,    50,     7,     8,     9,
      10,    11,    18,    50,    20,    15,    16,     7,    24,    25,
      26,    12,    13,    14,     1,    31,     3,     1,    34,     3,
      36,    37,     1,    22,     3,     1,    42,     3,     4,     5,
       6,     1,    48,     3,    50,    51,    22,    38,    39,    40,
      41,    45,    18,    47,    20,    49,    50,    48,    24,    25,
      26,     1,     1,     3,     3,    31,    33,    19,    34,    21,
      36,    37,     7,     1,    22,     1,    42,     3,     4,     5,
       6,    22,    48,    33,    50,    51,     7,    71,     1,    26,
       3,     4,     5,     6,    20,     1,   103,     3,     4,     5,
       6,    35,    82,   222,    83,    93,    -1,    20,    94,    -1,
      36,    37,    -1,    -1,    20,     1,    42,     3,     4,     5,
       6,    -1,    48,    36,    37,    51,    -1,    -1,    -1,    42,
      36,    37,    -1,    -1,    20,    48,    42,    -1,    51,    -1,
      -1,    -1,    48,    -1,     1,    51,     3,     4,     5,     6,
      36,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    48,    20,     1,    51,     3,     4,     5,     6,
      -1,     1,    -1,     3,     4,     5,     6,    -1,    -1,    36,
      37,    -1,    -1,    20,     1,    42,     3,     4,     5,     6,
      20,    48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    20,    -1,    42,    36,    37,    -1,    -1,
      -1,    48,    42,    -1,    51,    -1,    -1,    -1,    48,    36,
      37,    51,    -1,    -1,     1,    42,     3,     4,     5,     6,
      -1,    48,    -1,    -1,    51,    -1,    -1,     1,    -1,     3,
       4,     5,     6,    20,     1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    36,
      37,    -1,    -1,    20,     1,    42,     3,     4,     5,     6,
      -1,    48,    36,    37,    51,    -1,    -1,    -1,    42,    36,
      37,    -1,    -1,    20,    48,    42,    -1,    51,    -1,    -1,
      -1,    48,    -1,     1,    51,     3,     4,     5,     6,    36,
      37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    48,    20,     1,    51,     3,     4,     5,     6,    -1,
       1,    -1,     3,     4,     5,     6,    -1,    -1,    36,    37,
      -1,    -1,    20,     1,    42,     3,     4,     5,     6,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    42,    36,    37,    -1,    -1,    -1,
      48,    42,    -1,    51,    -1,    -1,    -1,    48,    36,    37,
      51,    -1,    -1,     1,    42,     3,     4,     5,     6,    -1,
      48,    -1,    -1,    51,     0,     1,     1,     3,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,     0,     1,    -1,     3,    -1,    -1,    36,    37,
      -1,    27,    28,    -1,    42,    -1,    -1,    -1,    -1,    17,
      48,    36,    37,    51,    -1,    -1,    -1,    42,    -1,    27,
      28,    -1,    -1,    48,    -1,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    17,    27,    28,    54,    55,    56,    57,
      62,    63,     1,     3,    59,    60,    61,    51,     0,    56,
       1,     3,    59,    47,    49,    46,    45,    50,    49,     1,
      62,    64,    65,    66,    50,    51,    50,     1,     3,     4,
       5,     6,    20,    36,    37,    42,    48,    51,    82,    83,
      84,    85,    87,    89,    91,    92,    93,    94,    95,    96,
      99,     1,     4,     1,    60,    82,     1,     3,    67,    68,
      52,    50,     1,    64,    51,    46,    51,     1,    85,     1,
      81,    82,    93,    19,    30,    12,    13,    14,    38,    39,
      40,    41,    48,    86,    88,    42,    43,    44,    90,     1,
      91,    47,    46,    45,     1,    31,    74,     1,    66,    52,
       1,    81,    81,    97,    98,     7,     8,     9,    10,    11,
      15,    16,    80,    52,    10,    11,    80,     1,    83,     1,
      85,     1,    87,     1,    89,     1,    91,    47,     1,    68,
      75,    74,    47,    52,    45,    81,     1,    81,    29,    58,
      62,    76,     1,    81,    62,    59,     1,    18,    24,    25,
      26,    32,    34,    50,    69,    70,    71,    72,    73,    74,
      78,    79,    81,    59,    50,    50,     1,    82,     1,     3,
      50,     1,    50,    81,     1,    82,    50,    50,    22,    23,
      23,     7,    50,    50,    33,    33,    18,    24,    34,    70,
      69,    70,    69,    70,     1,    77,    82,    70,    70,    71,
       1,    82,     3,    82,    22,    22,    21,    33,    33,    35,
      23,    23,     7,    33,    70,    71,    70,    71,     1,    70,
      70,    71,     1,    82,    70,    70,    77,    21,    22,    22,
      33,     1,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    73,    73,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    78,    78,    78,    79,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,    99,    99
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     3,     1,     1,     1,     3,     3,
       1,     4,     3,     2,     1,     1,     1,     6,     5,     2,
       4,     3,     5,     1,     0,     3,     1,     3,     1,     2,
       2,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       6,     4,     6,     2,     4,     6,     4,     2,     6,     2,
       6,     4,     4,     6,     4,     6,     2,     1,     2,     1,
       1,     1,     1,     4,     2,     0,     2,     0,     3,     5,
       3,     3,     5,     2,     3,     3,     2,     1,     1,     1,
       1,     1,     3,     1,     2,     2,     3,     3,     2,     2,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     4,     3,     1,     1,
       2,     1,     1,     4,     2,     1,     0,     3,     1,     3,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarationList  */
#line 80 "parser.y"
                                                                 { ROOT = (yyvsp[0].node);}
#line 1743 "parser.tab.c"
    break;

  case 3: /* declarationList: declarationList declaration  */
#line 84 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1749 "parser.tab.c"
    break;

  case 4: /* declarationList: declaration  */
#line 85 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1755 "parser.tab.c"
    break;

  case 5: /* declaration: funDeclaration  */
#line 88 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1761 "parser.tab.c"
    break;

  case 6: /* declaration: varDeclaration  */
#line 89 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1767 "parser.tab.c"
    break;

  case 7: /* declaration: error  */
#line 90 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 1773 "parser.tab.c"
    break;

  case 8: /* varDeclaration: typespec vardeclarationList SEMICOLON  */
#line 94 "parser.y"
                                                              { (yyval.node) = (yyvsp[-1].node); setType((yyval.node), (yyvsp[-2].type)); yyerrok;}
#line 1779 "parser.tab.c"
    break;

  case 9: /* varDeclaration: error vardeclarationList SEMICOLON  */
#line 95 "parser.y"
                                                              { (yyval.node) = NULL; yyerrok;}
#line 1785 "parser.tab.c"
    break;

  case 10: /* varDeclaration: typespec error SEMICOLON  */
#line 96 "parser.y"
                                                              { (yyval.node) = NULL; yyerrok;}
#line 1791 "parser.tab.c"
    break;

  case 11: /* scopedtypespecificer: STATIC typespec vardeclarationList SEMICOLON  */
#line 100 "parser.y"
                                                                {   
                                                                  (yyval.node) = (yyvsp[-1].node); 
                                                                  (yyval.node)->isStatic = true; 
                                                                  setType((yyval.node), (yyvsp[-2].type));
                                                                  yyerrok;
                                                                }
#line 1802 "parser.tab.c"
    break;

  case 12: /* scopedtypespecificer: typespec vardeclarationList SEMICOLON  */
#line 107 "parser.y"
                                                               { (yyval.node) = (yyvsp[-1].node); setType((yyval.node), (yyvsp[-2].type)); yyerrok;}
#line 1808 "parser.tab.c"
    break;

  case 13: /* vardeclarationList: vardeclarationList COMMA varDeclarationInit  */
#line 111 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok;}
#line 1814 "parser.tab.c"
    break;

  case 14: /* vardeclarationList: vardeclarationList COMMA error  */
#line 112 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 1820 "parser.tab.c"
    break;

  case 15: /* vardeclarationList: varDeclarationInit  */
#line 113 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1826 "parser.tab.c"
    break;

  case 16: /* vardeclarationList: error  */
#line 114 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1832 "parser.tab.c"
    break;

  case 17: /* varDeclarationInit: varDeclarationId  */
#line 118 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1838 "parser.tab.c"
    break;

  case 18: /* varDeclarationInit: varDeclarationId COLON simpleExp  */
#line 119 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->child[0] = (yyvsp[0].node);}
#line 1844 "parser.tab.c"
    break;

  case 19: /* varDeclarationInit: error COLON simpleExp  */
#line 120 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 1850 "parser.tab.c"
    break;

  case 20: /* varDeclarationId: ID  */
#line 124 "parser.y"
                                                                 { (yyval.node) = newDeclNode(VarK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                 }
#line 1858 "parser.tab.c"
    break;

  case 21: /* varDeclarationId: ID OBRACKET NUMCONST CBRACKET  */
#line 128 "parser.y"
                                                                 { (yyval.node) = newDeclNode(VarK, (yyvsp[-3].tokenData));       
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->arraySize = (yyvsp[-1].tokenData)->nvalue;
                                                                   (yyval.node)->thisTokenData = (yyvsp[-3].tokenData); 
                                                                   (yyval.node)->expType = UndefinedType;
                                                                 }
#line 1870 "parser.tab.c"
    break;

  case 22: /* varDeclarationId: ID OBRACKET error  */
#line 135 "parser.y"
                                                               { (yyval.node) = NULL;}
#line 1876 "parser.tab.c"
    break;

  case 23: /* varDeclarationId: error CBRACKET  */
#line 136 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 1882 "parser.tab.c"
    break;

  case 24: /* typespec: INT  */
#line 139 "parser.y"
                                                              { (yyval.type) = Integer; }
#line 1888 "parser.tab.c"
    break;

  case 25: /* typespec: CHAR  */
#line 140 "parser.y"
                                                                 { (yyval.type) = Char; }
#line 1894 "parser.tab.c"
    break;

  case 26: /* typespec: BOOL  */
#line 141 "parser.y"
                                                                 { (yyval.type) = Boolean;}
#line 1900 "parser.tab.c"
    break;

  case 27: /* funDeclaration: typespec ID OPAREN parameters CPAREN compoundstatement  */
#line 149 "parser.y"
                                                                 { (yyval.node) = newDeclNode(FuncK, (yyvsp[-4].tokenData));     
                                                                   (yyval.node)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->expType = (yyvsp[-5].type);
                                                                 }
#line 1911 "parser.tab.c"
    break;

  case 28: /* funDeclaration: ID OPAREN parameters CPAREN compoundstatement  */
#line 156 "parser.y"
                                                                 { (yyval.node) = newDeclNode(FuncK, (yyvsp[-4].tokenData));   
                                                                   (yyval.node)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 1921 "parser.tab.c"
    break;

  case 29: /* funDeclaration: typespec error  */
#line 161 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1927 "parser.tab.c"
    break;

  case 30: /* funDeclaration: typespec ID OPAREN error  */
#line 162 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1933 "parser.tab.c"
    break;

  case 31: /* funDeclaration: ID OPAREN error  */
#line 163 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1939 "parser.tab.c"
    break;

  case 32: /* funDeclaration: ID OPAREN parameters CPAREN error  */
#line 164 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1945 "parser.tab.c"
    break;

  case 33: /* parameters: parameterList  */
#line 167 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1951 "parser.tab.c"
    break;

  case 34: /* parameters: %empty  */
#line 168 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 1957 "parser.tab.c"
    break;

  case 35: /* parameterList: parameterList SEMICOLON parameterTypeList  */
#line 173 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1963 "parser.tab.c"
    break;

  case 36: /* parameterList: parameterTypeList  */
#line 174 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1969 "parser.tab.c"
    break;

  case 37: /* parameterList: parameterList SEMICOLON error  */
#line 175 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1975 "parser.tab.c"
    break;

  case 38: /* parameterList: error  */
#line 176 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1981 "parser.tab.c"
    break;

  case 39: /* parameterTypeList: typespec parameterIdList  */
#line 180 "parser.y"
                                                              { (yyval.node) = (yyvsp[0].node); setType((yyval.node), (yyvsp[-1].type)); }
#line 1987 "parser.tab.c"
    break;

  case 40: /* parameterTypeList: typespec error  */
#line 181 "parser.y"
                                                              { (yyval.node) = NULL;}
#line 1993 "parser.tab.c"
    break;

  case 41: /* parameterIdList: parameterIdList COMMA parameterId  */
#line 185 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok; }
#line 1999 "parser.tab.c"
    break;

  case 42: /* parameterIdList: parameterId  */
#line 186 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2005 "parser.tab.c"
    break;

  case 43: /* parameterIdList: parameterIdList COMMA error  */
#line 187 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2011 "parser.tab.c"
    break;

  case 44: /* parameterIdList: error  */
#line 188 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2017 "parser.tab.c"
    break;

  case 45: /* parameterId: ID  */
#line 191 "parser.y"
                                                                 { (yyval.node) = newDeclNode(ParamK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr; 
                                                                 }
#line 2025 "parser.tab.c"
    break;

  case 46: /* parameterId: ID OBRACKET CBRACKET  */
#line 194 "parser.y"
                                                                 { (yyval.node) = newDeclNode(ParamK, (yyvsp[-2].tokenData));
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr; 
                                                                 }
#line 2034 "parser.tab.c"
    break;

  case 47: /* statement: matched  */
#line 200 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2040 "parser.tab.c"
    break;

  case 48: /* statement: unmatched  */
#line 201 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2046 "parser.tab.c"
    break;

  case 49: /* matched: statementEnd  */
#line 204 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2052 "parser.tab.c"
    break;

  case 50: /* matched: IF simpleExp THEN matched ELSE matched  */
#line 205 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                 }
#line 2062 "parser.tab.c"
    break;

  case 51: /* matched: WHILE simpleExp DO matched  */
#line 210 "parser.y"
                                                                 { (yyval.node) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2072 "parser.tab.c"
    break;

  case 52: /* matched: FOR ID ASGN iterRange DO matched  */
#line 215 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                   (yyval.node)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                   (yyval.node)->child[0]->expType = Integer;
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                   
                                                                 }
#line 2085 "parser.tab.c"
    break;

  case 53: /* matched: IF error  */
#line 223 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2091 "parser.tab.c"
    break;

  case 54: /* matched: IF error ELSE matched  */
#line 224 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2097 "parser.tab.c"
    break;

  case 55: /* matched: IF error THEN matched ELSE matched  */
#line 225 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2103 "parser.tab.c"
    break;

  case 56: /* matched: WHILE error DO matched  */
#line 226 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2109 "parser.tab.c"
    break;

  case 57: /* matched: WHILE error  */
#line 227 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2115 "parser.tab.c"
    break;

  case 58: /* matched: FOR ID ASGN error DO matched  */
#line 228 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2121 "parser.tab.c"
    break;

  case 59: /* matched: FOR error  */
#line 229 "parser.y"
                                                                { (yyval.node) = NULL; }
#line 2127 "parser.tab.c"
    break;

  case 60: /* unmatched: IF simpleExp THEN matched ELSE unmatched  */
#line 232 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node); 
                                                                 }
#line 2137 "parser.tab.c"
    break;

  case 61: /* unmatched: IF simpleExp THEN statement  */
#line 237 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-3].tokenData));              
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node); 
                                                                 }
#line 2146 "parser.tab.c"
    break;

  case 62: /* unmatched: WHILE simpleExp DO unmatched  */
#line 241 "parser.y"
                                                                 { (yyval.node) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2156 "parser.tab.c"
    break;

  case 63: /* unmatched: FOR ID ASGN iterRange DO unmatched  */
#line 246 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                   (yyval.node)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                   (yyval.node)->child[0]->expType = Integer;
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                   
                                                                 }
#line 2169 "parser.tab.c"
    break;

  case 64: /* unmatched: IF error THEN statement  */
#line 254 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2175 "parser.tab.c"
    break;

  case 65: /* unmatched: IF error THEN matched ELSE unmatched  */
#line 255 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2181 "parser.tab.c"
    break;

  case 66: /* expstatement: exp SEMICOLON  */
#line 258 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2187 "parser.tab.c"
    break;

  case 67: /* expstatement: SEMICOLON  */
#line 259 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2193 "parser.tab.c"
    break;

  case 68: /* expstatement: error SEMICOLON  */
#line 260 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2199 "parser.tab.c"
    break;

  case 69: /* statementEnd: expstatement  */
#line 263 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2205 "parser.tab.c"
    break;

  case 70: /* statementEnd: compoundstatement  */
#line 264 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2211 "parser.tab.c"
    break;

  case 71: /* statementEnd: breakstatement  */
#line 265 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2217 "parser.tab.c"
    break;

  case 72: /* statementEnd: returnstatement  */
#line 266 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2223 "parser.tab.c"
    break;

  case 73: /* compoundstatement: BEGN localdeclaration statementList FINISH  */
#line 271 "parser.y"
                                                                 { (yyval.node) = newStmtNode(CompoundK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-1].node);
                                                                   yyerrok;
                                                                 }
#line 2233 "parser.tab.c"
    break;

  case 74: /* localdeclaration: localdeclaration scopedtypespecificer  */
#line 279 "parser.y"
                                                              { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2239 "parser.tab.c"
    break;

  case 75: /* localdeclaration: %empty  */
#line 280 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2245 "parser.tab.c"
    break;

  case 76: /* statementList: statementList statement  */
#line 283 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2251 "parser.tab.c"
    break;

  case 77: /* statementList: %empty  */
#line 284 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2257 "parser.tab.c"
    break;

  case 78: /* iterRange: simpleExp TO simpleExp  */
#line 287 "parser.y"
                                                                 { (yyval.node) = newStmtNode(RangeK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2266 "parser.tab.c"
    break;

  case 79: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 291 "parser.y"
                                                                 { (yyval.node) = newStmtNode(RangeK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                 }
#line 2276 "parser.tab.c"
    break;

  case 80: /* iterRange: simpleExp TO error  */
#line 296 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2282 "parser.tab.c"
    break;

  case 81: /* iterRange: error BY error  */
#line 297 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2288 "parser.tab.c"
    break;

  case 82: /* iterRange: simpleExp TO simpleExp BY error  */
#line 298 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2294 "parser.tab.c"
    break;

  case 83: /* returnstatement: RETURN SEMICOLON  */
#line 301 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ReturnK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                 }
#line 2302 "parser.tab.c"
    break;

  case 84: /* returnstatement: RETURN exp SEMICOLON  */
#line 304 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ReturnK, (yyvsp[-2].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = (yyvsp[-1].node)->expType;
                                                                   yyerrok;
                                                                 }
#line 2313 "parser.tab.c"
    break;

  case 85: /* returnstatement: RETURN error SEMICOLON  */
#line 310 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2319 "parser.tab.c"
    break;

  case 86: /* breakstatement: BREAK SEMICOLON  */
#line 314 "parser.y"
                                                                 { (yyval.node) = newStmtNode(BreakK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                 }
#line 2327 "parser.tab.c"
    break;

  case 87: /* asgnop: ASGN  */
#line 319 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2336 "parser.tab.c"
    break;

  case 88: /* asgnop: ADDASGN  */
#line 323 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2345 "parser.tab.c"
    break;

  case 89: /* asgnop: SUBASS  */
#line 327 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2354 "parser.tab.c"
    break;

  case 90: /* asgnop: MULASS  */
#line 331 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2363 "parser.tab.c"
    break;

  case 91: /* asgnop: DIVASS  */
#line 335 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2372 "parser.tab.c"
    break;

  case 92: /* exp: mutable asgnop exp  */
#line 341 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2381 "parser.tab.c"
    break;

  case 93: /* exp: simpleExp  */
#line 346 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2387 "parser.tab.c"
    break;

  case 94: /* exp: mutable INC  */
#line 348 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2397 "parser.tab.c"
    break;

  case 95: /* exp: mutable DEC  */
#line 353 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2407 "parser.tab.c"
    break;

  case 96: /* exp: error asgnop exp  */
#line 358 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2413 "parser.tab.c"
    break;

  case 97: /* exp: mutable asgnop error  */
#line 359 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2419 "parser.tab.c"
    break;

  case 98: /* exp: error INC  */
#line 360 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2425 "parser.tab.c"
    break;

  case 99: /* exp: error DEC  */
#line 361 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2431 "parser.tab.c"
    break;

  case 100: /* simpleExp: simpleExp OR andExp  */
#line 364 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2442 "parser.tab.c"
    break;

  case 101: /* simpleExp: andExp  */
#line 370 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2448 "parser.tab.c"
    break;

  case 102: /* simpleExp: simpleExp OR error  */
#line 371 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2454 "parser.tab.c"
    break;

  case 103: /* andExp: andExp AND unaryRelExp  */
#line 374 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2465 "parser.tab.c"
    break;

  case 104: /* andExp: unaryRelExp  */
#line 380 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2471 "parser.tab.c"
    break;

  case 105: /* andExp: andExp AND error  */
#line 381 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2477 "parser.tab.c"
    break;

  case 106: /* relExp: sumExp operator sumExp  */
#line 384 "parser.y"
                                                                    { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2486 "parser.tab.c"
    break;

  case 107: /* relExp: sumExp operator error  */
#line 388 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2492 "parser.tab.c"
    break;

  case 108: /* relExp: sumExp  */
#line 389 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2498 "parser.tab.c"
    break;

  case 109: /* unaryRelExp: NOT unaryRelExp  */
#line 392 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2508 "parser.tab.c"
    break;

  case 110: /* unaryRelExp: relExp  */
#line 397 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2514 "parser.tab.c"
    break;

  case 111: /* unaryRelExp: NOT error  */
#line 398 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2520 "parser.tab.c"
    break;

  case 112: /* operator: GREAT  */
#line 401 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2529 "parser.tab.c"
    break;

  case 113: /* operator: GEQ  */
#line 405 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2538 "parser.tab.c"
    break;

  case 114: /* operator: LESS  */
#line 410 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2547 "parser.tab.c"
    break;

  case 115: /* operator: LEQ  */
#line 414 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2556 "parser.tab.c"
    break;

  case 116: /* operator: EQUAL  */
#line 419 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2565 "parser.tab.c"
    break;

  case 117: /* operator: NEQ  */
#line 423 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2574 "parser.tab.c"
    break;

  case 118: /* sumExp: sumExp sumop mulExp  */
#line 429 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2583 "parser.tab.c"
    break;

  case 119: /* sumExp: mulExp  */
#line 433 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2589 "parser.tab.c"
    break;

  case 120: /* sumExp: sumExp sumop error  */
#line 434 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2595 "parser.tab.c"
    break;

  case 121: /* sumop: PLUS  */
#line 437 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2604 "parser.tab.c"
    break;

  case 122: /* sumop: MINUS  */
#line 441 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2613 "parser.tab.c"
    break;

  case 123: /* mulExp: mulExp mulop unaryExp  */
#line 447 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2622 "parser.tab.c"
    break;

  case 124: /* mulExp: unaryExp  */
#line 451 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2628 "parser.tab.c"
    break;

  case 125: /* mulExp: mulExp mulop error  */
#line 452 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2634 "parser.tab.c"
    break;

  case 126: /* mulop: MULT  */
#line 455 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2643 "parser.tab.c"
    break;

  case 127: /* mulop: DIV  */
#line 459 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2652 "parser.tab.c"
    break;

  case 128: /* mulop: MOD  */
#line 463 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2661 "parser.tab.c"
    break;

  case 129: /* unaryExp: unaryop unaryExp  */
#line 469 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[0].node);
                                                                 }
#line 2669 "parser.tab.c"
    break;

  case 130: /* unaryExp: factor  */
#line 472 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2675 "parser.tab.c"
    break;

  case 131: /* unaryExp: unaryop error  */
#line 473 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2681 "parser.tab.c"
    break;

  case 132: /* unaryop: MINUS  */
#line 476 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2690 "parser.tab.c"
    break;

  case 133: /* unaryop: MULT  */
#line 480 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2699 "parser.tab.c"
    break;

  case 134: /* unaryop: QUESTION  */
#line 484 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2708 "parser.tab.c"
    break;

  case 135: /* mutable: ID  */
#line 490 "parser.y"
                                                                 { (yyval.node) = newExpNode(IdK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;    
                                                                 }
#line 2716 "parser.tab.c"
    break;

  case 136: /* mutable: ID OBRACKET exp CBRACKET  */
#line 493 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-2].tokenData));  
                                                                  (yyval.node)->child[0] = newExpNode(IdK, (yyvsp[-3].tokenData));
                                                                  (yyval.node)->child[0]->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.node)->child[0]->isArray = true;
                                                                  (yyval.node)->child[1] = (yyvsp[-1].node); 
                                                                  (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                 }
#line 2728 "parser.tab.c"
    break;

  case 137: /* immutable: OPAREN exp CPAREN  */
#line 502 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); yyerrok; }
#line 2734 "parser.tab.c"
    break;

  case 138: /* immutable: call  */
#line 503 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2740 "parser.tab.c"
    break;

  case 139: /* immutable: constant  */
#line 504 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2746 "parser.tab.c"
    break;

  case 140: /* immutable: OPAREN error  */
#line 505 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2752 "parser.tab.c"
    break;

  case 141: /* factor: mutable  */
#line 508 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2758 "parser.tab.c"
    break;

  case 142: /* factor: immutable  */
#line 509 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2764 "parser.tab.c"
    break;

  case 143: /* call: ID OPAREN args CPAREN  */
#line 513 "parser.y"
                                                                 { (yyval.node) = newExpNode(CallK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2773 "parser.tab.c"
    break;

  case 144: /* call: error OPAREN  */
#line 517 "parser.y"
                                                               { (yyval.node) = NULL; yyerrok; }
#line 2779 "parser.tab.c"
    break;

  case 145: /* args: argList  */
#line 520 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2785 "parser.tab.c"
    break;

  case 146: /* args: %empty  */
#line 521 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2791 "parser.tab.c"
    break;

  case 147: /* argList: argList COMMA exp  */
#line 524 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok; }
#line 2797 "parser.tab.c"
    break;

  case 148: /* argList: exp  */
#line 525 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2803 "parser.tab.c"
    break;

  case 149: /* argList: argList COMMA error  */
#line 526 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2809 "parser.tab.c"
    break;

  case 150: /* constant: NUMCONST  */
#line 528 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.value = (yyvsp[0].tokenData)->nvalue; 
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2818 "parser.tab.c"
    break;

  case 151: /* constant: CHARCONST  */
#line 532 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->thisTokenData = (yyvsp[0].tokenData); 
                                                                   (yyval.node)->expType = Char;
                                                                 }
#line 2828 "parser.tab.c"
    break;

  case 152: /* constant: BOOLCONST  */
#line 537 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.value = (yyvsp[0].tokenData)->nvalue; 
                                                                   (yyval.node)->expType = Boolean;
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2839 "parser.tab.c"
    break;

  case 153: /* constant: STRINGCONST  */
#line 543 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.string = (yyvsp[0].tokenData)->stringvalue;
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->expType = CharInt;
                                                                   (yyval.node)->arraySize = (yyvsp[0].tokenData)->strlength;
                                                                 }
#line 2850 "parser.tab.c"
    break;


#line 2854 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 550 "parser.y"


extern int yydebug;
int main(int argc, char *argv[])
{
  int compilerFlag = 0;
  bool isPrintingAST = 0;
  numErrors = 0;
  numWarnings = 0;
  bool isGeneratingCode = true;
  int optionNumber; 
  extern int optind; 

  while((compilerFlag = getopt(argc, argv, "dDpPhM")) != -1)
  {

    switch(compilerFlag)
    {

        case 'p':
            {
              isPrintingAST = true;
              isPrintingTreeTypes = false;
              isGeneratingCode = false;
              optionNumber = 0; 
            }
            break;
    
        case 'P':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
                isGeneratingCode = false;
                optionNumber = 1;
              }
              break;

        case 'd':
              {
                yydebug = 1;
              }
              break;           
        
        case 'D':
              {
                symbolTable.debug(1);
              }  
              break;

        case 'M':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
                isPrintingMemoryOffset = true;
                isPrintingMemorySize = true;
                isOnlyPrintingMemoryInfo = true;
                isGeneratingCode = false;
                optionNumber = 1;
              }
              break; 

        case 'h':
              {
                std::cout << "usage: c- [options] [sourcefile]" << std::endl;
                std::cout << "options:" << std::endl;
                std::cout << "-d     - turn on parser debugging" << std::endl;
                std::cout << "-D     - turn on symbol table debugging" << std::endl;
                std::cout << "-h     - print this usage message" << std::endl;
                std::cout << "-p     - print the abstract syntax tree" << std::endl;
                std::cout << "-P     - print the abstract syntax tree plus type information" << std::endl;
                std::cout << "-M     - print the abstract syntax tree plus type information and memory offsets" << std::endl;
              }
              break;

        default:
              {
                exit(1);
              }
    }
  }

  if(isGeneratingCode)
  {
    isOnlyPrintingMemoryInfo = false;
    isPrintingTreeTypes = true;
    isPrintingMemorySize = true;
    optionNumber = 1;
  }
  
  std::string fileName = argv[argc-1];
  
  if(argc >1 && !(yyin = fopen(fileName.c_str(), "r")))
  {
    // failed to open file
    std::cout << "ERROR(ARGLIST): source file \"" << argv[1] << "\" could not be opened." << std::endl;
    numErrors++;
    std::cout << "Number of warnings: " << numWarnings << std::endl;
    std::cout << "Number of errors: " << numErrors << std::endl;
    exit(1);
  }

  initErrorProcessing(); 

  // remove line 623 before submission. Just For testing
  /* std::cout << "====================================" << std::endl; */

  yyparse();

  if(isPrintingAST && !isPrintingTreeTypes && numErrors == 0 && ROOT != NULL && optionNumber == 0)
  {
    printAST(ROOT, 0, isPrintingTreeTypes);
  }
  else if(isPrintingAST && isPrintingTreeTypes && numErrors == 0 && ROOT != NULL && optionNumber == 1)
  {
    initializeIO();
    
    semanticAnalysis(ROOT, numErrors, numWarnings);

    if(numErrors < 1 && isOnlyPrintingMemoryInfo)
    {  
      printAST(ROOT, 0, isPrintingTreeTypes);
    }
  }

  //code generation
  if(numErrors == 0) // if there are no errors
  {
    if(isGeneratingCode)
    {
        char* tmOutputFile = (char*)malloc(strlen(argv[optind]) + 1);
        int tmOutputFileLength = strlen(argv[optind]);

        strcpy(tmOutputFile, argv[optind]);
        tmOutputFile[tmOutputFileLength - 2] = 't';
        tmOutputFile[tmOutputFileLength - 1] = 'm';
        generateCode(ROOT, tmOutputFile);
    }

  }

  
  // remove line 644 before submission. Just For testing
  /* std::cout << "FILE: " << fileName.substr(fileName.find_last_of("/\\") + 1) << std::endl; */
  if(isPrintingMemoryOffset)
  {
    // print memory offsets
    std:: cout << "Offset for end of global space: " << globalOffset << std::endl;
  }
  std::cout << "Number of warnings: " << numWarnings << std::endl;
  std::cout << "Number of errors: " << numErrors << std::endl;

  return 0;
}
