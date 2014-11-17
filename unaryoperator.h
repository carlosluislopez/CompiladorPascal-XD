#ifndef UNARYOPERATOR_H
#define UNARYOPERATOR_H

#include "ExpresionNode.h"

class UnaryOperator : public ExpresionNode
{
public:
    UnaryOperator();
    ~UnaryOperator();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    ExpresionNode *OperandNode;
};

#endif // UNARYOPERATOR_H
