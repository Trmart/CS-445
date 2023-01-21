%{
/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW1
Dr. Wilder
1/14/2023

FILE: parser.y
DESC: yacc parser for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#include "scanType.hpp"  // TokenData Type

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

//ERROR Message Definition and Output Function
#define YYERROR_VERBOSE
void yyerror(const char *message)
{
    //Output the error message
    std::cout << "ERROR(" << lineNumber + 1 << "): " << message << std::endl;
    
    //increment the error count
    numberOfErrors++;
}

%}

// this is included in the tab.hpp file
// so scanType.hpp must be included before the tab.hpp file!!!!
%union 
{
    TokenData *tokenData;
}

%token <tokenData> ID NUMCONST STRINGCONST CHARCONST BOOLCONST TOKEN KEYWORD


%%
statementlist : statementlist statement
              | statement
              ;

statement     : '\n'

                | ID    { std::cout << "Line " << $1->tokenLineNumber << " Token: ID Value: " << $1->tokenInformation << std::endl; }

                | NUMCONST { std::cout << "Line " << $1->tokenLineNumber << " Token: NUMCONST Value: " << $1->numValue << "Input: " << $1->tokenInformation << std::endl; }

                | STRINGCONST { std::cout << "Line " << $1->tokenLineNumber << " Token: STRINGCONST Value: " << $1->stringValue << "  Len: " << $1->tokenInformation.length() - 2 << "  Input: " << $1->tokenInformation << std::endl; }

                | CHARCONST { 
                                //check if the char is a valid char
                                if($1->isCharLengthGreaterThan1)
                                {
                                    std::cout << "WARNING(" << $1->tokenLineNumber << "): " << "character is " << $1->tokenInformation.length() - 2 << " characters long and not a single character: '" << $1->tokenInformation<<"'.  The first char will be used.\n";
                                }

                                std::cout << "Line " << $1->tokenLineNumber << " Token: CHARCONST Value: '" << $1->charValue << "'  Input: " << $1->tokenInformation << std::endl; 
                            }

                | BOOLCONST { std::cout << "Line " << $1->tokenLineNumber << " Token: BOOLCONST Value: " << $1->numValue << "Input: " << $1->tokenInformation << std::endl; }

                | TOKEN { std::cout << "Line " << $1->tokenLineNumber << " Token: " << $1->stringValue << std::endl; }

                | KEYWORD { std::cout << "Line " << $1->tokenLineNumber << " Token: " << $1->stringValue << std::endl; }
                ;
%%


int main(int argc, char *argv[])
{
    if (argc > 1) 
    {
        // if failed to open file
        if (!(yyin = fopen(argv[1], "r"))) 
        {
            //print error message
            printf("ERROR: failed to open \'%s\'\n", argv[1]);
            //exit with error
            exit(1);
        }
    }

    //parse the input
    yyparse();

    //close the file and exit with success
    return 0;
}
