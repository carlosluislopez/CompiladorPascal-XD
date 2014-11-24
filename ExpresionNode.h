#ifndef EXPRESIONNODE_H
#define EXPRESIONNODE_H

#include "BaseType.h"
#include "ExpresionValue.h"
#include "utileria.h"

enum ExpresionNodeType{
    StringNodeType
    ,IntNodeType
    ,FloatNodeType
    ,CharNodeType
    ,BoolNodeType
    ,BinaryNodeType
    ,HexadecimalNodeType
    ,IdNodeType
    ,BooleanExpresionNodeType
    ,OperatorNodeType
    ,AccesorNodeType
    ,ArrayAccesorNodeType
    ,FieldAccesorNodeType
    ,ParamAccesorNodeType
};

class ExpresionNode
{
public:
    virtual BaseType *ValidateSemantics() const = 0;
    virtual ExpresionValue *Interpret() const = 0;
    virtual string ToXML(int identation) = 0;
    Utileria util;
    ExpresionNodeType TypeNode;
};

#endif // EXPRESIONNODE_H
