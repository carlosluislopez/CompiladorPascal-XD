#ifndef ACCESOR_H
#define ACCESOR_H

#include <string>
#include <list>
#include "BaseType.h"
#include "utileria.h"
#include "SemanticException.h"

using namespace std;

class Accesor
{
public:
    Accesor *Next;
    virtual BaseType *ValidateSemantics(BaseType *sourceType) const = 0;
    virtual string ToXML(int identation) = 0;
    Utileria util;
};
#endif // ACCESOR_H
