#ifndef STRINGTYPE_H
#define STRINGTYPE_H

#include "BaseType.h"
#include "ExpresionValue.h"

using namespace std;

class StringType : public BaseType
{
public:
    StringType();
    ~StringType();
    BaseType *ValidateSemantics() const;
    bool IsAssignable(BaseType *type) const;
    ExpresionValue *GetDefaultValue() const;
    ExpresionValue *Parse(string inputValue) const;
};

#endif // STRINGTYPE_H
