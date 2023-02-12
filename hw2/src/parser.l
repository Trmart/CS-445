%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: parser.l
DESC: scanner for the c- language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

// this *order* of these includes is mandatory
#include "CompilerFlags.hpp" // CompilerFlags class
#include "scanType.hpp"  // TokenData Type
#include "ast/AST.hpp"  // AST classes
#include "parser.tab.h"  // token definitions from the bison

#include <string>
#include <iostream>

// Variables for ERR
int lineNumber = 1;         // ERR line number from the scanner!!
int numberOfErrors;    // ERR err count

// this is the function that the scanner will call to set the token data
static int setValue(int linenum, int tokenClass, char *svalue)
{
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->tokenLineNumber = linenum;

    // duplicate string!!
    yylval.tokenData->tokenInformation = strdup(svalue);  
  

    return tokenClass;
}

%}

%option noyywrap

%%



"int" {return INT;}
"char" {return CHAR;}
"static" {return setValue(lineNumber, STATIC, yytext);}
"bool" {return BOOL;}

"for" {return setValue(lineNumber, FOR, yytext);}
"while" {return setValue(lineNumber, WHILE, yytext);}
"by" {return setValue(lineNumber, BY, yytext);}
"do" {return setValue(lineNumber, DO, yytext);}

"if" {return setValue(lineNumber, IF, yytext);}
"else" {return setValue(lineNumber, ELSE, yytext);}
"then" {return setValue(lineNumber, THEN, yytext);}


"return" {return setValue(lineNumber, RETURN, yytext);}
"break" {return setValue(lineNumber, BREAK, yytext);}

"and" {return setValue(lineNumber, AND, yytext);}
"or" {return setValue(lineNumber, OR, yytext);}
"true" {return setValue(lineNumber, BOOLCONST, yytext);}
"false" {return setValue(lineNumber, BOOLCONST, yytext);}

"begin" {return setValue(lineNumber, BEGIN, yytext);}
"end" {return setValue(lineNumber, END, yytext);}

"++" {return setValue(lineNumber, INC, yytext);}
"--" {return setValue(lineNumber, DEC, yytext);}
".." {return setValue(lineNumber, TO, yytext);}
"!>" {return setValue(lineNumber, LEQ, yytext);}
"<=" {return setValue(lineNumber, ASGN, yytext);}
"!<" {return setValue(lineNumber, GEQ, yytext);}
"!=" {return setValue(lineNumber, NEQ, yytext);}
"+=" {return setValue(lineNumber, ADDASS, yytext);}
"-=" {return setValue(lineNumber, SUBASS, yytext);}
"/=" {return setValue(lineNumber, DIVASS, yytext);}
"*=" {return setValue(lineNumber, MULASS, yytext);}
"==" {return setValue(lineNumber, EQ, yytext);}




"(" { return setValue(lineNumber, LPAREN, yytext); }
")" { return setValue(lineNumber, RPAREN, yytext); }
"[" { return setValue(lineNumber, LBRACK, yytext); }
"]" { return setValue(lineNumber, RBRACK, yytext); }


"+" { return setValue(lineNumber, ADD, yytext); }
"-" { return setValue(lineNumber, SUB, yytext); }
"*" { return setValue(lineNumber, MUL, yytext); }
"/" { return setValue(lineNumber, DIV, yytext); }
"%" { return setValue(lineNumber, MOD, yytext); }
"!" { return setValue(lineNumber, NOT, yytext); }
">" {return setValue(lineNumber, GT, yytext);}
"<" {return setValue(lineNumber, LT, yytext);}


";" { return setValue(lineNumber, SEMICOLON, yytext); }
":" { return setValue(lineNumber, COLON, yytext); }
"?" { return setValue(lineNumber, QUESTION, yytext); }
"," { return setValue(lineNumber, COMMA, yytext); }

[0-9]+                  { return setValue(lineNumber, NUMCONST, yytext); }
[a-zA-Z][a-zA-Z0-9]*    { return setValue(lineNumber,ID, yytext); }
\"((\\\")|[^\n"])*\"    { return setValue(lineNumber, STRINGCONST, yytext); }
\'((\\\')|[^\n'])*\'    { return setValue(lineNumber, CHARCONST, yytext); }
[ \t]                  { /* ignore white space */ }
\#\#.*\n               { /* ignore comments */ lineNumber++; }
"\n"                     { lineNumber++; }
.                      { 
                            printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", lineNumber, yytext[0]);
                            numberOfErrors++;
                       }
%%
