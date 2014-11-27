#ifndef TYPEDEFINED_H
#define TYPEDEFINED_H

#include <string>
#include "BaseType.h"

using namespace std;

enum TypePrimitive{
    IntPrimitive
    ,StringPrimitive
    ,FloatPrimitive
    ,CharPrimitive
    ,BoolPrimitive
    ,BinayPrimitive
    ,HexadecimalPrimitive
};

class TypeDefined{
public:
    TypeDefined(){ Type = 0; }
    ~TypeDefined(){ delete Type; }
    string Name;
    BaseType *Type;
};

#endif // TYPEDEFINED_H
