#include "Emit.hpp"


//*************************************************************************************************
// ******************************* Error Class Functions ******************************************
//*************************************************************************************************

//emitErrorCount()
//get the number of errors and emit the number of errors
void Emit::Error::emitErrorCount()
{
    std::cout << "Number of errors: " << m_errorCount<< std::endl;
}

//emitGenericError()
/* @p*/
void Emit::Error::emitGenericError(const int lineNumber, const std::string errorMessage)
{
    std::cout << "Error: " << errorMessage << " on line " << lineNumber << std::endl;
    setErrorCount(1);
}


void Emit::Error::setErrorCount(int count)
{
    //increment the number of errors
    m_errorCount += count;
}

//*************************************************************************************************
// ******************************* Warning Class Functions ****************************************
//*************************************************************************************************