#ifndef INTVALUE_H
#define INTVALUE_H

#include "ExpresionValue.h"

using namespace std;

class IntValue : public ExpresionValue
{
public:
    IntValue(int value);
    ~IntValue();
    string ToString();
    Utileria util;
private:
    int intValue;
};

#endif // INTVALUE_H
