#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"
#include "stringtype.h"

class StringNode : public ExpresionNode
{
public:
    StringNode();
    ~StringNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    string Value;
};

#endif // STRINGNODE_H
