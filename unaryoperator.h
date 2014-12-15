#ifndef UNARYOPERATOR_H
#define UNARYOPERATOR_H

#include "ExpresionNode.h"
#include "booltype.h"

class UnaryOperator : public ExpresionNode
{
public:
    UnaryOperator();
    ~UnaryOperator();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
    ExpresionNode *OperandNode;
};

#endif // UNARYOPERATOR_H
