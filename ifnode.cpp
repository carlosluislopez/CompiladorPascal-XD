#include "ifnode.h"

IfNode::IfNode()
{
}

IfNode::~IfNode()
{
}

void IfNode::ValidateSemantics() const
{
}

void IfNode::Interpret() const
{
}


string IfNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<IfNode>\n";

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

    xml += util.getMeIdentation(identation + 1) + "<CodeElse>\n";
    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</CodeElse>\n";

    xml += util.getMeIdentation(identation) + "</IfNode>\n";

    return xml;
}
