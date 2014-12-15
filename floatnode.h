#ifndef FLOATNODE_H
#define FLOATNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"
#include "floattype.h"
#include "floatvalue.h"


class FloatNode : public ExpresionNode
{
public:
    FloatNode();
    ~FloatNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret();
    string ToXML(int identation);
    string Value;
};

#endif // FLOATNODE_H
