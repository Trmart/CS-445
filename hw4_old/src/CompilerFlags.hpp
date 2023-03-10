/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW4
Dr. Wilder
DUE: 3/12/2023

FILE: CompilerFlags.cpp
DESC: Class functions definitions to detect and hold c- compiler flags
*/

#ifndef COMPILERFLAGS_H
#define COMPILERFLAGS_H

#include <string>

class CompilerFlags
{
    public: 
        
        // Constructor
        CompilerFlags(); 
        CompilerFlags(int argc, char *argv[]);

        // Reset all flags to false
        void resetCompilerFlags();
        void printHelpMenu();

        // Getters
        bool getDebugFlag() const;
        bool getSymbolTableFlag() const;
        bool getHelpFlag() const;
        bool getPrintASTFlag() const;
        bool getPrintASTWithTypesFlag() const;
        bool getErrorFlag() const;

    protected:

        // Flag member variables
        bool m_debugFlag = false;   // -d
        bool m_symbolTableFlag = false;   // -D
        bool m_helpFlag = false;   // -h
        bool m_printASTFlag = false;   // -p
        bool m_printASTWithTypesFlag = false;   // -P
        bool m_errorFlag = false;   // flag error

        //Setters
        void setDebugFlag(bool debugFlag);
        void setSymbolTableFlag(bool symbolTableFlag);
        void setHelpFlag(bool helpFlag);
        void setPrintASTFlag(bool printASTFlag);
        void setPrintASTWithTypesFlag(bool printASTWithTypesFlag);
        void setErrorFlag(bool errorFlag);
}; 

#endif
