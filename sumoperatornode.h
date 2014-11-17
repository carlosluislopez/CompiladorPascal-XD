#ifndef SUMOPERATORNODE_H
#define SUMOPERATORNODE_H

#include "BinaryOperatorNode.h"

class SumOperatorNode : public BinaryOperatorNode
{
public:
    SumOperatorNode();
    ~SumOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // SUMOPERATORNODE_H
