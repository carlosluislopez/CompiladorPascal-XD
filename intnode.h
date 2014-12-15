#ifndef INTNODE_H
#define INTNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"
#include "inttype.h"
#include "intvalue.h"

class IntNode : public ExpresionNode
{
public:
    IntNode();
    ~IntNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
    string Value;
};

#endif // INTNODE_H
