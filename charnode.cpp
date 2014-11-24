#include "charnode.h"

CharNode::CharNode()
{
}

CharNode::~CharNode()
{
}


BaseType * CharNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * CharNode::Interpret() const{
    return 0;
}

string CharNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<CharNode>\n";
    xml += util.getMeIdentation(identation + 1) + Value + "\n";
    xml += util.getMeIdentation(identation) + "</CharNode>\n";

    return xml;
}
