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
#include "../ourgetopt/ourgetopt.h"
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

        while((compilerFlag = ourGetopt(argc, argv, (char* )"dph")) != EOF)
        {
            switch (compilerFlag)
            {
                case 'd':
                        {
                            setDebugFlag(true);
                        }
                        break;
                case 'p':
                        {
                            setPrintASTFlag(true);
                        }
                        break;
                case 'h':
                        {
                            setHelpFlag(true);
                        }
                        break;
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
    std::cout << "Usage: ./c- [options] file" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-d: Enable debug mode" << std::endl;
    std::cout << "-p: Print the AST" << std::endl;
    std::cout << "-h: Print this help message" << std::endl;
}

//Setters
void CompilerFlags::setDebugFlag(bool debugFlag)
{
    m_debugFlag = debugFlag;
}


void CompilerFlags::setPrintASTFlag(bool printASTFlag)
{
    m_printASTFlag = printASTFlag;
}

void CompilerFlags::setFile(std::string file)
{
    m_file = file;
}

void CompilerFlags::setHelpFlag(bool helpFlag)
{
    m_helpFlag = helpFlag;
}

void CompilerFlags::setErrorFlag(bool errorFlag)
{
    m_errorFlag = errorFlag;
}


void CompilerFlags::resetCompilerFlags()
{
    m_debugFlag = false;

    m_printASTFlag = false;

    m_helpFlag = false;

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