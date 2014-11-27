#ifndef INTTYPE_H
#define INTTYPE_H

#include "BaseType.h"


class IntType : public BaseType
{
public:
    IntType();
    ~IntType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue) const;
};

#endif // INTTYPE_H
