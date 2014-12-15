#include "booltype.h"

BoolType::BoolType()
{
    this->type = BaseTypeBool;
}

BoolType::~BoolType()
{
}


bool BoolType::IsAssignable(BaseType *type) const{
    if(type->type == BaseTypeBool
       || type->type == BaseTypeInt
      )
        return true;

    return false;
}

ExpresionValue * BoolType::GetDefaultValue() const{
    return new BoolValue(false);
}

ExpresionValue * BoolType::Parse(string inputValue){
    return new BoolValue(util.toBoolFromString(inputValue));
}
