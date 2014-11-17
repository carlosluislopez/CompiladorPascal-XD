#ifndef LESSEQUALSTHANOPERATORNODE_H
#define LESSEQUALSTHANOPERATORNODE_H

#include "BinaryOperatorNode.h"

class LessEqualsThanOperatorNode : public BinaryOperatorNode
{
public:
    LessEqualsThanOperatorNode();
    ~LessEqualsThanOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // LESSEQUALSTHANOPERATORNODE_H
