#ifndef GREATERTHANOPERATORNODE_H
#define GREATERTHANOPERATORNODE_H

#include "BinaryOperatorNode.h"

class GreaterThanOperatorNode : public BinaryOperatorNode
{
public:
    GreaterThanOperatorNode();
    ~GreaterThanOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // GREATERTHANOPERATORNODE_H
