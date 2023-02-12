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
HW2
Dr. Wilder
1/30/2023

FILE: parser.y
DESC: yacc parser for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#include "scanType.hpp"  // TokenData Type
#include "flags/CompilerFlags.hpp" // Compiler Flags
#include "ast/AST.hpp" // AST Node Types
#include <stdio.h>
#include <string>
#include <iostream>


// Variables for YACC
extern int yylex();
extern FILE *yyin;
extern int yydebug;

// Variables for ERR,from c-.l scanner
extern int lineNumber;         // ERR line number from the scanner!!
extern int numberOfErrors;    // ERR err count

Node *root; // AST root node

//ERROR Message Definition and Output Function
#define YYERROR_VERBOSE
void yyerror(const char *message)
{
    //Output the error message
    std::cout << "ERROR(" << lineNumber + 1 << "): " << message << std::endl;
    
    //increment the error count
    numberOfErrors++;
}


#line 118 "parser.tab.c"

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
  YYSYMBOL_STRINGCONST = 5,                /* STRINGCONST  */
  YYSYMBOL_CHARCONST = 6,                  /* CHARCONST  */
  YYSYMBOL_BOOLCONST = 7,                  /* BOOLCONST  */
  YYSYMBOL_STATIC = 8,                     /* STATIC  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_BOOL = 11,                      /* BOOL  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_BY = 14,                        /* BY  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_INC = 23,                       /* INC  */
  YYSYMBOL_DEC = 24,                       /* DEC  */
  YYSYMBOL_TO = 25,                        /* TO  */
  YYSYMBOL_LEQ = 26,                       /* LEQ  */
  YYSYMBOL_ASGN = 27,                      /* ASGN  */
  YYSYMBOL_GEQ = 28,                       /* GEQ  */
  YYSYMBOL_NEQ = 29,                       /* NEQ  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_ADDASS = 31,                    /* ADDASS  */
  YYSYMBOL_SUBASS = 32,                    /* SUBASS  */
  YYSYMBOL_MULASS = 33,                    /* MULASS  */
  YYSYMBOL_DIVASS = 34,                    /* DIVASS  */
  YYSYMBOL_LCURLY = 35,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 36,                    /* RCURLY  */
  YYSYMBOL_LPAREN = 37,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 38,                    /* RPAREN  */
  YYSYMBOL_LBRACK = 39,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 40,                    /* RBRACK  */
  YYSYMBOL_SEMICOLON = 41,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 42,                     /* COLON  */
  YYSYMBOL_QUESTION = 43,                  /* QUESTION  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_ADD = 45,                       /* ADD  */
  YYSYMBOL_SUB = 46,                       /* SUB  */
  YYSYMBOL_MUL = 47,                       /* MUL  */
  YYSYMBOL_DIV = 48,                       /* DIV  */
  YYSYMBOL_MOD = 49,                       /* MOD  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_declList = 55,                  /* declList  */
  YYSYMBOL_decl = 56,                      /* decl  */
  YYSYMBOL_varDecl = 57,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 58,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 59,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 60,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 61,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 62,                  /* typeSpec  */
  YYSYMBOL_funDecl = 63,                   /* funDecl  */
  YYSYMBOL_parms = 64,                     /* parms  */
  YYSYMBOL_parmList = 65,                  /* parmList  */
  YYSYMBOL_parmTypeList = 66,              /* parmTypeList  */
  YYSYMBOL_parmIdList = 67,                /* parmIdList  */
  YYSYMBOL_parmId = 68,                    /* parmId  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_stmtUnmatched = 70,             /* stmtUnmatched  */
  YYSYMBOL_stmtMatched = 71,               /* stmtMatched  */
  YYSYMBOL_expStmt = 72,                   /* expStmt  */
  YYSYMBOL_compoundStmt = 73,              /* compoundStmt  */
  YYSYMBOL_localDecls = 74,                /* localDecls  */
  YYSYMBOL_stmtList = 75,                  /* stmtList  */
  YYSYMBOL_selectStmtUnmatched = 76,       /* selectStmtUnmatched  */
  YYSYMBOL_selectStmtMatched = 77,         /* selectStmtMatched  */
  YYSYMBOL_iterStmtUnmatched = 78,         /* iterStmtUnmatched  */
  YYSYMBOL_iterStmtMatched = 79,           /* iterStmtMatched  */
  YYSYMBOL_iterRange = 80,                 /* iterRange  */
  YYSYMBOL_returnStmt = 81,                /* returnStmt  */
  YYSYMBOL_breakStmt = 82,                 /* breakStmt  */
  YYSYMBOL_exp = 83,                       /* exp  */
  YYSYMBOL_assignop = 84,                  /* assignop  */
  YYSYMBOL_simpleExp = 85,                 /* simpleExp  */
  YYSYMBOL_andExp = 86,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 87,               /* unaryRelExp  */
  YYSYMBOL_relExp = 88,                    /* relExp  */
  YYSYMBOL_relOp = 89,                     /* relOp  */
  YYSYMBOL_sumExp = 90,                    /* sumExp  */
  YYSYMBOL_sumOp = 91,                     /* sumOp  */
  YYSYMBOL_mulExp = 92,                    /* mulExp  */
  YYSYMBOL_mulOp = 93,                     /* mulOp  */
  YYSYMBOL_unaryExp = 94,                  /* unaryExp  */
  YYSYMBOL_unaryOp = 95,                   /* unaryOp  */
  YYSYMBOL_factor = 96,                    /* factor  */
  YYSYMBOL_mutable = 97,                   /* mutable  */
  YYSYMBOL_immutable = 98,                 /* immutable  */
  YYSYMBOL_call = 99,                      /* call  */
  YYSYMBOL_args = 100,                     /* args  */
  YYSYMBOL_argList = 101,                  /* argList  */
  YYSYMBOL_constant = 102                  /* constant  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

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
       0,    83,    83,    90,    95,   101,   105,   111,   119,   126,
     134,   139,   145,   149,   156,   160,   166,   170,   174,   180,
     186,   194,   199,   204,   209,   215,   223,   235,   241,   245,
     251,   255,   261,   265,   271,   275,   279,   283,   287,   291,
     297,   301,   307,   315,   328,   333,   346,   351,   357,   366,
     375,   381,   391,   397,   407,   413,   422,   426,   433,   439,
     445,   450,   455,   461,   465,   469,   473,   477,   483,   489,
     495,   501,   507,   512,   518,   524,   530,   534,   538,   542,
     546,   550,   556,   562,   568,   572,   578,   584,   590,   594,
     598,   604,   609,   615,   619,   623,   629,   633,   639,   643,
     652,   656,   660,   666,   673,   678,   683,   688,   694,   698,
     702,   706
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUMCONST",
  "STRINGCONST", "CHARCONST", "BOOLCONST", "STATIC", "INT", "CHAR", "BOOL",
  "FOR", "WHILE", "BY", "DO", "IF", "ELSE", "THEN", "RETURN", "BREAK",
  "AND", "OR", "INC", "DEC", "TO", "LEQ", "ASGN", "GEQ", "NEQ", "EQ",
  "ADDASS", "SUBASS", "MULASS", "DIVASS", "LCURLY", "RCURLY", "LPAREN",
  "RPAREN", "LBRACK", "RBRACK", "SEMICOLON", "COLON", "QUESTION", "COMMA",
  "ADD", "SUB", "MUL", "DIV", "MOD", "NOT", "GT", "LT", "$accept",
  "program", "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "parms", "parmList",
  "parmTypeList", "parmIdList", "parmId", "stmt", "stmtUnmatched",
  "stmtMatched", "expStmt", "compoundStmt", "localDecls", "stmtList",
  "selectStmtUnmatched", "selectStmtMatched", "iterStmtUnmatched",
  "iterStmtMatched", "iterRange", "returnStmt", "breakStmt", "exp",
  "assignop", "simpleExp", "andExp", "unaryRelExp", "relExp", "relOp",
  "sumExp", "sumOp", "mulExp", "mulOp", "unaryExp", "unaryOp", "factor",
  "mutable", "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,   -29,  -142,  -142,  -142,    46,    60,  -142,  -142,    32,
    -142,    79,  -142,  -142,   -16,    16,  -142,     8,    53,    37,
      52,  -142,    79,    69,  -142,   104,    35,    59,    64,  -142,
      81,    79,    80,    82,    85,  -142,    78,  -142,  -142,  -142,
    -142,    35,  -142,  -142,  -142,    35,    97,    99,  -142,  -142,
     153,    62,  -142,   148,  -142,  -142,  -142,  -142,  -142,    86,
      53,  -142,  -142,  -142,    81,  -142,    35,    35,    89,    97,
      68,  -142,    35,    35,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,   148,   148,  -142,  -142,  -142,   148,  -142,  -142,
    -142,    95,  -142,  -142,    96,    91,    93,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,    35,    99,  -142,    21,    62,
    -142,    79,  -142,   104,    12,  -142,    35,  -142,  -142,   104,
      20,   136,    35,    35,   143,   101,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   115,
    -142,    36,  -142,   113,    -8,    15,  -142,   116,  -142,  -142,
    -142,    35,   125,   125,  -142,   144,    61,  -142,  -142,  -142,
     141,   125,    35,   125,  -142,  -142,    -9,  -142,  -142,    35,
      97
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    18,    17,     0,     2,     4,     5,     0,
       6,    22,     1,     3,    14,     0,    11,    12,     0,     0,
      21,    24,    22,     0,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,    98,   108,   111,   110,
     109,     0,    95,    93,    94,     0,    13,    69,    71,    73,
      75,    83,    87,     0,    92,    96,    97,   101,   102,     0,
       0,    44,    20,    23,     0,    15,   105,     0,     0,    62,
      96,    72,     0,     0,    77,    79,    81,    80,    84,    85,
      78,    76,     0,     0,    88,    89,    90,     0,    91,    29,
      26,    46,    19,   107,     0,   104,     0,   100,    60,    61,
      63,    64,    65,    66,    67,     0,    68,    70,    74,    82,
      86,     0,    43,     0,     0,   103,     0,    99,    59,     0,
       0,     0,     0,     0,     0,     0,    42,    41,    45,    30,
      31,    36,    37,    32,    34,    33,    35,    38,    39,     0,
     106,     0,     9,     0,     0,     0,    56,     0,    58,    40,
       8,     0,     0,     0,    57,     0,     0,    50,    52,    47,
      31,     0,     0,     0,    51,    53,    54,    48,    49,     0,
      55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   155,  -142,  -142,   -68,   138,  -142,     3,
    -142,   142,  -142,   134,  -142,   107,    17,  -109,  -141,  -142,
     -28,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
     -37,  -142,   -26,   102,   -39,  -142,  -142,    87,  -142,    90,
    -142,   -43,  -142,  -142,   -40,  -142,  -142,  -142,  -142,  -142
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   112,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   128,   129,   130,   131,
     132,    91,   114,   133,   134,   135,   136,   155,   137,   138,
     139,   105,    69,    47,    48,    49,    82,    50,    83,    51,
      87,    52,    53,    54,    55,    56,    57,    94,    95,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    70,    62,     9,    68,   169,    71,   152,    11,     9,
      88,   158,   160,    72,    72,    36,    37,    38,    39,    40,
     165,    22,   168,    23,   121,   122,    70,    70,   123,    93,
      96,   124,   125,   153,   107,    14,    92,    72,    36,    37,
      38,    39,    40,   157,   110,   120,    12,    61,   126,    41,
      26,   141,   164,   127,   167,    42,    27,    24,    43,    44,
      25,   142,    45,     1,    25,    70,    78,    79,   118,     2,
       3,     4,    41,    33,    70,    30,    70,   150,    42,   140,
      25,    43,    44,    72,    70,    45,   162,   147,     2,     3,
       4,    98,    99,    31,   113,   100,   144,   145,    59,   101,
     102,   103,   104,   111,     2,     3,     4,    34,    60,    84,
      85,    86,    70,    70,   119,    66,    61,    67,    64,    72,
      73,    70,    65,    70,    23,   156,    89,    97,    36,    37,
      38,    39,    40,   117,   115,   116,   166,   121,   122,   143,
     151,   123,   148,   170,   124,   125,    36,    37,    38,    39,
      40,    36,    37,    38,    39,    40,   149,   154,   163,   161,
      61,    13,    41,    35,    32,    63,   127,    90,    42,   108,
     159,    43,    44,   109,   106,    45,     0,     0,     0,    74,
      41,    75,    76,    77,   146,    41,    42,     0,     0,    43,
      44,    42,     0,    45,    43,    44,     0,     0,    78,    79,
       0,     0,     0,     0,    80,    81
};

static const yytype_int16 yycheck[] =
{
      26,    41,    30,     0,    41,    14,    45,    15,    37,     6,
      53,   152,   153,    22,    22,     3,     4,     5,     6,     7,
     161,    37,   163,    39,    12,    13,    66,    67,    16,    66,
      67,    19,    20,    18,    73,     3,    64,    22,     3,     4,
       5,     6,     7,   152,    87,   113,     0,    35,    36,    37,
      42,   119,   161,    41,   163,    43,     3,    41,    46,    47,
      44,    41,    50,     3,    44,   105,    45,    46,   105,     9,
      10,    11,    37,     4,   114,    38,   116,    41,    43,   116,
      44,    46,    47,    22,   124,    50,    25,   124,     9,    10,
      11,    23,    24,    41,    91,    27,   122,   123,    39,    31,
      32,    33,    34,     8,     9,    10,    11,     3,    44,    47,
      48,    49,   152,   153,   111,    37,    35,    39,    38,    22,
      21,   161,    40,   163,    39,   151,    40,    38,     3,     4,
       5,     6,     7,    40,    38,    44,   162,    12,    13,     3,
      27,    16,    41,   169,    19,    20,     3,     4,     5,     6,
       7,     3,     4,     5,     6,     7,    41,    41,    17,    15,
      35,     6,    37,    25,    22,    31,    41,    60,    43,    82,
     153,    46,    47,    83,    72,    50,    -1,    -1,    -1,    26,
      37,    28,    29,    30,    41,    37,    43,    -1,    -1,    46,
      47,    43,    -1,    50,    46,    47,    -1,    -1,    45,    46,
      -1,    -1,    -1,    -1,    51,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     9,    10,    11,    54,    55,    56,    57,    62,
      63,    37,     0,    56,     3,    59,    60,    61,    62,    64,
      65,    66,    37,    39,    41,    44,    42,     3,    67,    68,
      38,    41,    64,     4,     3,    60,     3,     4,     5,     6,
       7,    37,    43,    46,    47,    50,    85,    86,    87,    88,
      90,    92,    94,    95,    96,    97,    98,    99,   102,    39,
      44,    35,    73,    66,    38,    40,    37,    39,    83,    85,
      97,    87,    22,    21,    26,    28,    29,    30,    45,    46,
      51,    52,    89,    91,    47,    48,    49,    93,    94,    40,
      68,    74,    73,    83,   100,   101,    83,    38,    23,    24,
      27,    31,    32,    33,    34,    84,    86,    87,    90,    92,
      94,     8,    58,    62,    75,    38,    44,    40,    83,    62,
      59,    12,    13,    16,    19,    20,    36,    41,    69,    70,
      71,    72,    73,    76,    77,    78,    79,    81,    82,    83,
      83,    59,    41,     3,    85,    85,    41,    83,    41,    41,
      41,    27,    15,    18,    41,    80,    85,    70,    71,    69,
      71,    15,    25,    17,    70,    71,    85,    70,    71,    14,
      85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      72,    72,    73,    74,    74,    75,    75,    76,    76,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    98,    99,   100,   100,   101,   101,   102,   102,
     102,   102
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     6,
       5,     1,     0,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     2,     0,     2,     0,     4,     6,     6,
       4,     6,     4,     6,     3,     5,     2,     3,     2,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     1,     1,     4,     1,     0,     3,     1,     1,     1,
       1,     1
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
  case 2: /* program: declList  */
