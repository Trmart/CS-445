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
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/


#include "scanType.hpp"
#include "AST.hpp"
#include "EmitDiagnostics.hpp"
#include "CompilerFlags.hpp"
#include "Semantics.hpp"
#include "symbolTable.hpp"
#include "IOinit.hpp"

#include <iostream>
#include <string>

// From yacc
extern int yylex();
extern int yydebug;
extern FILE *yyin;

// From c-.l scanner
extern int lineCount;
extern int errorCount;

// AST
Node* root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << lineCount + 1 << "): " << msg << std::endl;
    errorCount++;
}


#line 117 "parser.tab.c"

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
  YYSYMBOL_NUMCONST = 3,                   /* NUMCONST  */
  YYSYMBOL_BOOLCONST = 4,                  /* BOOLCONST  */
  YYSYMBOL_CHARCONST = 5,                  /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 6,                /* STRINGCONST  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_BOOL = 9,                       /* BOOL  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_STATIC = 11,                    /* STATIC  */
  YYSYMBOL_ASGN = 12,                      /* ASGN  */
  YYSYMBOL_ADDASGN = 13,                   /* ADDASGN  */
  YYSYMBOL_SUBASGN = 14,                   /* SUBASGN  */
  YYSYMBOL_MULASGN = 15,                   /* MULASGN  */
  YYSYMBOL_DIVASGN = 16,                   /* DIVASGN  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_TO = 22,                        /* TO  */
  YYSYMBOL_BY = 23,                        /* BY  */
  YYSYMBOL_DO = 24,                        /* DO  */
  YYSYMBOL_COLON = 25,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_ADD = 33,                       /* ADD  */
  YYSYMBOL_SUB = 34,                       /* SUB  */
  YYSYMBOL_MUL = 35,                       /* MUL  */
  YYSYMBOL_DIV = 36,                       /* DIV  */
  YYSYMBOL_MOD = 37,                       /* MOD  */
  YYSYMBOL_INC = 38,                       /* INC  */
  YYSYMBOL_DEC = 39,                       /* DEC  */
  YYSYMBOL_QUESTION = 40,                  /* QUESTION  */
  YYSYMBOL_RPAREN = 41,                    /* RPAREN  */
  YYSYMBOL_LPAREN = 42,                    /* LPAREN  */
  YYSYMBOL_RBRACK = 43,                    /* RBRACK  */
  YYSYMBOL_LBRACK = 44,                    /* LBRACK  */
  YYSYMBOL_T_BEGIN = 45,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 46,                     /* T_END  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_NEQ = 48,                       /* NEQ  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_LEQ = 50,                       /* LEQ  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_GEQ = 52,                       /* GEQ  */
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
#define YYLAST   207

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
       0,    76,    76,    82,    86,    92,    96,   102,   109,   115,
     122,   126,   132,   136,   143,   148,   158,   162,   166,   172,
     180,   189,   194,   199,   203,   209,   216,   221,   227,   232,
     240,   244,   250,   254,   260,   264,   268,   272,   276,   280,
     286,   290,   296,   304,   309,   314,   319,   324,   330,   339,
     348,   355,   366,   373,   384,   390,   399,   404,   413,   420,
     426,   433,   440,   446,   451,   456,   461,   466,   473,   481,
     487,   495,   501,   508,   514,   520,   526,   532,   538,   544,
     550,   556,   564,   570,   576,   582,   590,   596,   602,   608,
     614,   622,   627,   633,   639,   645,   653,   657,   663,   668,
     679,   683,   687,   693,   701,   706,   711,   715,   721,   727,
     734,   741
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
  "\"end of file\"", "error", "\"invalid token\"", "NUMCONST",
  "BOOLCONST", "CHARCONST", "STRINGCONST", "ID", "INT", "BOOL", "CHAR",
  "STATIC", "ASGN", "ADDASGN", "SUBASGN", "MULASGN", "DIVASGN", "IF",
  "THEN", "ELSE", "WHILE", "FOR", "TO", "BY", "DO", "COLON", "SEMICOLON",
  "COMMA", "RETURN", "BREAK", "AND", "OR", "NOT", "ADD", "SUB", "MUL",
  "DIV", "MOD", "INC", "DEC", "QUESTION", "RPAREN", "LPAREN", "RBRACK",
  "LBRACK", "T_BEGIN", "T_END", "EQ", "NEQ", "LT", "LEQ", "GT", "GEQ",
  "$accept", "program", "declList", "decl", "varDecl", "scopedVarDecl",
  "varDeclList", "varDeclInit", "varDeclId", "typeSpec", "funDecl",
  "parms", "parmList", "parmTypeList", "parmIdList", "parmId", "stmt",
  "stmtUnmatched", "stmtMatched", "expStmt", "compoundStmt", "localDecls",
  "stmtList", "selectStmtUnmatched", "selectStmtMatched",
  "iterStmtUnmatched", "iterStmtMatched", "iterRange", "returnStmt",
  "breakStmt", "exp", "assignop", "simpleExp", "andExp", "unaryRelExp",
  "relExp", "relOp", "sumExp", "sumOp", "mulExp", "mulOp", "unaryExp",
  "unaryOp", "factor", "mutable", "immutable", "call", "args", "argList",
  "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      68,   -21,  -135,  -135,  -135,    50,    68,  -135,  -135,    51,
    -135,    23,  -135,  -135,   -33,    53,  -135,    35,    62,    30,
      36,  -135,    23,    70,  -135,    75,   150,    48,    85,  -135,
      49,    23,    78,    73,    77,  -135,  -135,  -135,  -135,  -135,
       4,   150,  -135,  -135,  -135,   150,    93,    95,  -135,  -135,
     155,    67,  -135,   159,  -135,  -135,  -135,  -135,  -135,    87,
      62,  -135,  -135,  -135,    49,  -135,   150,   150,  -135,    90,
      93,    52,   150,   150,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,   159,   159,  -135,  -135,  -135,   159,  -135,  -135,
    -135,    76,  -135,  -135,    91,   106,    92,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,   150,    95,  -135,    55,    67,
    -135,    23,  -135,    75,     9,  -135,   150,  -135,  -135,    75,
      79,   150,   150,   131,  -135,   141,   114,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   115,
    -135,    83,  -135,   -11,    21,   130,  -135,   123,  -135,  -135,
    -135,    94,    94,   150,  -135,  -135,   132,  -135,  -135,   126,
     -12,    94,    94,   150,  -135,  -135,  -135,  -135,    11,   150,
      93
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    17,    18,     0,     2,     4,     5,     0,
       6,    22,     1,     3,    14,     0,    11,    12,     0,     0,
      21,    24,    22,     0,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,   108,   109,   110,   111,
      98,     0,    93,    94,    95,     0,    13,    69,    71,    73,
      75,    83,    87,     0,    92,    96,    97,   101,   102,     0,
       0,    44,    20,    23,     0,    15,   105,     0,    72,     0,
      62,    96,     0,     0,    84,    85,    80,    81,    76,    77,
      78,    79,     0,     0,    88,    89,    90,     0,    91,    29,
      26,    46,    19,   107,     0,   104,     0,   100,    63,    64,
      65,    66,    67,    60,    61,     0,    68,    70,    74,    82,
      86,     0,    43,     0,     0,   103,     0,    99,    59,     0,
       0,     0,     0,     0,    41,     0,     0,    42,    45,    30,
      31,    36,    37,    32,    34,    33,    35,    38,    39,     0,
     106,     0,     9,     0,     0,     0,    56,     0,    58,    40,
       8,     0,     0,     0,    57,    47,    31,    50,    52,     0,
       0,     0,     0,     0,    48,    49,    51,    53,    54,     0,
      55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,   146,  -135,  -135,   -60,   133,  -135,     2,
    -135,   137,  -135,   129,  -135,   101,    17,  -105,  -134,  -135,
     -25,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
     -42,  -135,   -26,    97,   -37,  -135,  -135,    88,  -135,    89,
    -135,   -47,  -135,  -135,   -44,  -135,  -135,  -135,  -135,  -135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   112,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   128,   129,   130,   131,
     132,    91,   114,   133,   134,   135,   136,   159,   137,   138,
     139,   105,    70,    47,    48,    49,    82,    50,    83,    51,
      87,    52,    53,    54,    55,    56,    57,    94,    95,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    71,     9,    69,    68,    62,    88,   151,     9,    22,
     163,    23,    36,    37,    38,    39,    40,   156,   158,    72,
      72,    11,    71,    71,    93,    96,   121,   165,   167,   122,
     123,     2,     3,     4,   169,   124,   107,   125,   126,    92,
     110,    41,    72,    42,    43,   152,    66,   157,    67,    44,
      12,    45,    72,   120,    61,   127,   164,   166,    14,   141,
      26,    71,    31,   118,    98,    99,   100,   101,   102,    27,
      71,    30,    71,    33,   140,     1,     2,     3,     4,    24,
      25,    71,    34,   147,     2,     3,     4,   111,    74,    75,
     103,   104,    59,   113,    61,   143,   144,    36,    37,    38,
      39,    40,    84,    85,    86,   142,    25,    71,    71,   150,
      25,   121,    60,   119,   122,   123,    65,    71,    71,    64,
     124,    23,   125,   126,    72,    73,    41,   160,    42,    43,
      89,    97,   115,   116,    44,   117,    45,   168,   145,    61,
     148,   149,   153,   170,    36,    37,    38,    39,    40,   154,
     162,   161,    13,    36,    37,    38,    39,    40,    35,    32,
      63,    90,    36,    37,    38,    39,    40,   146,   155,   106,
     108,     0,   109,    41,     0,    42,    43,     0,     0,     0,
       0,    44,    41,    45,    42,    43,     0,     0,    74,    75,
      44,     0,    45,    42,    43,     0,     0,     0,     0,    44,
       0,    45,    76,    77,    78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
      26,    45,     0,    45,    41,    30,    53,    18,     6,    42,
      22,    44,     3,     4,     5,     6,     7,   151,   152,    31,
      31,    42,    66,    67,    66,    67,    17,   161,   162,    20,
      21,     8,     9,    10,    23,    26,    73,    28,    29,    64,
      87,    32,    31,    34,    35,    24,    42,   152,    44,    40,
       0,    42,    31,   113,    45,    46,   161,   162,     7,   119,
      25,   105,    26,   105,    12,    13,    14,    15,    16,     7,
     114,    41,   116,     3,   116,     7,     8,     9,    10,    26,
      27,   125,     7,   125,     8,     9,    10,    11,    33,    34,
      38,    39,    44,    91,    45,   121,   122,     3,     4,     5,
       6,     7,    35,    36,    37,    26,    27,   151,   152,    26,
      27,    17,    27,   111,    20,    21,    43,   161,   162,    41,
      26,    44,    28,    29,    31,    30,    32,   153,    34,    35,
      43,    41,    41,    27,    40,    43,    42,   163,     7,    45,
      26,    26,    12,   169,     3,     4,     5,     6,     7,    26,
      24,    19,     6,     3,     4,     5,     6,     7,    25,    22,
      31,    60,     3,     4,     5,     6,     7,    26,   151,    72,
      82,    -1,    83,    32,    -1,    34,    35,    -1,    -1,    -1,
      -1,    40,    32,    42,    34,    35,    -1,    -1,    33,    34,
      40,    -1,    42,    34,    35,    -1,    -1,    -1,    -1,    40,
      -1,    42,    47,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    10,    54,    55,    56,    57,    62,
      63,    42,     0,    56,     7,    59,    60,    61,    62,    64,
      65,    66,    42,    44,    26,    27,    25,     7,    67,    68,
      41,    26,    64,     3,     7,    60,     3,     4,     5,     6,
       7,    32,    34,    35,    40,    42,    85,    86,    87,    88,
      90,    92,    94,    95,    96,    97,    98,    99,   102,    44,
      27,    45,    73,    66,    41,    43,    42,    44,    87,    83,
      85,    97,    31,    30,    33,    34,    47,    48,    49,    50,
      51,    52,    89,    91,    35,    36,    37,    93,    94,    43,
      68,    74,    73,    83,   100,   101,    83,    41,    12,    13,
      14,    15,    16,    38,    39,    84,    86,    87,    90,    92,
      94,    11,    58,    62,    75,    41,    27,    43,    83,    62,
      59,    17,    20,    21,    26,    28,    29,    46,    69,    70,
      71,    72,    73,    76,    77,    78,    79,    81,    82,    83,
      83,    59,    26,    85,    85,     7,    26,    83,    26,    26,
      26,    18,    24,    12,    26,    69,    71,    70,    71,    80,
      85,    19,    24,    22,    70,    71,    70,    71,    85,    23,
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
#line 77 "parser.y"
                        {
                            root = (yyvsp[0].node);
                        }
