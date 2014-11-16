#ifndef EXPRESIONVALUE_H
#define EXPRESIONVALUE_H

#include "string"
#include "utileria.h"

using namespace std;

class ExpresionValue
{
public:
    virtual string ToXML(int identation) = 0;
    Utileria util;
};

#endif // EXPRESIONVALUE_H