#line 84 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                            root = (yyval.node);
                        }
#line 1347 "parser.tab.c"
    break;

  case 3: /* declList: declList decl  */
#line 91 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addSiblingNode((yyvsp[0].node));
                        }
#line 1356 "parser.tab.c"
    break;

  case 4: /* declList: decl  */
#line 96 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1364 "parser.tab.c"
    break;

  case 5: /* decl: varDecl  */
#line 102 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1372 "parser.tab.c"
    break;

  case 6: /* decl: funDecl  */
#line 106 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1380 "parser.tab.c"
    break;

  case 7: /* varDecl: typeSpec varDeclList SEMICOLON  */
#line 112 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            VariableNode *node = (VariableNode *)(yyval.node);
                            node->setVariableType((yyvsp[-2].primitiveType));
                        }
#line 1390 "parser.tab.c"
    break;

  case 8: /* scopedVarDecl: STATIC typeSpec varDeclList SEMICOLON  */
#line 120 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            VariableNode *node = (VariableNode *)(yyval.node);
                            node->setVariableType((yyvsp[-2].primitiveType));
                            node->setStaticVariable();
                        }
#line 1401 "parser.tab.c"
    break;

  case 9: /* scopedVarDecl: typeSpec varDeclList SEMICOLON  */
#line 127 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            VariableNode *node = (VariableNode *)(yyval.node);
                            node->setVariableType((yyvsp[-2].primitiveType));
                        }
