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
    ExpresionValue *Interpret();
    string ToXML(int identation);
    string Value;
};

#endif // BINARYNODE_H