#line 1346 "parser.tab.c"
    break;

  case 3: /* declList: declList decl  */
#line 83 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-1].node),(yyvsp[0].node));
                        }
#line 1354 "parser.tab.c"
    break;

  case 4: /* declList: decl  */
#line 87 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1362 "parser.tab.c"
    break;

  case 5: /* decl: varDecl  */
#line 93 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1370 "parser.tab.c"
    break;

  case 6: /* decl: funDecl  */
#line 97 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1378 "parser.tab.c"
    break;

  case 7: /* varDecl: typeSpec varDeclList SEMICOLON  */
#line 103 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            setSiblingsType((yyval.node), (yyvsp[-2].type));
                        }
#line 1387 "parser.tab.c"
    break;

  case 8: /* scopedVarDecl: STATIC typeSpec varDeclList SEMICOLON  */
#line 110 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            setSiblingsType((yyval.node), (yyvsp[-2].type));
                            (yyval.node)->m_isStatic = true;
                        }
#line 1397 "parser.tab.c"
    break;

  case 9: /* scopedVarDecl: typeSpec varDeclList SEMICOLON  */
#line 116 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            setSiblingsType((yyval.node), (yyvsp[-2].type));
                        }
#line 1406 "parser.tab.c"
    break;

  case 10: /* varDeclList: varDeclList COMMA varDeclInit  */
