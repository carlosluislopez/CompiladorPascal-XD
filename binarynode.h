#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"

class BinaryNode : public ExpresionNode
{
public:
    BinaryNode();
    ~BinaryNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    int Value;
};

#endif // BINARYNODE_H
