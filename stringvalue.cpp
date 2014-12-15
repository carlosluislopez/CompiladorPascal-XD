#include "stringvalue.h"

StringValue::StringValue(string value)
{
    stringValue = value;
}

StringValue::~StringValue(){}

string StringValue::ToString()
{
    return stringValue;
}


