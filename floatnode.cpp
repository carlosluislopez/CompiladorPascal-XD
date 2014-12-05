#include "floatnode.h"

FloatNode::FloatNode()
{
}

FloatNode::~FloatNode()
{
}


BaseType * FloatNode::ValidateSemantics() const{
    return new FloatType();
}

ExpresionValue * FloatNode::Interpret() const{
    return 0;
}

string FloatNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<FloatNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</FloatNode>\n";

    return xml;
}
