#ifndef NOTEQUALSOPERATORNODE_H
#define NOTEQUALSOPERATORNODE_H

#include "BinaryOperatorNode.h"

class NotEqualsOperatorNode : public BinaryOperatorNode
{
public:
    NotEqualsOperatorNode();
    ~NotEqualsOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // NOTEQUALSOPERATORNODE_H
