#include "floattype.h"

FloatType::FloatType()
{
    this->type = BaseTypeFloat;
}

FloatType::~FloatType()
{
}


bool FloatType::IsAssignable(BaseType *type) const{
    if(type->type == BaseTypeInt
       || type->type == BaseTypeFloat
      )
        return true;

    return false;
}

ExpresionValue * FloatType::GetDefaultValue() const{
    return new FloatValue(0);
}

ExpresionValue * FloatType::Parse(string inputValue){
    return new FloatValue(util.toFloatFromString(inputValue));
}
