#ifndef WHILENODE_H
#define WHILENODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include <list>

class WhileNode : public StatementNode
{
public:
    WhileNode();
    ~WhileNode();

    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);

    ExpresionNode *Condition;
    list<StatementNode*> * Code;

};

#endif // WHILENODE_H
