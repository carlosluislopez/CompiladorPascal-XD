#include "fornode.h"

ForNode::ForNode()
{
}

ForNode::~ForNode()
{
}

void ForNode::ValidateSemantics() const
{
    Id->ValidateSemantics();
    InitialValue->ValidateSemantics();
    FinalValue->ValidateSemantics();
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
}

void ForNode::Interpret() const
{
}


string ForNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ForNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<IdNode>\n";
    xml += this->Id->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</IdNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<InitialValue>\n";
    xml += InitialValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</InitialValue>\n";

    xml += util.getMeIdentation(identation + 1) + "<FinalValue>\n";
    xml += FinalValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</FinalValue>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation) + "</ForNode>\n";

    return xml;
}
