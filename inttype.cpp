#include "inttype.h"

IntType::IntType()
{
    this->type = BaseTypeInt;
}

IntType::~IntType()
{
}

bool IntType::IsAssignable(BaseType *type) const{
    if(type->type == BaseTypeFloat
       || type->type == BaseTypeInt
      )
        return true;

    return false;
}

ExpresionValue * IntType::GetDefaultValue() const{
    return new IntValue(0);
}

ExpresionValue * IntType::Parse(string inputValue){
    return new IntValue(util.toIntFromString(inputValue));
}
