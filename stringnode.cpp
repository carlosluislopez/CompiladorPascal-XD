#include "stringnode.h"

StringNode::StringNode()
{
}

StringNode::~StringNode()
{
}

BaseType * StringNode::ValidateSemantics() const{
    return new StringType();
}

ExpresionValue * StringNode::Interpret() const{
    return 0;
}

string StringNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<StringNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</StringNode>\n";

    return xml;
}
