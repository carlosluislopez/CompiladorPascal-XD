#ifndef CHARTYPE_H
#define CHARTYPE_H

#include "BaseType.h"

class CharType : public BaseType
{
public:
    CharType();
    ~CharType();
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue) const;
};

#endif // CHARTYPE_H
