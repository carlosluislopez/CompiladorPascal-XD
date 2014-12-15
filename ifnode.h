#ifndef IFNODE_H
#define IFNODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include <list>

class IfNode : public StatementNode
{
public:
    IfNode();
    ~IfNode();

    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);

    ExpresionNode *Condition;
    list<StatementNode*> * Code;
    list<StatementNode*> * CodeElse;

};

#endif // IFNODE_H