#line 1411 "parser.tab.c"
    break;

  case 10: /* varDeclList: varDeclList COMMA varDeclInit  */
#line 135 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->addSiblingNode((yyvsp[0].node));
                        }
#line 1420 "parser.tab.c"
    break;

  case 11: /* varDeclList: varDeclInit  */
#line 140 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1428 "parser.tab.c"
    break;

  case 12: /* varDeclInit: varDeclId  */
#line 146 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1436 "parser.tab.c"
    break;

  case 13: /* varDeclInit: varDeclId COLON simpleExp  */
#line 150 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1445 "parser.tab.c"
    break;

  case 14: /* varDeclId: ID  */
#line 157 "parser.y"
                        {
                            (yyval.node) = new VariableNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::VOID));
                        }
#line 1453 "parser.tab.c"
    break;

  case 15: /* varDeclId: ID LBRACK NUMCONST RBRACK  */
#line 161 "parser.y"
                        {
                            (yyval.node) = new VariableNode((yyvsp[-3].tokenData)->tokenLineNumber, (yyvsp[-3].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::VOID, true));
                        }
#line 1461 "parser.tab.c"
    break;

  case 16: /* typeSpec: INT  */
#line 167 "parser.y"
                        {
                            (yyval.primitiveType) = PrimitiveType::Type::INT;
                        }
