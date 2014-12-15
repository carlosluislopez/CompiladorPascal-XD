#include "charvalue.h"

CharValue::CharValue(char value)
{
    charValue = value;
}

CharValue::~CharValue(){}


string CharValue::ToString()
{
    return util.toStringChar(charValue);
}
