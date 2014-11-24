#include "equalsoperatornode.h"

EqualsOperatorNode::EqualsOperatorNode()
{
    LeftOperandNode = 0;
    RightOperandNode = 0;
}

EqualsOperatorNode::~EqualsOperatorNode()
{
    delete LeftOperandNode;
    delete RightOperandNode;
}


BaseType * EqualsOperatorNode::ValidateSemantics() const{
    return 0;
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
