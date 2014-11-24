#include "printnode.h"

PrintNode::PrintNode()
{
    Value = 0;
}

PrintNode::~PrintNode(){
    delete Value;
}

void PrintNode::ValidateSemantics() const
{
}

void PrintNode::Interpret() const
{
}


string PrintNode::ToXML(int identation)
{
    string xml = "";

    xml = util.getMeIdentation(identation) + "<PrintNode>\n";
    xml += Value->ToXML(identation + 1);
    xml += util.getMeIdentation(identation) + "</PrintNode>\n";

    return xml;
}
