#include "intnode.h"

IntNode::IntNode()
{
}

IntNode::~IntNode()
{
}


BaseType * IntNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * IntNode::Interpret() const{
    return 0;
}

string IntNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<IntNode>\n";
    xml += util.getMeIdentation(identation + 1) + Value + "\n";
    xml += util.getMeIdentation(identation) + "</IntNode>\n";

    return xml;
}
