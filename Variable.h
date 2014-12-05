#ifndef VARIABLE_H
#define VARIABLE_H

#include "BaseType.h"
#include <string>

using namespace std;

class Variable{
public:
    Variable(){ Type = 0; }
    ~Variable(){ delete Type; }
    string Name;
    BaseType * Type;
};

#endif // VARIABLE_H
