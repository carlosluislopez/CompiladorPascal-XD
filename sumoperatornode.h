#ifndef SUMOPERATORNODE_H
#define SUMOPERATORNODE_H

#include "BinaryOperatorNode.h"

class SumOperatorNode : public BinaryOperatorNode
{
public:
    SumOperatorNode();
    ~SumOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
};

#endif // SUMOPERATORNODE_H
