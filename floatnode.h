#ifndef FLOATNODE_H
#define FLOATNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"


class FloatNode : public ExpresionNode
{
public:
    FloatNode();
    ~FloatNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
};

#endif // FLOATNODE_H
