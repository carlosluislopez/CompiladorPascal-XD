#ifndef FLOATTYPE_H
#define FLOATTYPE_H

#include "BaseType.h"
#include "Values.h"

class FloatType : public BaseType
{
public:
    FloatType();
    ~FloatType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue);
};

#endif // FLOATTYPE_H
