#include "boolnode.h"

BoolNode::BoolNode()
{
}

BoolNode::~BoolNode()
{
}


BaseType * BoolNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * BoolNode::Interpret() const{
    return 0;
}

string BoolNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<BoolNode>\n";
    xml += util.getMeIdentation(identation + 1) + Value + "\n";
    xml += util.getMeIdentation(identation) + "</BoolNode>\n";

    return xml;
}
