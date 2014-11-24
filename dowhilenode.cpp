#include "dowhilenode.h"

DoWhileNode::DoWhileNode()
{
    Code = 0;
    Condition = 0;
}

DoWhileNode::~DoWhileNode()
{
    delete Code;
    delete Condition;
}

void DoWhileNode::ValidateSemantics() const
{
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
