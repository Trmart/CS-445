%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: parser.l
DESC: scanner for the c- language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

// this *order* of these includes is mandatory
#include "scanType.hpp"  // TokenData Type
#include "parser.tab.h"  // token definitions from the bison

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

    // duplicate string!!
    yylval.tokenData->tokenstr = strdup(svalue);  
  
    // tokenClass State Machine
    switch (tokenClass)
    {
        case ID:
            break;
        case NUMCONST:
                {
                    yylval.tokenData->numValue = stoi(yylval.tokenData->tokenInformation);
                }
                break;
        case STRINGCONST:
                    {

                    }
                    break;
        case CHARCONST:
                    { 

                    }
                    break;
        case BOOLCONST:
                    {
                        yylval.tokenData->numValue = yyval.tokenData->tokenInformation == "true";
                    }
                    break;
        case TOKEN:
                {
                    switch (yylval.tokenData->tokenInformation)
                    {
                        case '==':
                            yylval.tokenData->stringValue = "EQ";
                            break;
                        case '++':
                            yylval.tokenData->stringValue = "INC";
                            break;
                        case '--':
                            yylval.tokenData->stringValue = "DEC";
                            break;
                        case '>=':
                            yylval.tokenData->stringValue = "GEQ";
                            break;
                        case '<=':
                            yylval.tokenData->stringValue = "LEQ";
                            break;
                        case '!=':
                            yylval.tokenData->stringValue = "NEQ";
                            break;
                        case '+=':
                            yylval.tokenData->stringValue = "ADDASS";
                            break;
                        default:
                            yylval.tokenData->stringValue = yylval.tokenData->tokenInformation;
                            break;
                    }
                }
            break;
        case KEYWORD:
            break;
    }

    return tokenClass;
}

%}

%option noyywrap

%%

/*KEYWORDS*/

int|bool|char|static  { return setValue(lineNumber, KEYWORD, yytext); }

while|for|break  { return setValue(lineNumber, KEYWORD, yytext); }

if|else|begin|end|then  { return setValue(lineNumber, KEYWORD, yytext); }

and|or|not  { return setValue(lineNumber, KEYWORD, yytext); }

return|to|do|by  { return setValue(lineNumber, KEYWORD, yytext); }

true|false  { return setValue(lineNumber, BOOLCONST, yytext); }


/*TOKENS & REGEX*/

[0-9]+                  { return setValue(lineNumber, NUMCONST, yytext); }
[a-zA-Z][a-zA-Z0-9]*    { return setValue(lineNumber,ID, yytext); }
\"((\\\")|[^\n"])*\"    { return setValue(lineNumber, STRINGCONST, yytext); }
\'((\\\")|[^\n"])*\'    { return setValue(lineNumber, CHARCONST, yytext); }
\(|\)|\{|\}|\[|\]       { return setValue(lineNumber, TOKEN, yytext ); }
\;|\:|\,                        { return setValue(lineCount, TOKEN, yytext); }
\?|\*|\/|\%|\-|\+               { return setValue(lineCount, TOKEN, yytext); }
\/\=|\+\=|\-\=|\*\=|\+\+|\-\-   { return setValue(lineCount, TOKEN, yytext); }
\<|\<\=|\>|\>\=|\=\=|\=|\!\=    { return setValue(lineCount, TOKEN, yytext); }
[ \t]                  { /* ignore white space */ }
\/\/.*\n               { lineNumber++; }                 ;
\n                     { lineNumber++; return setValue(lineNumber, yytext[0], yytext ); }
.                      { 
                            printf("ERROR(%d): Invalid or misplaced input character: \'%c\' Character Ignored.\n", lineNumber, yytext[0]);
                            NumberOfErrors++;
                       }
%%
