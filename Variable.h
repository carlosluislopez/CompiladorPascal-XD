#ifndef VARIABLE_H
#define VARIABLE_H

#include "BaseType.h"
#include "ExpresionValue.h"
#include <string>

using namespace std;

class Variable{
public:
    Variable(){ Type = 0; Value = 0; }
    ~Variable(){ delete Type; delete Value; }
    string Name;
    BaseType * Type;
    ExpresionValue * Value;
};

#endif // VARIABLE_H
