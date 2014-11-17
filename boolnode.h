#ifndef BOOLNODE_H
#define BOOLNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"

class BoolNode : public ExpresionNode
{
public:
    BoolNode();
    ~BoolNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    bool Value;
};

#endif // BOOLNODE_H
