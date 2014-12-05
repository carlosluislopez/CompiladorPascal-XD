#ifndef FLOATTYPE_H
#define FLOATTYPE_H

#include "BaseType.h"

class FloatType : public BaseType
{
public:
    FloatType();
    ~FloatType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue) const;
};

#endif // FLOATTYPE_H
