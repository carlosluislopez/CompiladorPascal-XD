#include "chartype.h"

CharType::CharType()
{
    this->type = BaseTypeChar;
}

CharType::~CharType()
{
}


bool CharType::IsAssignable(BaseType *type) const{
    if(type->type == BaseTypeChar
       || type->type == BaseTypeString
      )
        return true;

    return false;
}

ExpresionValue * CharType::GetDefaultValue() const{
    return new CharValue('\0');
}

ExpresionValue * CharType::Parse(string inputValue){
    return new CharValue(inputValue.c_str()[0]);
}
