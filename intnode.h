#ifndef INTNODE_H
#define INTNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"

class IntNode : public ExpresionNode
{
public:
    IntNode();
    ~IntNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    string Value;
};

#endif // INTNODE_H
