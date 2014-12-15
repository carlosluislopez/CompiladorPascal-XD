#ifndef CHARTYPE_H
#define CHARTYPE_H

#include "BaseType.h"
#include "Values.h"

class CharType : public BaseType
{
public:
    CharType();
    ~CharType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue);
};

#endif // CHARTYPE_H