#line 123 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 1414 "parser.tab.c"
    break;

  case 11: /* varDeclList: varDeclInit  */
#line 127 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1422 "parser.tab.c"
    break;

  case 12: /* varDeclInit: varDeclId  */
#line 133 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1430 "parser.tab.c"
    break;

  case 13: /* varDeclInit: varDeclId COLON simpleExp  */
#line 137 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node); 
                            (yyvsp[-2].node)->m_childernNodes[0] = (yyvsp[0].node);
                        }
#line 1439 "parser.tab.c"
    break;

  case 14: /* varDeclId: ID  */
#line 144 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_VARIABLE, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1448 "parser.tab.c"
    break;

  case 15: /* varDeclId: ID LBRACK NUMCONST RBRACK  */
#line 149 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_VARIABLE, (yyvsp[-3].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                            (yyval.node)->m_isArray = true;
                            (yyval.node)->m_parmType = ParmType::T_UNDEFINED;
                            (yyvsp[-3].tokenData)->m_tokenData = (yyvsp[-3].tokenData); 
                        }
#line 1460 "parser.tab.c"
    break;

  case 16: /* typeSpec: INT  */
#line 159 "parser.y"
                        {
                            (yyval.type) = ParmType::T_INTEGER;
                        }
#line 1468 "parser.tab.c"
    break;

  case 17: /* typeSpec: BOOL  */
