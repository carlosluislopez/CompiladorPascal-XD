#ifndef BOOLNODE_H
#define BOOLNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"
#include "booltype.h"
#include "boolvalue.h"

class BoolNode : public ExpresionNode
{
public:
    BoolNode();
    ~BoolNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
    string Value;
};

#endif // BOOLNODE_H
