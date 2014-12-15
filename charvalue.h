#ifndef CHARVALUE_H
#define CHARVALUE_H

#include "ExpresionValue.h"

class CharValue : public ExpresionValue
{
public:
    CharValue(char);
    ~CharValue();
    string ToString();
    Utileria util;
private:
    char charValue;
};

#endif // CHARVALUE_H
