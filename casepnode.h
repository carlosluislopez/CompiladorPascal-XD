#ifndef CASEPNODE_H
#define CASEPNODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include <list>

class CasePNode : public StatementNode
{
public:
    CasePNode();
    ~CasePNode();

    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);

    ExpresionNode *Condition;
    list<StatementNode*> * Code;
};

#endif // CASEPNODE_H
