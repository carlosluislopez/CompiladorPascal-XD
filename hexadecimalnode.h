#ifndef HEXADECIMALNODE_H
#define HEXADECIMALNODE_H

#include "ExpresionNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"

class HexadecimalNode : public ExpresionNode
{
public:
    HexadecimalNode();
    ~HexadecimalNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    string Value;
};

#endif // HEXADECIMALNODE_H
