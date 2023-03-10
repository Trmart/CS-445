#ifndef TOKENFORMATTER_H
#define TOKENFORMATTER_H

#include <string>

class TokenFormatter
{
   public:
   
      // Formats the TokenData contained string value to UpperCase Letters
      static std::string toUpperCase(const std::string &str);

      // identifies if the leftmost char is the beginning of a newline or null char
      static char parseLeftmostCharacter(const std::string &str);

      // deletes the leftmost and rightmost characters of a string
      static std::string stringSize(const std::string &str);

      // parses the characters of a string
      static std::string parseCharacters(const std::string &str);
};    

#endif