#line 1469 "parser.tab.c"
    break;

  case 17: /* typeSpec: BOOL  */
#line 171 "parser.y"
                        {
                            (yyval.primitiveType) = PrimitiveType::Type::BOOL;
                        }
#line 1477 "parser.tab.c"
    break;

  case 18: /* typeSpec: CHAR  */
#line 175 "parser.y"
                        {
                            (yyval.primitiveType) = PrimitiveType::Type::CHAR;
                        }
#line 1485 "parser.tab.c"
    break;

  case 19: /* funDecl: typeSpec ID LPAREN parms RPAREN compoundStmt  */
#line 181 "parser.y"
                        {
                            (yyval.node) = new FunctionNode((yyvsp[-4].tokenData)->tokenLineNumber, (yyvsp[-4].tokenData)->tokenInformation, new PrimitiveType((yyvsp[-5].primitiveType)));
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1495 "parser.tab.c"
    break;

  case 20: /* funDecl: ID LPAREN parms RPAREN compoundStmt  */
#line 187 "parser.y"
                        {
                            (yyval.node) = new FunctionNode((yyvsp[-4].tokenData)->tokenLineNumber, (yyvsp[-4].tokenData)->tokenInformation,new PrimitiveType(PrimitiveType::Type::VOID));
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1505 "parser.tab.c"
    break;

  case 21: /* parms: parmList  */
#line 195 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1513 "parser.tab.c"
    break;

  case 22: /* parms: %empty  */
#line 199 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1521 "parser.tab.c"
    break;

  case 23: /* parmList: parmList SEMICOLON parmTypeList  */
#line 205 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->addSiblingNode((yyvsp[0].node));
                        }
#line 1530 "parser.tab.c"
    break;

  case 24: /* parmList: parmTypeList  */
#line 210 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1538 "parser.tab.c"
    break;

  case 25: /* parmTypeList: typeSpec parmIdList  */
#line 216 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                            ParameterNode *node = (ParameterNode *)(yyval.node);
                            node->setParameterType((yyvsp[-1].primitiveType));
                        }
