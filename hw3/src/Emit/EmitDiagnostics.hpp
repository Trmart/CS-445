/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: EmitDiagnostics.hpp
DESC: Creates classes within the EmitDiagnostics namespace to emit errors and warnings

*/

#ifndef EMITDIAGNOSTICS_HPP
#define EMITDIAGNOSTICS_HPP

#include <iostream>
#include <string>


namespace EmitDiagnostics
{
    class Error
    {
        public: 

            //get the number of errors and emit the number of errors
            static void emitErrorCount();
            
            //emit a generic error
            static void emitGenericError(const int lineNumber, const std::string errorMessage);

            //emit a Linker error
            static void emitLinkerError(const std::string errorMessage);

            //emit a ArgList error
            static void emitArgListError(const std::string errorMessage);

            //emit an Undefined Main function error
            static void emitUndefinedMainError();

            //get the number of errors
            static int getErrorCount(); 



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
            static void emitGenericWarnings(const int lineNumber, const std::string warningMessage);

            //get the number of warnings
            static int getWarningCount(); 
        
        protected:
            
            //set the number of warnings
            static void setWarningCount(int count);

            //the number of warnings
            static int m_warningCount;
    };
}

#endif