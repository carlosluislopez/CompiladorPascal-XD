#include "stringtype.h"

StringType::StringType()
{
    this->type = BaseTypeString;
}

StringType::~StringType()
{
}

bool StringType::IsAssignable(BaseType *type) const{
    if(type->type == BaseTypeString
       || type->type == BaseTypeInt
       || type->type == BaseTypeFloat
       || type->type == BaseTypeChar
       || type->type == BaseTypeBool
      )
        return true;

    return false;
}


ExpresionValue * StringType::GetDefaultValue() const{
    return new StringValue("");
}

ExpresionValue * StringType::Parse(string inputValue){
    return new StringValue(inputValue);
}