#line 163 "parser.y"
                        {
                            (yyval.type) = ParmType::T_BOOL;
                        }
#line 1476 "parser.tab.c"
    break;

  case 18: /* typeSpec: CHAR  */
#line 167 "parser.y"
                        {
                            (yyval.type) = ParmType::T_CHAR;
                        }
#line 1484 "parser.tab.c"
    break;

  case 19: /* funDecl: typeSpec ID LPAREN parms RPAREN compoundStmt  */
#line 173 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_FUNCTION, (yyvsp[-4].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-4].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                            (yyval.node)->m_parmType = (yyvsp[-5].type);
                        }
#line 1496 "parser.tab.c"
    break;

  case 20: /* funDecl: ID LPAREN parms RPAREN compoundStmt  */
#line 181 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_FUNCTION, (yyvsp[-4].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-4].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 1507 "parser.tab.c"
    break;

  case 21: /* parms: parmList  */
#line 190 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1515 "parser.tab.c"
    break;

  case 22: /* parms: %empty  */
#line 194 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1523 "parser.tab.c"
    break;

  case 23: /* parmList: parmList SEMICOLON parmTypeList  */
#line 200 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-2].node), (yyvsp[0].node))
                        }
#line 1531 "parser.tab.c"
    break;

  case 24: /* parmList: parmTypeList  */
