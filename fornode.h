#ifndef FORNODE_H
#define FORNODE_H

#include "StatementNode.h"
#include "idnode.h"
#include "ExpresionNode.h"
#include "symboltable.h"
#include <list>

class ForNode : public StatementNode
{
public:
    ForNode();
    ~ForNode();
    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);

    IdNode *Id;
    ExpresionNode *InitialValue;
    ExpresionNode *FinalValue;
    list<StatementNode*> * Code;
    bool Increment;
    SymbolTable *symbolTable;
};

#endif // FORNODE_H
