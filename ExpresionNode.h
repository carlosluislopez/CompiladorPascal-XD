#ifndef EXPRESIONNODE_H
#define EXPRESIONNODE_H

#include "BaseType.h"
#include "ExpresionValue.h"
#include "utileria.h"
#include "SemanticException.h"

class ExpresionNode
{
public:
    virtual BaseType *ValidateSemantics() const = 0;
    virtual ExpresionValue *Interpret() const = 0;
    virtual string ToXML(int identation) = 0;
    Utileria util;
};

#endif // EXPRESIONNODE_H