#line 204 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1539 "parser.tab.c"
    break;

  case 25: /* parmTypeList: typeSpec parmIdList  */
#line 210 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                            setSiblingsType((yyval.node), (yyvsp[-1].type));
                        }
#line 1548 "parser.tab.c"
    break;

  case 26: /* parmIdList: parmIdList COMMA parmId  */
#line 217 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-2].node), (yyvsp[0].node));
                            
                        }
#line 1557 "parser.tab.c"
    break;

  case 27: /* parmIdList: parmId  */
#line 222 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1565 "parser.tab.c"
    break;

  case 28: /* parmId: ID  */
#line 228 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_PARAMETER, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1574 "parser.tab.c"
    break;

  case 29: /* parmId: ID LBRACK RBRACK  */
#line 233 "parser.y"
                        {
                            (yyval.node) = newDeclNode(DeclarationType::T_PARAMETER, (yyvsp[-2].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-2].tokenData)->tokenContent;
                            (yyval.node)->m_isArray = true;
                        }
#line 1584 "parser.tab.c"
    break;

  case 30: /* stmt: stmtUnmatched  */
#line 241 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1592 "parser.tab.c"
    break;

  case 31: /* stmt: stmtMatched  */
#line 245 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1600 "parser.tab.c"
    break;

  case 32: /* stmtUnmatched: selectStmtUnmatched  */
#line 251 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1608 "parser.tab.c"
    break;

  case 33: /* stmtUnmatched: iterStmtUnmatched  */
#line 255 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1616 "parser.tab.c"
    break;

  case 34: /* stmtMatched: selectStmtMatched  */
#line 261 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1624 "parser.tab.c"
    break;

  case 35: /* stmtMatched: iterStmtMatched  */
#line 265 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1632 "parser.tab.c"
    break;

  case 36: /* stmtMatched: expStmt  */
#line 269 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1640 "parser.tab.c"
    break;

  case 37: /* stmtMatched: compoundStmt  */
#line 273 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1648 "parser.tab.c"
    break;

  case 38: /* stmtMatched: returnStmt  */
#line 277 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1656 "parser.tab.c"
    break;

  case 39: /* stmtMatched: breakStmt  */
#line 281 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1664 "parser.tab.c"
    break;

  case 40: /* expStmt: exp SEMICOLON  */
#line 287 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                        }
#line 1672 "parser.tab.c"
    break;

  case 41: /* expStmt: SEMICOLON  */
#line 291 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1680 "parser.tab.c"
    break;

  case 42: /* compoundStmt: T_BEGIN localDecls stmtList T_END  */
#line 297 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_COMPOUND, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-1].node);
                        }
#line 1690 "parser.tab.c"
    break;

  case 43: /* localDecls: localDecls scopedVarDecl  */
#line 305 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-1].node), (yyvsp[0].node));
                        }
#line 1698 "parser.tab.c"
    break;

  case 44: /* localDecls: %empty  */
#line 309 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1706 "parser.tab.c"
    break;

  case 45: /* stmtList: stmtList stmt  */
#line 315 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-1].node), (yyvsp[0].node));
                        }
#line 1714 "parser.tab.c"
    break;

  case 46: /* stmtList: %empty  */
#line 319 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 1722 "parser.tab.c"
    break;

  case 47: /* selectStmtUnmatched: IF simpleExp THEN stmt  */
#line 325 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_IF, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 1732 "parser.tab.c"
    break;

  case 48: /* selectStmtUnmatched: IF simpleExp THEN stmtMatched ELSE stmtUnmatched  */
#line 331 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_IF, (yyvsp[-5].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-4].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[2] = (yyvsp[0].node);
                        }
#line 1743 "parser.tab.c"
    break;

  case 49: /* selectStmtMatched: IF simpleExp THEN stmtMatched ELSE stmtMatched  */
#line 340 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_IF, (yyvsp[-5].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-4].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[2] = (yyvsp[0].node);
                        }
#line 1754 "parser.tab.c"
    break;

  case 50: /* iterStmtUnmatched: WHILE simpleExp DO stmtUnmatched  */
