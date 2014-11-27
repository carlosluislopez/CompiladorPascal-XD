#include "stringtype.h"

StringType::StringType()
{
}

StringType::~StringType()
{
}

bool StringType::IsAssignable(BaseType *type) const{
    return true;
}


ExpresionValue * StringType::GetDefaultValue() const{
    return 0;
}

ExpresionValue * StringType::Parse(string inputValue) const{
    return 0;
}
