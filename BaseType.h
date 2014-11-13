#ifndef BASETYPE_H
#define BASETYPE_H

#include <string>
#include "ExpresionValue.h"

using namespace std;

class BaseType
{
public:
    BaseType(){}
    ~BaseType(){}
    virtual bool IsAssignable(BaseType *type) = 0;
    virtual ExpresionValue *GetDefaultValue() = 0;
    virtual ExpresionValue *Parse(string inputValue) = 0;
};

#endif // BASETYPE_H