#line 349 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_WHILE, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                        }
#line 1765 "parser.tab.c"
    break;

  case 51: /* iterStmtUnmatched: FOR ID ASGN iterRange DO stmtUnmatched  */
#line 356 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_FOR, (yyvsp[-5].tokenData));
                            (yyval.node)->m_childernNodes[0] = newDeclNode(DeclarationType::T_VARIABLE, (yyvsp[-4].tokenData));
                            (yyval.node)->m_childernNodes[0]->m_parmType = ParmType::T_INTEGER; 
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[2] = (yyvsp[0].node);
                        }
#line 1778 "parser.tab.c"
    break;

  case 52: /* iterStmtMatched: WHILE simpleExp DO stmtMatched  */
#line 367 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_WHILE, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                        }
#line 1789 "parser.tab.c"
    break;

  case 53: /* iterStmtMatched: FOR ID ASGN iterRange DO stmtMatched  */
#line 374 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_FOR, (yyvsp[-5].tokenData));
                            (yyval.node)->m_childernNodes[0] = newDeclNode(DeclarationType::T_VARIABLE, (yyvsp[-4].tokenData));
                            (yyval.node)->m_childernNodes[0]->m_parmType = ParmType::T_INTEGER;
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[2] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                        }
#line 1802 "parser.tab.c"
    break;

  case 54: /* iterRange: simpleExp TO simpleExp  */
#line 385 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_RANGE, (yyvsp[-2].node));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 1812 "parser.tab.c"
    break;

  case 55: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 391 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_RANGE, (yyvsp[-4].node));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-4].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[2] = (yyvsp[0].node);
                        }
#line 1823 "parser.tab.c"
    break;

  case 56: /* returnStmt: RETURN SEMICOLON  */
#line 400 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_RETURN, (yyvsp[-1].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-1].tokenData)->tokenContent;
                        }
#line 1832 "parser.tab.c"
    break;

  case 57: /* returnStmt: RETURN exp SEMICOLON  */
#line 405 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_RETURN, (yyvsp[-2].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-2].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-1].node);
                            (yyval.node)->m_parmType = (yyvsp[-1].node)->m_parmType;
                        }
#line 1843 "parser.tab.c"
    break;

  case 58: /* breakStmt: BREAK SEMICOLON  */
#line 414 "parser.y"
                        {
                            (yyval.node) = newStmtNode(StatementType::T_BREAK, (yyvsp[-1].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-1].tokenData)->tokenContent;
                        }
#line 1852 "parser.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 421 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 1862 "parser.tab.c"
    break;

  case 60: /* exp: mutable INC  */
#line 427 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[-1].node));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-1].node);
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 1873 "parser.tab.c"
    break;

  case 61: /* exp: mutable DEC  */
#line 434 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[-1].node));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-1].node);
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 1884 "parser.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 441 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1892 "parser.tab.c"
    break;

  case 63: /* assignop: ASGN  */
