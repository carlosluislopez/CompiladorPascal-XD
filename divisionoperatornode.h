#ifndef DIVISIONOPERATORNODE_H
#define DIVISIONOPERATORNODE_H

#include "BinaryOperatorNode.h"

class DivisionOperatorNode : public BinaryOperatorNode
{
public:
    DivisionOperatorNode();
    ~DivisionOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // DIVISIONOPERATORNODE_H
