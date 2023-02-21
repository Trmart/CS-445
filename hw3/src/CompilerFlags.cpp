/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/

#include "CompilerFlags.hpp"
#include "ourgetopt/ourgetopt.h"
#include <iostream>

// default constructor
CompilerFlags::CompilerFlags()
{

}

// constructor
CompilerFlags::CompilerFlags(int argc, char *argv[])
{
    //from ourgetopt.h
    extern char *optarg;                   /* option argument if : in opts */
    extern int optind;  
    
    resetCompilerFlags();
    
    char compilerFlag = ' ';

    while(true)
    {

        while((compilerFlag = ourGetopt(argc, argv, (char* )"dDhpP")) != EOF)
        {
            switch (compilerFlag)
            {
                case 'd':
                        {
                            setDebugFlag(true);
                        }
                        break;
                case 'D':
                        {
                            setSymbolTableFlag(true);
                        }
                case 'h':
                        {
                            setHelpFlag(true);
                        }
                        break;
                case 'p':
                        {
                            setPrintASTFlag(true);
                        }
                        break;
                case 'P':
                        {
                            setPrintASTWithTypesFlag(true);
                        }
                default:
                        {
                            setErrorFlag(true);
                        }
                    break;
            }
        }
        
        if(getHelpFlag())
        {
            printHelpMenu();
            exit(0);
        }
        else if(getErrorFlag())
        {
            std::cout << "Invalid flag: \'" << compilerFlag << "\'" << std::endl;
            printHelpMenu();
            exit(1);
        }
        // Remove an invalid input option
        else 
        {
            if(optind < argc)
            {
                // m_file = argv[optind];
                setFile(argv[optind]);
                optind++;
            }
            else
            {
                break; 
            }
        }
    }
}

void CompilerFlags::printHelpMenu()
{
    std::cout << "usage: c- [options] [sourcefile]" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "-d     - turn on parser debugging" << std::endl;
    std::cout << "-D     - turn on symbol table debugging" << std::endl;
    std::cout << "-h     - print this usage message" << std::endl;
    std::cout << "-p     - print the abstract syntax tree" << std::endl;
    std::cout << "-P     - print the abstract syntax tree plus type information" << std::endl;
}

//Setters
void CompilerFlags::setDebugFlag(bool debugFlag)
{
    m_debugFlag = debugFlag;
}

void CompilerFlags::setSymbolTableFlag(bool symbolTableFlag)
{
    m_symbolTableFlag = symbolTableFlag;
}

void CompilerFlags::setHelpFlag(bool helpFlag)
{
    m_helpFlag = helpFlag;
}

void CompilerFlags::setPrintASTFlag(bool printASTFlag)
{
    m_printASTFlag = printASTFlag;
}

void CompilerFlags::setPrintASTWithTypesFlag(bool printASTWithTypesFlag)
{
    m_printASTWithTypesFlag = printASTWithTypesFlag;
}

void CompilerFlags::setFile(std::string file)
{
    m_file = file;
}


void CompilerFlags::setErrorFlag(bool errorFlag)
{
    m_errorFlag = errorFlag;
}




void CompilerFlags::resetCompilerFlags()
{
    m_debugFlag = false;
    
    m_symbolTableFlag = false;

    m_helpFlag = false;
    
    m_printASTFlag = false;

    m_printASTWithTypesFlag = false;
    
    m_errorFlag = false;
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

bool CompilerFlags::getErrorFlag() const
{
    return m_errorFlag;
}

bool CompilerFlags::getHelpFlag() const
{
    return m_helpFlag;
}

bool CompilerFlags::getSymbolTableFlag() const
{
    return m_symbolTableFlag;
}

bool CompilerFlags::getPrintASTWithTypesFlag() const
{
    return m_printASTWithTypesFlag;
}