#line 447 "parser.y"
                        {
                           (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[0].tokenData));
                           (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1901 "parser.tab.c"
    break;

  case 64: /* assignop: ADDASGN  */
#line 452 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1910 "parser.tab.c"
    break;

  case 65: /* assignop: SUBASGN  */
#line 457 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1919 "parser.tab.c"
    break;

  case 66: /* assignop: MULASGN  */
#line 462 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1928 "parser.tab.c"
    break;

  case 67: /* assignop: DIVASGN  */
#line 467 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_ASSIGN, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 1937 "parser.tab.c"
    break;

  case 68: /* simpleExp: simpleExp OR andExp  */
#line 474 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[-1].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-1].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 1949 "parser.tab.c"
    break;

  case 69: /* simpleExp: andExp  */
#line 482 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1957 "parser.tab.c"
    break;

  case 70: /* andExp: andExp AND unaryRelExp  */
#line 488 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[-1].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-1].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 1969 "parser.tab.c"
    break;

  case 71: /* andExp: unaryRelExp  */
#line 496 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1977 "parser.tab.c"
    break;

  case 72: /* unaryRelExp: NOT unaryRelExp  */
#line 502 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[-1].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[0].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-1].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 1988 "parser.tab.c"
    break;

  case 73: /* unaryRelExp: relExp  */
#line 509 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1996 "parser.tab.c"
    break;

  case 74: /* relExp: sumExp relOp sumExp  */
#line 515 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 2006 "parser.tab.c"
    break;

  case 75: /* relExp: sumExp  */
#line 521 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2014 "parser.tab.c"
    break;

  case 76: /* relOp: LT  */
#line 527 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2024 "parser.tab.c"
    break;

  case 77: /* relOp: LEQ  */
#line 533 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2034 "parser.tab.c"
    break;

  case 78: /* relOp: GT  */
#line 539 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2044 "parser.tab.c"
    break;

  case 79: /* relOp: GEQ  */
#line 545 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2054 "parser.tab.c"
    break;

  case 80: /* relOp: EQ  */
#line 551 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2064 "parser.tab.c"
    break;

  case 81: /* relOp: NEQ  */
#line 557 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                        }
#line 2074 "parser.tab.c"
    break;

  case 82: /* sumExp: sumExp sumOp mulExp  */
#line 565 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 2084 "parser.tab.c"
    break;

  case 83: /* sumExp: mulExp  */
#line 571 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2092 "parser.tab.c"
    break;

  case 84: /* sumOp: ADD  */
#line 577 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2102 "parser.tab.c"
    break;

  case 85: /* sumOp: SUB  */
#line 583 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2112 "parser.tab.c"
    break;

  case 86: /* mulExp: mulExp mulOp unaryExp  */
#line 591 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-2].node);
                            (yyval.node)->m_childernNodes[1] = (yyvsp[0].node);
                        }
#line 2122 "parser.tab.c"
    break;

  case 87: /* mulExp: unaryExp  */
#line 597 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2130 "parser.tab.c"
    break;

  case 88: /* mulOp: MUL  */
#line 603 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2140 "parser.tab.c"
    break;

  case 89: /* mulOp: DIV  */
#line 609 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2150 "parser.tab.c"
    break;

  case 90: /* mulOp: MOD  */
#line 615 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2160 "parser.tab.c"
    break;

  case 91: /* unaryExp: unaryOp unaryExp  */
#line 623 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->m_childernNodes[0] = (yyvsp[0].node);
                        }
#line 2169 "parser.tab.c"
    break;

  case 92: /* unaryExp: factor  */
#line 628 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2177 "parser.tab.c"
    break;

  case 93: /* unaryOp: SUB  */
#line 634 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2187 "parser.tab.c"
    break;

  case 94: /* unaryOp: MUL  */
#line 640 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2197 "parser.tab.c"
    break;

  case 95: /* unaryOp: QUESTION  */
#line 646 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2207 "parser.tab.c"
    break;

  case 96: /* factor: mutable  */
#line 654 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2215 "parser.tab.c"
    break;

  case 97: /* factor: immutable  */
#line 658 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2223 "parser.tab.c"
    break;

  case 98: /* mutable: ID  */
#line 664 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 2232 "parser.tab.c"
    break;

  case 99: /* mutable: ID LBRACK exp RBRACK  */
#line 669 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_OP, (yyvsp[-2].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[-2].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0] = newExpNode(ExpressionType::T_IDENTIFIER, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0]->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                            (yyval.node)->m_childernNodes[0]->m_isArray = true;; 
                            (yyval.node)->m_childernNodes[1] = (yyvsp[-1].node);
                        }
#line 2245 "parser.tab.c"
    break;

  case 100: /* immutable: LPAREN exp RPAREN  */
#line 680 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                        }
#line 2253 "parser.tab.c"
    break;

  case 101: /* immutable: call  */
#line 684 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2261 "parser.tab.c"
    break;

  case 102: /* immutable: constant  */
#line 688 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2269 "parser.tab.c"
    break;

  case 103: /* call: ID LPAREN args RPAREN  */
#line 694 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_CALL, (yyvsp[-3].tokenData));
                            (yyval.node)->m_childernNodes[0] = (yyvsp[-1].node);
                            (yyval.node)->nodeAttributes.name = (yyvsp[-3].tokenData)->tokenContent;
                        }
#line 2279 "parser.tab.c"
    break;

  case 104: /* args: argList  */
