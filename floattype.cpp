#include "floattype.h"

FloatType::FloatType()
{
    this->type = BaseTypeFloat;
}

FloatType::~FloatType()
{
}


bool FloatType::IsAssignable(BaseType *type) const{
    return true;
}

ExpresionValue * FloatType::GetDefaultValue() const{
    return 0;
}

ExpresionValue * FloatType::Parse(string inputValue) const{
    return 0;
}
