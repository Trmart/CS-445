/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMCONST = 258,                /* NUMCONST  */
    BOOLCONST = 259,               /* BOOLCONST  */
    CHARCONST = 260,               /* CHARCONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    ID = 262,                      /* ID  */
    INT = 263,                     /* INT  */
    BOOL = 264,                    /* BOOL  */
    CHAR = 265,                    /* CHAR  */
    STATIC = 266,                  /* STATIC  */
    ASGN = 267,                    /* ASGN  */
    ADDASGN = 268,                 /* ADDASGN  */
    SUBASGN = 269,                 /* SUBASGN  */
    MULASGN = 270,                 /* MULASGN  */
    DIVASGN = 271,                 /* DIVASGN  */
    IF = 272,                      /* IF  */
    THEN = 273,                    /* THEN  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    FOR = 276,                     /* FOR  */
    TO = 277,                      /* TO  */
    BY = 278,                      /* BY  */
    DO = 279,                      /* DO  */
    COLON = 280,                   /* COLON  */
    SEMICOLON = 281,               /* SEMICOLON  */
    COMMA = 282,                   /* COMMA  */
    RETURN = 283,                  /* RETURN  */
    BREAK = 284,                   /* BREAK  */
    AND = 285,                     /* AND  */
    OR = 286,                      /* OR  */
    NOT = 287,                     /* NOT  */
    ADD = 288,                     /* ADD  */
    SUB = 289,                     /* SUB  */
    MUL = 290,                     /* MUL  */
    DIV = 291,                     /* DIV  */
    MOD = 292,                     /* MOD  */
    INC = 293,                     /* INC  */
    DEC = 294,                     /* DEC  */
    QUESTION = 295,                /* QUESTION  */
    RPAREN = 296,                  /* RPAREN  */
    LPAREN = 297,                  /* LPAREN  */
    RBRACK = 298,                  /* RBRACK  */
    LBRACK = 299,                  /* LBRACK  */
    T_BEGIN = 300,                 /* T_BEGIN  */
    T_END = 301,                   /* T_END  */
    EQ = 302,                      /* EQ  */
    NEQ = 303,                     /* NEQ  */
    LT = 304,                      /* LT  */
    LEQ = 305,                     /* LEQ  */
    GT = 306,                      /* GT  */
    GEQ = 307                      /* GEQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 48 "parser.y"

    ParmType type;
    TokenData* tokenData;
    Node* node;

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
