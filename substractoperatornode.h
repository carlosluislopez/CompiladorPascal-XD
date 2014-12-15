#ifndef SUBSTRACTOPERATORNODE_H
#define SUBSTRACTOPERATORNODE_H

#include "BinaryOperatorNode.h"

class SubstractOperatorNode : public BinaryOperatorNode
{
public:
    SubstractOperatorNode();
    ~SubstractOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // SUBSTRACTOPERATORNODE_H
