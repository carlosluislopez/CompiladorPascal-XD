#include "intvalue.h"

IntValue::IntValue(int value)
{
    intValue = value;
}

IntValue::~IntValue()
{
}

string IntValue::ToString()
{
    return this->util.toString(intValue);
}
