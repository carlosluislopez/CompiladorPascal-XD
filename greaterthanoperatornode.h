#ifndef GREATERTHANOPERATORNODE_H
#define GREATERTHANOPERATORNODE_H

#include "BinaryOperatorNode.h"

class GreaterThanOperatorNode : public BinaryOperatorNode
{
public:
    GreaterThanOperatorNode();
    ~GreaterThanOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // GREATERTHANOPERATORNODE_H
