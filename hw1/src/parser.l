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
#include "TokenFormatter.hpp" // TokenFormatter class
#include <string>

// Variables for ERR
int lineNumber = 1;         // ERR line number from the scanner!!
int numberOfErrors;    // ERR err count

void setTokenString(int line)
{
    lineNumber = line;
}

static int setValue(int linenum, int tokenClass, char *svalue)
{
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->tokenLineNumber = linenum;

    // duplicate string!!
    yylval.tokenData->tokenInformation = strdup(svalue);  
  
    // tokenClass State Machine
    switch (tokenClass)
    {
        case ID:
            break;
        case NUMCONST:
                {
                    yylval.tokenData->numValue = std::stoi(yylval.tokenData->tokenInformation);
                }
                break;
        case STRINGCONST:
                    {
                        //remove the leftmost and rightmost escape characters
                        TokenFormatter::deleteLeftmostAndRightmostCharacters(yylval.tokenData->tokenInformation);
                        
                        //parse the string
                        yylval.tokenData->stringValue = TokenFormatter::parseCharacters(yylval.tokenData->tokenInformation);
                    }
                    break;
        case CHARCONST:
                    { 
                        std::string chars = TokenFormatter::deleteLeftmostAndRightmostCharacters(yylval.tokenData->tokenInformation);
                        
                        yylval.tokenData->charValue = TokenFormatter::parseLeftmostCharacter(chars);
                        
                        if (chars.length() > 1 && chars[0] != '\\')
                        {
                            yylval.tokenData->isCharLengthGreaterThan1 = true;
                        }
                    }
                    break;
        case BOOLCONST:
                    {
                        //if num value is 1, then it is true. else it is false
                        yylval.tokenData->numValue = yylval.tokenData->tokenInformation == "true";
                    }
                    break;
        case TOKEN:
                {
                    //Token State Machine for string comparisons and token formatting
                    if(yylval.tokenData->tokenInformation == "==")
                    {
                        yylval.tokenData->stringValue = '=';
                    }
                    else if(yylval.tokenData->tokenInformation == "++")
                    {
                        yylval.tokenData->stringValue = "INC";
                    }
                    else if(yylval.tokenData->tokenInformation == "..")
                    {
                        yylval.tokenData->stringValue = "TO";
                    }
                    else if(yylval.tokenData->tokenInformation == "--")
                    {
                        yylval.tokenData->stringValue = "DEC";
                    }
                    else if(yylval.tokenData->tokenInformation == "!>")
                    {
                        yylval.tokenData->stringValue = "LEQ";
                    }
                    else if(yylval.tokenData->tokenInformation == "<=")
                    {
                        yylval.tokenData->stringValue = "ASGN";
                    }
                    else if(yylval.tokenData->tokenInformation == "!<")
                    {
                        yylval.tokenData->stringValue = "GEQ";
                    }
                    else if(yylval.tokenData->tokenInformation == "!=")
                    {
                        yylval.tokenData->stringValue = "NEQ";
                    }
                    else if(yylval.tokenData->tokenInformation == "+=")
                    {
                        yylval.tokenData->stringValue = "ADDASS";
                    }
                    else
                    {
                        yylval.tokenData->stringValue = yylval.tokenData->tokenInformation;
                    }
                }
                break;
        case KEYWORD:
                {
                    //convery string to uppercase for output formatting
                    yylval.tokenData->stringValue = TokenFormatter::toUpperCase(yylval.tokenData->tokenInformation);
                    
                    //convert STEP keyword to BY keyword
                    if(yylval.tokenData->stringValue == "STEP")
                    {
                        yylval.tokenData->stringValue = "BY";
                    }

                }
            break;
    }

    return tokenClass;
}

%}

%option noyywrap

%%



int|bool|char|static  { return setValue(lineNumber, KEYWORD, yytext); }

while|for|break  { return setValue(lineNumber, KEYWORD, yytext); }

if|else|begin|end|then  { return setValue(lineNumber, KEYWORD, yytext); }

and|or|not  { return setValue(lineNumber, KEYWORD, yytext); }

return|do|step  { return setValue(lineNumber, KEYWORD, yytext); }

true|false  { return setValue(lineNumber, BOOLCONST, yytext); }



[0-9]+                  { return setValue(lineNumber, NUMCONST, yytext); }
[a-zA-Z][a-zA-Z0-9]*    { return setValue(lineNumber,ID, yytext); }
\"((\\\")|[^\n"])*\"    { return setValue(lineNumber, STRINGCONST, yytext); }
\'((\\\')|[^\n'])*\'    { return setValue(lineNumber, CHARCONST, yytext); }
\(|\)|\[|\]       { return setValue(lineNumber, TOKEN, yytext ); }
\;|\:|\,                        { return setValue(lineNumber, TOKEN, yytext); }
\?|\*|\/|\%|\-|\+               { return setValue(lineNumber, TOKEN, yytext); }
\/\=|\+\=|\-\=|\*\=|\+\+|\-\-   { return setValue(lineNumber, TOKEN, yytext); }
\<|\<\=|\>|\>\=|\=\=|\=|\!\=|\!\<|\!\>|\.\.    { return setValue(lineNumber, TOKEN, yytext); }
[ \t]                  { /* ignore white space */ }
\#\#.*\n               { /* ignore comments */ lineNumber++; }
\n                     { lineNumber++; return setValue(lineNumber, yytext[0], yytext ); }
.                      { 
                            printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", lineNumber, yytext[0]);
                            numberOfErrors++;
                       }
%%