#line 1548 "parser.tab.c"
    break;

  case 26: /* parmIdList: parmIdList COMMA parmId  */
#line 224 "parser.y"
                        {
                            if ((yyvsp[-2].node) == nullptr)
                            {
                                (yyval.node) = (yyvsp[0].node);
                            }
                            else
                            {
                                (yyval.node) = (yyvsp[-2].node);
                                (yyval.node)->addSiblingNode((yyvsp[0].node));
                            }
                        }
#line 1564 "parser.tab.c"
    break;

  case 27: /* parmIdList: parmId  */
#line 236 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1572 "parser.tab.c"
    break;

  case 28: /* parmId: ID  */
#line 242 "parser.y"
                        {
                            (yyval.node) = new ParameterNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::VOID));
                        }
#line 1580 "parser.tab.c"
    break;

  case 29: /* parmId: ID LBRACK RBRACK  */
#line 246 "parser.y"
                        {
                            (yyval.node) = new ParameterNode((yyvsp[-2].tokenData)->tokenLineNumber, (yyvsp[-2].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::VOID, true));
                        }
#line 1588 "parser.tab.c"
    break;

  case 30: /* stmt: stmtUnmatched  */
#line 252 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1596 "parser.tab.c"
    break;

  case 31: /* stmt: stmtMatched  */
#line 256 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1604 "parser.tab.c"
    break;

  case 32: /* stmtUnmatched: selectStmtUnmatched  */
#line 262 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1612 "parser.tab.c"
    break;

  case 33: /* stmtUnmatched: iterStmtUnmatched  */
#line 266 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1620 "parser.tab.c"
    break;

  case 34: /* stmtMatched: selectStmtMatched  */
#line 272 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1628 "parser.tab.c"
    break;

  case 35: /* stmtMatched: iterStmtMatched  */
#line 276 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1636 "parser.tab.c"
    break;

  case 36: /* stmtMatched: expStmt  */
#line 280 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1644 "parser.tab.c"
    break;

  case 37: /* stmtMatched: compoundStmt  */
#line 284 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1652 "parser.tab.c"
    break;

  case 38: /* stmtMatched: returnStmt  */
#line 288 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1660 "parser.tab.c"
    break;

  case 39: /* stmtMatched: breakStmt  */
#line 292 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1668 "parser.tab.c"
    break;

  case 40: /* expStmt: exp SEMICOLON  */
#line 298 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                        }
#line 1676 "parser.tab.c"
    break;

  case 41: /* expStmt: SEMICOLON  */
#line 302 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1684 "parser.tab.c"
    break;

  case 42: /* compoundStmt: LCURLY localDecls stmtList RCURLY  */
