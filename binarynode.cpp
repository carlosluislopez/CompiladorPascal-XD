#include "binarynode.h"

BinaryNode::BinaryNode()
{
}

BinaryNode::~BinaryNode()
{
}


BaseType * BinaryNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * BinaryNode::Interpret() const{
    return 0;
}

string BinaryNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<BoolNode>\n";
    xml += util.getMeIdentation(identation + 1) + Value + "\n";
    xml += util.getMeIdentation(identation) + "</BoolNode>\n";

    return xml;
}
