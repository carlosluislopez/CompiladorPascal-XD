#include "equalsoperatornode.h"

EqualsOperatorNode::EqualsOperatorNode()
{
}

EqualsOperatorNode::~EqualsOperatorNode()
{
}


BaseType * EqualsOperatorNode::ValidateSemantics() const{
    return new BoolType();
}

ExpresionValue * EqualsOperatorNode::Interpret() const{
    return 0;
}

string EqualsOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<EqualsOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</EqualsOperatorNode>\n";

    return xml;
}
