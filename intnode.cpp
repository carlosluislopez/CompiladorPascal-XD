#include "intnode.h"

IntNode::IntNode()
{
}

IntNode::~IntNode()
{
}


BaseType * IntNode::ValidateSemantics() const{
    return new IntType();
}

ExpresionValue * IntNode::Interpret() const{
    return 0;
}

string IntNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<IntNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</IntNode>\n";

    return xml;
}
