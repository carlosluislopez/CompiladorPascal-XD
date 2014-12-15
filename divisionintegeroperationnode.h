#ifndef DIVISIONINTEGEROPERATIONNODE_H
#define DIVISIONINTEGEROPERATIONNODE_H

#include "BinaryOperatorNode.h"

class DivisionIntegerOperationNode : public BinaryOperatorNode
{
public:
    DivisionIntegerOperationNode();
    ~DivisionIntegerOperationNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // DIVISIONINTEGEROPERATIONNODE_H
