#ifndef BOOLTYPE_H
#define BOOLTYPE_H

#include "BaseType.h"

class BoolType : public BaseType
{
public:
    BoolType();
    ~BoolType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue) const;
};

#endif // BOOLTYPE_H