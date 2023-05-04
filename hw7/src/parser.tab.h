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
    CHARCONST = 260,               /* CHARCONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    ASGN = 262,                    /* ASGN  */
    ADDASGN = 263,                 /* ADDASGN  */
    SUBASS = 264,                  /* SUBASS  */
    INC = 265,                     /* INC  */
    DEC = 266,                     /* DEC  */
    GEQ = 267,                     /* GEQ  */
    LEQ = 268,                     /* LEQ  */
    NEQ = 269,                     /* NEQ  */
    MULASS = 270,                  /* MULASS  */
    DIVASS = 271,                  /* DIVASS  */
    INT = 272,                     /* INT  */
    IF = 273,                      /* IF  */
    OR = 274,                      /* OR  */
    NOT = 275,                     /* NOT  */
    BY = 276,                      /* BY  */
    ELSE = 277,                    /* ELSE  */
    THEN = 278,                    /* THEN  */
    FOR = 279,                     /* FOR  */
    BREAK = 280,                   /* BREAK  */
    RETURN = 281,                  /* RETURN  */
    BOOL = 282,                    /* BOOL  */
    CHAR = 283,                    /* CHAR  */
    STATIC = 284,                  /* STATIC  */
    AND = 285,                     /* AND  */
    BEGN = 286,                    /* BEGN  */
    FINISH = 287,                  /* FINISH  */
    DO = 288,                      /* DO  */
    WHILE = 289,                   /* WHILE  */
    TO = 290,                      /* TO  */
    BOOLCONST = 291,               /* BOOLCONST  */
    QUESTION = 292,                /* QUESTION  */
    LESS = 293,                    /* LESS  */
    GREAT = 294,                   /* GREAT  */
    PLUS = 295,                    /* PLUS  */
    EQUAL = 296,                   /* EQUAL  */
    MULT = 297,                    /* MULT  */
    DIV = 298,                     /* DIV  */
    MOD = 299,                     /* MOD  */
    COMMA = 300,                   /* COMMA  */
    OBRACKET = 301,                /* OBRACKET  */
    CBRACKET = 302,                /* CBRACKET  */
    MINUS = 303,                   /* MINUS  */
    COLON = 304,                   /* COLON  */
    SEMICOLON = 305,               /* SEMICOLON  */
    OPAREN = 306,                  /* OPAREN  */
    CPAREN = 307                   /* CPAREN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "parser.y"

  ExpType type;           
  TokenData* tokenData; 
  TreeNode* node;        

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
