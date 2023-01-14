#ifndef SCANTYPE_H
#define SCANTYPE_H
struct TokenData {
    int tokenclass;  // token class
    int linenum;     // what line did this token occur on?
    char *tokenstr;
    int idIndex;     // index for id
    double numValue; // the value of the number as a DOUBLE!
};

#endif
