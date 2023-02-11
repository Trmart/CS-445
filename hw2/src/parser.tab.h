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
    ID = 258,                      /* ID  */
    NUMCONST = 259,                /* NUMCONST  */
    STRINGCONST = 260,             /* STRINGCONST  */
    CHARCONST = 261,               /* CHARCONST  */
    BOOLCONST = 262,               /* BOOLCONST  */
    STATIC = 263,                  /* STATIC  */
    INT = 264,                     /* INT  */
    CHAR = 265,                    /* CHAR  */
    BOOL = 266,                    /* BOOL  */
    FOR = 267,                     /* FOR  */
    WHILE = 268,                   /* WHILE  */
    BY = 269,                      /* BY  */
    DO = 270,                      /* DO  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    THEN = 273,                    /* THEN  */
    RETURN = 274,                  /* RETURN  */
    BREAK = 275,                   /* BREAK  */
    AND = 276,                     /* AND  */
    OR = 277,                      /* OR  */
    INC = 278,                     /* INC  */
    DEC = 279,                     /* DEC  */
    TO = 280,                      /* TO  */
    LEQ = 281,                     /* LEQ  */
    ASGN = 282,                    /* ASGN  */
    GEQ = 283,                     /* GEQ  */
    NEQ = 284,                     /* NEQ  */
    EQ = 285,                      /* EQ  */
    ADDASS = 286,                  /* ADDASS  */
    SUBASS = 287,                  /* SUBASS  */
    MULASS = 288,                  /* MULASS  */
    DIVASS = 289,                  /* DIVASS  */
    LCURLY = 290,                  /* LCURLY  */
    RCURLY = 291,                  /* RCURLY  */
    LPAREN = 292,                  /* LPAREN  */
    RPAREN = 293,                  /* RPAREN  */
    LBRACK = 294,                  /* LBRACK  */
    RBRACK = 295,                  /* RBRACK  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COLON = 297,                   /* COLON  */
    QUESTION = 298,                /* QUESTION  */
    COMMA = 299,                   /* COMMA  */
    ADD = 300,                     /* ADD  */
    SUB = 301,                     /* SUB  */
    MUL = 302,                     /* MUL  */
    DIV = 303,                     /* DIV  */
    MOD = 304,                     /* MOD  */
    NOT = 305,                     /* NOT  */
    GT = 306,                      /* GT  */
    LT = 307                       /* LT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 51 "parser.y"

    PrimitiveType::Type primitiveType;
    TokenData *tokenData;
    Node *node;

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
