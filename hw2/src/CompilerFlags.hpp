/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW2
Dr. Wilder
1/30/2023

FILE: CompilerFlags.hpp
DESC: CompilerFlags Class to detect and hold c- compiler flags
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
        bool getPrintASTFlag() const;
        bool getHelpFlag() const;
        bool getErrorFlag() const;
        std::string getFile() const;

    protected:

        // Flag member variables
        bool m_debugFlag = false;   // -d
        bool m_printASTFlag = false;   // -p
        bool m_helpFlag = false;   // -h
        bool m_errorFlag = false;   // flag error


        //file member variable
        std::string m_file = "";

        //Setters
        void setDebugFlag(bool debugFlag);
        void setPrintASTFlag(bool printASTFlag);
        void setHelpFlag(bool helpFlag);
        void setErrorFlag(bool errorFlag);
        void setFile(std::string file);
}; 

#endif