#ifndef CASENODE_H
#define CASENODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include "casepnode.h"
#include <list>

class CaseNode : public StatementNode
{
public:
    CaseNode();
    ~CaseNode();

    void ValidateSemantics() const;
    void Interpret() const;
    string ToXML(int identation);

    ExpresionNode *Condition;
    list<CasePNode*> * CaseList;
    list<StatementNode*> * CodeElse;
};

#endif // CASENODE_H
