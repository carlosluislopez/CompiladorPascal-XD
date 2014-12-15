#ifndef DOWHILENODE_H
#define DOWHILENODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include <list>

class DoWhileNode : public StatementNode
{
public:
    DoWhileNode();
    ~DoWhileNode();

    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);

    ExpresionNode *Condition;
    list<StatementNode*> * Code;

};

#endif // DOWHILENODE_H
