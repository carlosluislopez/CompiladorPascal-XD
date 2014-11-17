#ifndef MODOPERATIONNODE_H
#define MODOPERATIONNODE_H

#include "BinaryOperatorNode.h"

class ModOperationNode : public BinaryOperatorNode
{
public:
    ModOperationNode();
    ~ModOperationNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // MODOPERATIONNODE_H
