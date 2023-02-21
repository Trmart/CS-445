/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: Emit.hpp
DESC: yacc parser for the calculator language

Based off CS445 - Calculator Example Program by Robert Heckendorn
*/

#ifndef EMIT_HPP
#define EMIT_HPP

#include <iostream>
#include <string>


namespace Emit
{
    class Error
    {
        public: 

            //get the number of errors and emit the number of errors
            static void emitErrorCount();
            
            //emit a generic error
            static void emitGenericError(const int lineNumber, const std::string errorMessage);

            //emit a Linker error
            static void emitLinkerError(const int lineNumber, const std::string errorMessage);

            //emit a ArgList error
            static void emitArgListError(const int lineNumber, const std::string errorMessage);

            //emit an Undefined Main function error
            static void emitUndefinedMainError(const int lineNumber, const std::string errorMessage);


        protected:

            //set the number of errors
            static void setErrorCount(int count);
            
            //the number of errors
            static int m_errorCount;

    };

    class Warning
    {
        public: 
            
            //get the number of warnings and emit the number of warnings
            static void emitWarningCount();

            //emit a generic warning message
            static void emitGenericWarnings(const char* message);
        
        
        protected:
            
            //set the number of warnings
            static void setWarningCount(int count);

            //the number of warnings
            static int m_warningCount;
    };
}

#endif