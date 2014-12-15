#ifndef LESSTHANOPERATORNODE_H
#define LESSTHANOPERATORNODE_H

#include "BinaryOperatorNode.h"

class LessThanOperatorNode : public BinaryOperatorNode
{
public:
    LessThanOperatorNode();
    ~LessThanOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // LESSTHANOPERATORNODE_H
