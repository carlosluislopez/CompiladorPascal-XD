#ifndef EXPRESIONNODE_H
#define EXPRESIONNODE_H

#include "BaseType.h"
#include "ExpresionValue.h"

class ExpresionNode
{
public:
    ExpresionNode(){}
    ~ExpresionNode(){}
    virtual float Evaluate() = 0;
    virtual BaseType *ValidateSemantics() = 0;
    virtual ExpresionValue *Interpret() = 0;
};

#endif // EXPRESIONNODE_H
