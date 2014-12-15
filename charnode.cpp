#include "charnode.h"

CharNode::CharNode()
{
}

CharNode::~CharNode()
{
}


BaseType * CharNode::ValidateSemantics() const{
    return new CharType();
}

ExpresionValue * CharNode::Interpret()
{
    return new CharValue(Value.c_str()[0]);
}

string CharNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<CharNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</CharNode>\n";

    return xml;
}
