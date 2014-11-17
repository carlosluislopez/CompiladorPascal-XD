#include "greaterthanoperatornode.h"

GreaterThanOperatorNode::GreaterThanOperatorNode()
{
}


GreaterThanOperatorNode::~GreaterThanOperatorNode()
{
}

BaseType * GreaterThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * GreaterThanOperatorNode::Interpret() const{
    return 0;
}

string GreaterThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<GreaterThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</GreaterThanOperatorNode>\n";

    return xml;
}
