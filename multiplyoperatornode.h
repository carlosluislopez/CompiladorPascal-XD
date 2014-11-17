#ifndef MULTIPLYOPERATORNODE_H
#define MULTIPLYOPERATORNODE_H

#include "BinaryOperatorNode.h"

class MultiplyOperatorNode : public BinaryOperatorNode
{
public:
    MultiplyOperatorNode();
    ~MultiplyOperatorNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // MULTIPLYOPERATORNODE_H
