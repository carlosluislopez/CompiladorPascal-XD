#ifndef BASETYPE_H
#define BASETYPE_H

#include <string>
#include "ExpresionValue.h"
#include "utileria.h"
#include "SemanticException.h"

using namespace std;

class BaseType
{
public:
    virtual bool IsAssignable(BaseType *type) const = 0;
    virtual ExpresionValue *GetDefaultValue() const = 0;
    virtual ExpresionValue *Parse(string inputValue) const = 0;
    Utileria util;
};

#endif // BASETYPE_H
