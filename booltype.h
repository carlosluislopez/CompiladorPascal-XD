#ifndef BOOLTYPE_H
#define BOOLTYPE_H

#include "BaseType.h"
#include "Values.h"

class BoolType : public BaseType
{
public:
    BoolType();
    ~BoolType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue);
};

#endif // BOOLTYPE_H
