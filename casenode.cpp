#include "casenode.h"

CaseNode::CaseNode()
{
    Condition = 0;
    CaseList = 0;
    CodeElse = 0;
}

CaseNode::~CaseNode()
{
    delete Condition;
    delete CaseList;
    delete CodeElse;
}


void CaseNode::ValidateSemantics() const
{
}

void CaseNode::Interpret() const
{
}


string CaseNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<CaseNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation + 1) + "<Case>\n";
    for(std::list<CasePNode*>::iterator it = CaseList->begin(); it != CaseList->end(); it++)
    {
        CasePNode *caseP = *it;
        xml += caseP->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Case>\n";

    xml += util.getMeIdentation(identation + 1) + "<CodeElse>\n";
    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</CodeElse>\n";

    xml += util.getMeIdentation(identation) + "</CaseNode>\n";

    return xml;
}
