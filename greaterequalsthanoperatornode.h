#ifndef GREATEREQUALSTHANOPERATORNODE_H
#define GREATEREQUALSTHANOPERATORNODE_H

#include "BinaryOperatorNode.h"

class GreaterEqualsThanOperatorNode : public BinaryOperatorNode
{
public:
    GreaterEqualsThanOperatorNode();
    ~GreaterEqualsThanOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // GREATEREQUALSTHANOPERATORNODE_H
