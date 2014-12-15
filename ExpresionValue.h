#ifndef EXPRESIONVALUE_H
#define EXPRESIONVALUE_H

#include "string"
#include "utileria.h"
#include "SemanticException.h"

using namespace std;

class ExpresionValue
{
public:
    virtual string ToString() = 0;
    Utileria util;
};

#endif // EXPRESIONVALUE_H
