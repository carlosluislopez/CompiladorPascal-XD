#include "casepnode.h"

CasePNode::CasePNode()
{
    Condition = 0;
    Code = 0;
}

CasePNode::~CasePNode()
{
    delete Condition;
    delete Code;
}


void CasePNode::ValidateSemantics() const
{
    BaseType *typeCondition = Condition->ValidateSemantics();
    if(!(typeCondition->type == BaseTypeInt || typeCondition->type == BaseTypeChar))
        throw SemanticException("La condicion del case debe ser Int o Char");


    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
}

void CasePNode::Interpret()
{
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->Interpret();
    }
}


string CasePNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<CasePNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation) + "</CasePNode>\n";

    return xml;
}
