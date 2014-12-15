#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include "ExpresionValue.h"

class StringValue : public ExpresionValue
{
public:
    StringValue(string);
    ~StringValue();
    string ToString();
    Utileria util;
private:
    string stringValue;
};

#endif // STRINGVALUE_H
