#ifndef EQUALSOPERATORNODE_H
#define EQUALSOPERATORNODE_H

#include "BinaryOperatorNode.h"

class EqualsOperatorNode : public BinaryOperatorNode
{
public:
    EqualsOperatorNode();
    ~EqualsOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // EQUALSOPERATORNODE_H
