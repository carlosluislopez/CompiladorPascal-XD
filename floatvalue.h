#ifndef FLOATVALUE_H
#define FLOATVALUE_H

#include "ExpresionValue.h"

class FloatValue : public ExpresionValue
{
public:
    FloatValue(float);
    ~FloatValue();
    string ToString();
    Utileria util;
private:
    float floatValue;
};

#endif // FLOATVALUE_H
