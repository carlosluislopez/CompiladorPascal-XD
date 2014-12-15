#include "boolnode.h"

BoolNode::BoolNode()
{
}

BoolNode::~BoolNode()
{
}


BaseType * BoolNode::ValidateSemantics() const{
    return new BoolType();
}

ExpresionValue * BoolNode::Interpret(){
    return new BoolValue(util.toBoolFromString(Value));
}

string BoolNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<BoolNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</BoolNode>\n";

    return xml;
}
