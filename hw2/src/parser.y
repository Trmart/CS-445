%{
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
#include "CompilerFlags.hpp" // Compiler Flags

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

%}

// this is included in the tab.hpp file
// so scanType.hpp must be included before the tab.hpp file!!!!
%union 
{
    Primitive::Type primitiveType;
    TokenData *tokenData;
    Node *node;
}

%token <tokenData> ID NUMCONST STRINGCONST CHARCONST BOOLCONST TOKEN KEYWORD


%%
statementlist : statementlist statement
              | statement
              ;

statement     : '\n'
                ;
%%


int main(int argc, char *argv[])
{
    //create the compiler flags object. This will parse the command line arguments
    CompilerFlags compilerFlags(argc, argv);

    //get the debug flag from the compiler flags object
    yydebug = compilerFlags.getDebugFlag();

    //get the file name from the compiler flags object
    std::string fileName = compilerFlags.getFileName();

    //if the compiler flags object has an error, print the error and exit
    if (argc > 1) 
    {
        // if failed to open file
        if (!(yyin = fileName.c_str(), "r"))) 
        {
            //print error message
            printf("ERROR: failed to open \'%s\'\n", fileName.c_str());
            //exit with error
            exit(1);
        }
    }

    //parse the input
    yyparse();

    //if the the -p flag was passed, print the AST
    if(compilerFlags.getPrintFlag())
    {
        if(root != NULL)
        {
            root->print();
        }
    }

    //delete the tree root. Free the memory. 
    delete root;

    //close the file sent into the c- compiler
    fclose(yyin);


    //close the file and exit with success
    return 0;
}
