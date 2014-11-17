#ifndef EXPOPERATIONNODE_H
#define EXPOPERATIONNODE_H

#include "BinaryOperatorNode.h"

class ExpOperationNode : public BinaryOperatorNode
{
public:
    ExpOperationNode();
    ~ExpOperationNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // EXPOPERATIONNODE_H
