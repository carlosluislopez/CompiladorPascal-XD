#ifndef CHARNODE_H
#define CHARNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"

class CharNode : public ExpresionNode
{
public:
    CharNode();
    ~CharNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    string Value;
};

#endif // CHARNODE_H
