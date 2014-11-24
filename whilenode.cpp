#include "whilenode.h"

WhileNode::WhileNode()
{
}

WhileNode::~WhileNode()
{
    Condition = 0;
    Code = 0;
}

void WhileNode::ValidateSemantics() const
{
    delete Condition;
    delete Code;
}

void WhileNode::Interpret() const
{
}


string WhileNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<WhileNode>\n";

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

    xml += util.getMeIdentation(identation) + "</WhileNode>\n";

    return xml;
}
