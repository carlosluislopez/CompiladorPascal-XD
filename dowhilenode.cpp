#include "dowhilenode.h"

DoWhileNode::DoWhileNode()
{
}

DoWhileNode::~DoWhileNode()
{
}

void DoWhileNode::ValidateSemantics() const
{
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
    Condition->ValidateSemantics();
}

void DoWhileNode::Interpret() const
{
}


string DoWhileNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DoWhileNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation) + "</DoWhileNode>\n";

    return xml;
}
