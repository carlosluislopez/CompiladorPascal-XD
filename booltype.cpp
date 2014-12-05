#include "booltype.h"

BoolType::BoolType()
{
    this->type = BaseTypeBool;
}

BoolType::~BoolType()
{
}


bool BoolType::IsAssignable(BaseType *type) const{
    return true;
}

ExpresionValue * BoolType::GetDefaultValue() const{
    return 0;
}

ExpresionValue * BoolType::Parse(string inputValue) const{
    return 0;
}
