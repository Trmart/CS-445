%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: c-.l
DESC: scanner for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

// this *order* of these includes is mandatory
#include "scanType.h"  // TokenData Type
#include "c-.tab.h"  // token definitions from the bison

#include <string>

// Variables for ERR
int lineNumber;         // ERR line number from the scanner!!
int numberOfErrors;    // ERR err count

static int setValue(int linenum, int tokenClass, char *svalue)
{
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string!!
  
    if (tokenClass == NUMBER) {
        yylval.tokenData->numValue = atof(svalue); 
    }
    else if (tokenClass == ID) {
        yylval.tokenData->idIndex = svalue[0]-'a';
    }

    return tokenClass;
}

%}

%option noyywrap

%%
"stop"|"quit"|"exit"   { return setValue(lineNumber, QUIT, yytext); }
"pi"                   { return setValue(lineNumber, NUMBER, (char *)"3.141592653589793238"); }
[0-9]+|[0-9]*\.[0-9]+  { return setValue(lineNumber, NUMBER, yytext); }
[0-9]+\.[0-9]*         { return setValue(lineNumber, NUMBER, yytext); }
[a-z]                  { return setValue(lineNumber, ID, yytext); }
[\=\+\-\*\/\(\)]       { return setValue(lineNumber, yytext[0], yytext ); }
[ \t]                  ;
\/\/.*                 ;
\n                     { lineNumber++; return setValue(lineNumber, yytext[0], yytext ); }
.                      { printf("ERROR(%d): char \'%c\' is not in the language\n", lineNumber, yytext[0]); numberOfErrors++; }
%%
