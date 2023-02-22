/*
Taylor Martin
CS-445 Compiler Design
University Of Idaho
HW3
Dr. Wilder
2/13/2023

FILE: EmitDiagnostics.cpp
DESC: Creates classes within the EmitDiagnostics namespace to emit errors and warnings

*/

#include "EmitDiagnostics.hpp"


//*************************************************************************************************
// ******************************* Error Class Functions ******************************************
//*************************************************************************************************

/*
@function getErrorCount()
@return the number of errors
@description get the number of errors
*/
void EmitDiagnostics::Error::emitErrorCount()
{
    std::cout << "Number of errors: " << m_errorCount<< std::endl;
}


/* 
@function emitGenericError()
@param lineNumber the line number of the error
@param errorMessage the error message to be emitted
@description emit a generic error message and increment the number of errors
*/
void EmitDiagnostics::Error::emitGenericError(const int lineNumber, const std::string errorMessage)
{
    std::cout << "ERROR(" <<  lineNumber << "): " << errorMessage << std::endl;
    setErrorCount(1);
}

/* 
@function emitLinkerError()
@param lineNumber the line number of the error
@param errorMessage the error message to be emitted
@description emit a linker error message and increment the number of errors
*/
void EmitDiagnostics::Error::emitLinkerError(const std::string errorMessage)
{
    std::cout << "ERROR(LINKER): " << errorMessage << std::endl;
    setErrorCount(1);
}

/*
@function emitArgListError()
@param lineNumber the line number of the error
@param errorMessage the error message to be emitted
@description emit an ArgList error message and increment the number of errors
*/

void EmitDiagnostics::Error::emitArgListError(const std::string errorMessage)
{
    std::cout << "ERROR(ARGLIST): " << errorMessage << std::endl;
    setErrorCount(1);
}

/*
@function emitUndefinedMainError()
@description emit an Undefined Main function error message and increment the number of errors
*/
void EmitDiagnostics::Error::emitUndefinedMainError()
{
    emitLinkerError("A function named 'main()' must be defined.");
}

/*
@function setErrorCount()
@param count the number of errors to be set
@description set the number of errors
*/
void EmitDiagnostics::Error::setErrorCount(int count)
{
    //increment the number of errors
    m_errorCount += count;
}

/*
@function setErrorCount()
@return number of errors 
@description set the number of errors
*/
int EmitDiagnostics::Error::getErrorCount()
{
    return m_errorCount;
}

//*************************************************************************************************
// ******************************* Warning Class Functions ****************************************
//*************************************************************************************************

/*
@function emitWarningCount()
@description get the number of warnings and emit the number of warnings
*/
void EmitDiagnostics::Warning::emitWarningCount()
{
    std::cout << "Number of warnings: " << m_warningCount << std::endl;
}

/*
@function emitGenericWarnings()
@param message the warning message to be emitted
@description emit a generic warning message and increment the number of warnings
*/

void EmitDiagnostics::Warning::emitGenericWarnings(const int lineNumber, const char* message)
{
    std::cout << "WARNING(" << lineNumber << "): " << message << std::endl;
    setWarningCount(1);
}

/*
@function setWarningCount()
@param count the number of warnings to be set
@description set the number of warnings
*/
void EmitDiagnostics::Warning::setWarningCount(int count)
{
    //increment the number of warnings
    m_warningCount += count;
}

/*
@function getWarningCount()
@return number of warnings 
@description gets the number of warnings
*/
int EmitDiagnostics::Warning::getWarningCount()
{
    return m_warningCount;
}
