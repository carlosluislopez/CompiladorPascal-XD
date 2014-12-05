#ifndef IDNODE_H
#define IDNODE_H

#include "ExpresionNode.h"
#include "Accesor.h"
#include "symboltable.h"

class IdNode : public ExpresionNode
{
public:
    IdNode();
    ~IdNode();
    BaseType *ValidateSemantics() const;
    ExpresionValue *Interpret() const;
    string ToXML(int identation);
    string Name;
    Accesor *AccesorList;
    SymbolTable *symbolTable;
};

#endif // IDNODE_H