#line 308 "parser.y"
                        {
                            (yyval.node) = new CompoundNode((yyvsp[-3].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 1694 "parser.tab.c"
    break;

  case 43: /* localDecls: localDecls scopedVarDecl  */
#line 316 "parser.y"
                        {
                            if ((yyvsp[-1].node) == nullptr)
                            {
                                (yyval.node) = (yyvsp[0].node);
                            }
                            else
                            {
                                (yyval.node) = (yyvsp[-1].node);
                                (yyval.node)->addSiblingNode((yyvsp[0].node));
                            }
                        }
#line 1710 "parser.tab.c"
    break;

  case 44: /* localDecls: %empty  */
#line 328 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1718 "parser.tab.c"
    break;

  case 45: /* stmtList: stmtList stmt  */
#line 334 "parser.y"
                        {
                            if ((yyvsp[-1].node) == nullptr)
                            {
                                (yyval.node) = (yyvsp[0].node);
                            }
                            else
                            {
                                (yyval.node) = (yyvsp[-1].node);
                                (yyval.node)->addSiblingNode((yyvsp[0].node));
                            }
                        }
#line 1734 "parser.tab.c"
    break;

  case 46: /* stmtList: %empty  */
#line 346 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1742 "parser.tab.c"
    break;

  case 47: /* selectStmtUnmatched: IF simpleExp THEN stmt  */
#line 352 "parser.y"
                        {
                            (yyval.node) = new IfNode((yyvsp[-3].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1752 "parser.tab.c"
    break;

  case 48: /* selectStmtUnmatched: IF simpleExp THEN stmtMatched ELSE stmtUnmatched  */
#line 358 "parser.y"
                        {
                            (yyval.node) = new IfNode((yyvsp[-5].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-4].node));
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1763 "parser.tab.c"
    break;

  case 49: /* selectStmtMatched: IF simpleExp THEN stmtMatched ELSE stmtMatched  */
#line 367 "parser.y"
                        {
                            (yyval.node) = new IfNode((yyvsp[-5].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-4].node));
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1774 "parser.tab.c"
    break;

  case 50: /* iterStmtUnmatched: WHILE simpleExp DO stmtUnmatched  */
#line 376 "parser.y"
                        {
                            (yyval.node) = new WhileNode((yyvsp[-3].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1784 "parser.tab.c"
    break;

  case 51: /* iterStmtUnmatched: FOR ID ASGN iterRange DO stmtUnmatched  */
#line 382 "parser.y"
                        {
                            (yyval.node) = new ForNode((yyvsp[-5].tokenData)->tokenLineNumber);
                            VariableNode *node = new VariableNode((yyvsp[-4].tokenData)->tokenLineNumber, (yyvsp[-4].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::INT));
                            (yyval.node)->addChildNode(node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1796 "parser.tab.c"
    break;

  case 52: /* iterStmtMatched: WHILE simpleExp DO stmtMatched  */
#line 392 "parser.y"
                        {
                            (yyval.node) = new WhileNode((yyvsp[-3].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1806 "parser.tab.c"
    break;

  case 53: /* iterStmtMatched: FOR ID ASGN iterRange DO stmtMatched  */
#line 398 "parser.y"
                        {
                            (yyval.node) = new ForNode((yyvsp[-5].tokenData)->tokenLineNumber);
                            VariableNode *node = new VariableNode((yyvsp[-4].tokenData)->tokenLineNumber, (yyvsp[-4].tokenData)->tokenInformation, new PrimitiveType(PrimitiveType::Type::INT));
                            (yyval.node)->addChildNode(node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1818 "parser.tab.c"
    break;

  case 54: /* iterRange: simpleExp TO simpleExp  */
#line 408 "parser.y"
                        {
                            (yyval.node) = new RangeNode((yyvsp[-2].node)->getTokenLineNumber());
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1828 "parser.tab.c"
    break;

  case 55: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 414 "parser.y"
                        {
                            (yyval.node) = new RangeNode((yyvsp[-4].node)->getTokenLineNumber());
                            (yyval.node)->addChildNode((yyvsp[-4].node));
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1839 "parser.tab.c"
    break;

  case 56: /* returnStmt: RETURN SEMICOLON  */
#line 423 "parser.y"
                        {
                            (yyval.node) = new ReturnNode((yyvsp[-1].tokenData)->tokenLineNumber);
                        }
#line 1847 "parser.tab.c"
    break;

  case 57: /* returnStmt: RETURN exp SEMICOLON  */
#line 427 "parser.y"
                        {
                            (yyval.node) = new ReturnNode((yyvsp[-2].tokenData)->tokenLineNumber);
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 1856 "parser.tab.c"
    break;

  case 58: /* breakStmt: BREAK SEMICOLON  */
#line 434 "parser.y"
                        {
                            (yyval.node) = new BreakNode((yyvsp[-1].tokenData)->tokenLineNumber);
                        }
#line 1864 "parser.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 440 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1874 "parser.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 446 "parser.y"
                        {
                            (yyval.node) = new UnaryAssignmentNode((yyvsp[-1].node)->getTokenLineNumber(), UnaryAssignmentNode::Type::INC);
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 1883 "parser.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 451 "parser.y"
                        {
                            (yyval.node) = new UnaryAssignmentNode((yyvsp[-1].node)->getTokenLineNumber(), UnaryAssignmentNode::Type::DEC);
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 1892 "parser.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 456 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1900 "parser.tab.c"
    break;

  case 63: /* assignop: ASGN  */
#line 462 "parser.y"
                        {
                            (yyval.node) = new AssignmentNode((yyvsp[0].tokenData)->tokenLineNumber, AssignmentNode::Type::ASGN);
                        }
#line 1908 "parser.tab.c"
    break;

  case 64: /* assignop: ADDASS  */
#line 466 "parser.y"
                        {
                            (yyval.node) = new AssignmentNode((yyvsp[0].tokenData)->tokenLineNumber, AssignmentNode::Type::ADDASS);
                        }
#line 1916 "parser.tab.c"
    break;

  case 65: /* assignop: SUBASS  */
#line 470 "parser.y"
                        {
                            (yyval.node) = new AssignmentNode((yyvsp[0].tokenData)->tokenLineNumber, AssignmentNode::Type::SUBASS);
                        }
#line 1924 "parser.tab.c"
    break;

  case 66: /* assignop: MULASS  */
#line 474 "parser.y"
                        {
                            (yyval.node) = new AssignmentNode((yyvsp[0].tokenData)->tokenLineNumber, AssignmentNode::Type::MULASS);
                        }
#line 1932 "parser.tab.c"
    break;

  case 67: /* assignop: DIVASS  */
#line 478 "parser.y"
                        {
                            (yyval.node) = new AssignmentNode((yyvsp[0].tokenData)->tokenLineNumber, AssignmentNode::Type::DIVASS);
                        }
#line 1940 "parser.tab.c"
    break;

  case 68: /* simpleExp: simpleExp OR andExp  */
#line 484 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[-2].node)->getTokenLineNumber(), BinaryNode::Type::OR);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1950 "parser.tab.c"
    break;

  case 69: /* simpleExp: andExp  */
#line 490 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1958 "parser.tab.c"
    break;

  case 70: /* andExp: andExp AND unaryRelExp  */
#line 496 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[-2].node)->getTokenLineNumber(), BinaryNode::Type::AND);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1968 "parser.tab.c"
    break;

  case 71: /* andExp: unaryRelExp  */
#line 502 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1976 "parser.tab.c"
    break;

  case 72: /* unaryRelExp: NOT unaryRelExp  */
#line 508 "parser.y"
                        {
                            (yyval.node) = new UnaryNode((yyvsp[-1].tokenData)->tokenLineNumber, UnaryNode::Type::NOT);
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 1985 "parser.tab.c"
    break;

  case 73: /* unaryRelExp: relExp  */
#line 513 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1993 "parser.tab.c"
    break;

  case 74: /* relExp: sumExp relOp sumExp  */
#line 519 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 2003 "parser.tab.c"
    break;

  case 75: /* relExp: sumExp  */
#line 525 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2011 "parser.tab.c"
    break;

  case 76: /* relOp: LT  */
#line 531 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::LT);
                        }
#line 2019 "parser.tab.c"
    break;

  case 77: /* relOp: LEQ  */
#line 535 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::LEQ);
                        }
#line 2027 "parser.tab.c"
    break;

  case 78: /* relOp: GT  */
#line 539 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::GT);
                        }
#line 2035 "parser.tab.c"
    break;

  case 79: /* relOp: GEQ  */
#line 543 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::GEQ);
                        }
#line 2043 "parser.tab.c"
    break;

  case 80: /* relOp: EQ  */
#line 547 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::EQ);
                        }
#line 2051 "parser.tab.c"
    break;

  case 81: /* relOp: NEQ  */
#line 551 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::NEQ);
                        }
#line 2059 "parser.tab.c"
    break;

  case 82: /* sumExp: sumExp sumOp mulExp  */
#line 557 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 2069 "parser.tab.c"
    break;

  case 83: /* sumExp: mulExp  */
#line 563 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2077 "parser.tab.c"
    break;

  case 84: /* sumOp: ADD  */
#line 569 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::ADD);
                        }
#line 2085 "parser.tab.c"
    break;

  case 85: /* sumOp: SUB  */
#line 573 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::SUB);
                        }
#line 2093 "parser.tab.c"
    break;

  case 86: /* mulExp: mulExp mulOp unaryExp  */
#line 579 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addChildNode((yyvsp[-2].node));
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 2103 "parser.tab.c"
    break;

  case 87: /* mulExp: unaryExp  */
#line 585 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2111 "parser.tab.c"
    break;

  case 88: /* mulOp: MUL  */
#line 591 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::MUL);
                        }
#line 2119 "parser.tab.c"
    break;

  case 89: /* mulOp: DIV  */
#line 595 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::DIV);
                        }
#line 2127 "parser.tab.c"
    break;

  case 90: /* mulOp: MOD  */
#line 599 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[0].tokenData)->tokenLineNumber, BinaryNode::Type::MOD);
                        }
#line 2135 "parser.tab.c"
    break;

  case 91: /* unaryExp: unaryOp unaryExp  */
#line 605 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->addChildNode((yyvsp[0].node));
                        }
#line 2144 "parser.tab.c"
    break;

  case 92: /* unaryExp: factor  */
#line 610 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2152 "parser.tab.c"
    break;

  case 93: /* unaryOp: SUB  */
#line 616 "parser.y"
                        {
                            (yyval.node) = new UnaryNode((yyvsp[0].tokenData)->tokenLineNumber, UnaryNode::Type::CHSIGN);
                        }
#line 2160 "parser.tab.c"
    break;

  case 94: /* unaryOp: MUL  */
#line 620 "parser.y"
                        {
                            (yyval.node) = new UnaryNode((yyvsp[0].tokenData)->tokenLineNumber, UnaryNode::Type::SIZEOF);
                        }
#line 2168 "parser.tab.c"
    break;

  case 95: /* unaryOp: QUESTION  */
#line 624 "parser.y"
                        {
                            (yyval.node) = new UnaryNode((yyvsp[0].tokenData)->tokenLineNumber, UnaryNode::Type::QUESTION);
                        }
#line 2176 "parser.tab.c"
    break;

  case 96: /* factor: mutable  */
#line 630 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2184 "parser.tab.c"
    break;

  case 97: /* factor: immutable  */
#line 634 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2192 "parser.tab.c"
    break;

  case 98: /* mutable: ID  */
#line 640 "parser.y"
                        {
                            (yyval.node) = new IdentifierNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation);
                        }
#line 2200 "parser.tab.c"
    break;

  case 99: /* mutable: ID LBRACK exp RBRACK  */
#line 644 "parser.y"
                        {
                            (yyval.node) = new BinaryNode((yyvsp[-3].tokenData)->tokenLineNumber, BinaryNode::Type::INDEX);
                            IdentifierNode *node = new IdentifierNode((yyvsp[-3].tokenData)->tokenLineNumber, (yyvsp[-3].tokenData)->tokenInformation, true);
                            (yyval.node)->addChildNode(node);
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 2211 "parser.tab.c"
    break;

  case 100: /* immutable: LPAREN exp RPAREN  */
#line 653 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                        }
#line 2219 "parser.tab.c"
    break;

  case 101: /* immutable: call  */
#line 657 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2227 "parser.tab.c"
    break;

  case 102: /* immutable: constant  */
#line 661 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2235 "parser.tab.c"
    break;

  case 103: /* call: ID LPAREN args RPAREN  */
#line 667 "parser.y"
                        {
                            (yyval.node) = new CallNode((yyvsp[-3].tokenData)->tokenLineNumber, (yyvsp[-3].tokenData)->tokenInformation);
                            (yyval.node)->addChildNode((yyvsp[-1].node));
                        }
#line 2244 "parser.tab.c"
    break;

  case 104: /* args: argList  */
#line 674 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2252 "parser.tab.c"
    break;

  case 105: /* args: %empty  */
#line 678 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 2260 "parser.tab.c"
    break;

  case 106: /* argList: argList COMMA exp  */
#line 684 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->addSiblingNode((yyvsp[0].node));
                        }
#line 2269 "parser.tab.c"
    break;

  case 107: /* argList: exp  */
#line 689 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2277 "parser.tab.c"
    break;

  case 108: /* constant: NUMCONST  */
#line 695 "parser.y"
                        {
                            (yyval.node) = new ConstantNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, ConstantNode::Type::INT);
                        }
#line 2285 "parser.tab.c"
    break;

  case 109: /* constant: BOOLCONST  */
#line 699 "parser.y"
                        {
                            (yyval.node) = new ConstantNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, ConstantNode::Type::BOOL);
                        }
#line 2293 "parser.tab.c"
    break;

  case 110: /* constant: CHARCONST  */
#line 703 "parser.y"
                        {
                            (yyval.node) = new ConstantNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, ConstantNode::Type::CHAR);
                        }
#line 2301 "parser.tab.c"
    break;

  case 111: /* constant: STRINGCONST  */
#line 707 "parser.y"
                        {
                            (yyval.node) = new ConstantNode((yyvsp[0].tokenData)->tokenLineNumber, (yyvsp[0].tokenData)->tokenInformation, ConstantNode::Type::STRING);
                        }
#line 2309 "parser.tab.c"
    break;


#line 2313 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 711 "parser.y"



int main(int argc, char *argv[])
{
    //create the compiler flags object. This will parse the command line arguments
    CompilerFlags compilerFlags(argc, argv);

    //get the debug flag from the compiler flags object
    yydebug = compilerFlags.getDebugFlag();

    //get the file name from the compiler flags object
    std::string fileName = compilerFlags.getFile();

    //if the compiler flags object has an error, print the error and exit
    if (argc > 1) 
    {
        // if failed to open file
        if (!(yyin = fopen(fileName.c_str(), "r")))
        {
            //print error message
            std :: cout << "ERROR: failed to open \'" << fileName << "\'" << std :: endl;
            //exit with error
            exit(1);
        }
    }

    //parse the input
    yyparse();

    //if the the -p flag was passed, print the AST
    if(compilerFlags.getPrintASTFlag())
    {
        if(root != NULL)
        {
            root->printAST();
        }
    }

    //delete the tree root. Free the memory. 
    delete root;

    //close the file sent into the c- compiler
    fclose(yyin);


    //close the file and exit with success
    return 0;
}
