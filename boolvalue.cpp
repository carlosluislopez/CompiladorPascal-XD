#include "boolvalue.h"

BoolValue::BoolValue(bool value)
{
    boolValue = value;
}

BoolValue::~BoolValue(){}


string BoolValue::ToString(){
    return util.toStringBool(boolValue);
}

