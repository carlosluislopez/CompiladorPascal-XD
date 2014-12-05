#ifndef BASETYPE_H
#define BASETYPE_H

#include <string>
#include "ExpresionValue.h"
#include "utileria.h"
#include "SemanticException.h"
//#include "Types.h"

using namespace std;

enum BaseTypeType{
    BaseTypeInt
    ,BaseTypeFloat
    ,BaseTypeString
    ,BaseTypeChar
    ,BaseTypeBool
    ,BaseTypeArray
    ,BaseTypeRange
    ,BaseTypeEnum
    ,BaseTypeRecord
};

class BaseType
{
public:
    virtual bool IsAssignable(BaseType *type) const = 0;
    virtual ExpresionValue *GetDefaultValue() const = 0;
    virtual ExpresionValue *Parse(string inputValue) const = 0;
    Utileria util;
    BaseTypeType type;
};

#endif // BASETYPE_H
