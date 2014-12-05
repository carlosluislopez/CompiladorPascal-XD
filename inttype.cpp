#include "inttype.h"

IntType::IntType()
{
    this->type = BaseTypeInt;
}

IntType::~IntType()
{
}

bool IntType::IsAssignable(BaseType *type) const{
    return true;
}

ExpresionValue * IntType::GetDefaultValue() const{
    return 0;
}

ExpresionValue * IntType::Parse(string inputValue) const{
    return 0;
}
