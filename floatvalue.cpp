#include "floatvalue.h"

FloatValue::FloatValue(float value)
{
    floatValue = value;
}

FloatValue::~FloatValue(){}


string FloatValue::ToString(){
    return util.toStringFloat(floatValue);
}
