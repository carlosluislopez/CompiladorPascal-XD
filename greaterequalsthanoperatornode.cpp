#include "greaterequalsthanoperatornode.h"

GreaterEqualsThanOperatorNode::GreaterEqualsThanOperatorNode()
{
}

GreaterEqualsThanOperatorNode::~GreaterEqualsThanOperatorNode()
{
}

BaseType * GreaterEqualsThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * GreaterEqualsThanOperatorNode::Interpret() const{
    return 0;
}

string GreaterEqualsThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<GreaterEqualsThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</GreaterEqualsThanOperatorNode>\n";

    return xml;
}
