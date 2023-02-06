/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/

#include "CompilerFlags.hpp"
#include "ourgetopt/ourgetopt.h"
#include <iostream>

    
CompilerFlags::CompilerFlags(int argc, char *argv[])
{
    //from ourgetopt.h
    extern char *optarg;                   /* option argument if : in opts */
    extern int optind;  
    
    resetCompilerFlags();
    
    char compilerFlag = ' ';

    while(1)
    {

        while((compilerFlag = ourGetopt(argc, argv, (char*) "dp") != EOF))
        {
            if(compilerFlag == 'd')
            {
                setDebugFlag(true);
            }

            else if(compilerFlag == 'p')
            {
                setPrintASTFlag(true);
            }

            else
            {
                std::cout << "Invalid Compiler Flag: " << compilerFlag << std::endl;
                exit(1);
            }
        }
        
        // Pick off a nonoption
        if (optind < argc)
        {
            m_file = argv[optind];
            optind++;
        }
        else
        {
            break;
        }
    }
}

//Setters
bool CompilerFlags::setDebugFlag(bool debugFlag)
{
    m_debugFlag = debugFlag;
}


bool CompilerFlags::setPrintASTFlag(bool printASTFlag)
{
    m_printASTFlag = printASTFlag;
}

void CompilerFlags::setFile(std::string file)
{
    m_file = file;
}


void CompilerFlags::resetCompilerFlags()
{
    m_debugFlag = false;

    m_printASTFlag = false;
}

// Getters
bool CompilerFlags:: getDebugFlag() const
{
    return m_debugFlag;
}
bool CompilerFlags::getPrintASTFlag() const
{
    return m_printASTFlag;
}
std::string CompilerFlags::getFile() const
{
    return m_file;
}