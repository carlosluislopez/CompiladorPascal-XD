#include "chartype.h"

CharType::CharType()
{
    this->type = BaseTypeChar;
}

CharType::~CharType()
{
}


bool CharType::IsAssignable(BaseType *type) const{
    return true;
}

ExpresionValue * CharType::GetDefaultValue() const{
    return 0;
}

ExpresionValue * CharType::Parse(string inputValue) const{
    return 0;
}