#line 702 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2287 "parser.tab.c"
    break;

  case 105: /* args: %empty  */
#line 706 "parser.y"
                        {
                            (yyval.node) = nullptr;
                        }
#line 2295 "parser.tab.c"
    break;

  case 106: /* argList: argList COMMA exp  */
#line 712 "parser.y"
                        {
                            (yyval.node) = addSiblingNode((yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2303 "parser.tab.c"
    break;

  case 107: /* argList: exp  */
#line 716 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 2311 "parser.tab.c"
    break;

  case 108: /* constant: NUMCONST  */
#line 722 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_CONSTANT, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.intVal = (yyvsp[0].tokenData)->numValue;
                            (yyval.node)->m_parmType = ParmType::T_INTEGER;
                        }
#line 2321 "parser.tab.c"
    break;

  case 109: /* constant: BOOLCONST  */
#line 728 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_CONSTANT, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.intVal = (yyvsp[0].tokenData)->numValue;
                            (yyval.node)->m_parmType = ParmType::T_BOOL;
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                        }
#line 2332 "parser.tab.c"
    break;

  case 110: /* constant: CHARCONST  */
#line 735 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_CONSTANT, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.name = (yyvsp[0].tokenData)->tokenContent;
                            (yyval.node)->m_parmType = ParmType::T_CHAR;
                            (yyval.node)->m_tokenData = (yyvsp[0].tokenData);
                        }
#line 2343 "parser.tab.c"
    break;

  case 111: /* constant: STRINGCONST  */
#line 742 "parser.y"
                        {
                            (yyval.node) = newExpNode(ExpressionType::T_CONSTANT, (yyvsp[0].tokenData));
                            (yyval.node)->nodeAttributes.stringVal = (yyvsp[0].tokenData)->stringValue;
                            (yyval.node)->m_parmType = ParmType::T_CHARINT;
                            (yyval.node)->m_isArray = true;
                        }
#line 2354 "parser.tab.c"
    break;


#line 2358 "parser.tab.c"

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

#line 750 "parser.y"


int main(int argc, char *argv[])
{

    //create the compiler flags object. This will parse the command line arguments
    CompilerFlags compilerFlags(argc, argv);

    //get the debug flag from the compiler flags object
    yydebug = compilerFlags.getDebugFlag();

    //get the file name from the compiler flags object
    std::string fileName = argv[argc - 1];

    //if the compiler flags object has an error, print the error and exit
    if (argc > 1 && !(yyin = fopen(fileName.c_str(), "r")))
    {
        // if failed to open file
        //print error message
        //exit with error
        throw std::runtime_error("Cannot open file: \'" + fileName + "\'");
        
        //print the number of errors and warnings
        EmitDiagnostics::Error::emitArgListError("source file \"" + fileName + "\" could not be opened. Terminating compilation."); 

        EmitDiagnostics::Warning::emitWarningCount();

        EmitDiagnostics::Error::emitErrorCount();

        exit(1);
    }

    //parse the input
    yyparse();



    //if the the -p flag was passed, print the AST
    if(compilerFlags.getPrintASTFlag() && !compilerFlags.getPrintASTWithTypesFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        //print the AST without types
        printAST(root, 0, false);
    }
    else if(compilerFlags.getPrintASTFlag() && compilerFlags.getPrintASTWithTypesFlag())
    {
        //if the root is null, throw an error
        if (root == nullptr)
        {
            throw std::runtime_error("main(): Cannot print root: nullptr");
        }

        setupIO();
        //create the semantics analyzer
        /* Semantics semanticAnalyzer = Semantics(); */
    
        //perform semantic analysis
        /* semanticAnalysis(root); */
        //semanticAnalyzer.semanticAnalysis(root);

        //code generation will eventually go here

        if(EmitDiagnostics::Error::getErrorCount() < 1)
        {
            //print the AST with types
            printAST(root, 0, true);
        }
    }


    //print the number of errors and warnings
    EmitDiagnostics::Warning::emitWarningCount();
    EmitDiagnostics::Error::emitErrorCount();

    //delete the tree root. Free the memory. 
    /* delete root; */

    //close the file sent into the c- compiler
    fclose(yyin);


    //close the file and exit with success
    return 0;
}
