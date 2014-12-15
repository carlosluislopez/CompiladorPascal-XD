#ifndef BOOLVALUE_H
#define BOOLVALUE_H

#include "ExpresionValue.h"

class BoolValue : public ExpresionValue
{
public:
    BoolValue(bool);
    ~BoolValue();
    string ToString();
    Utileria util;
private:
    bool boolValue;
};

#endif // BOOLVALUE_H
