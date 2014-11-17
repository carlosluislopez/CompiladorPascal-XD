#include "divisionoperatornode.h"

DivisionOperatorNode::DivisionOperatorNode()
{
}

DivisionOperatorNode::~DivisionOperatorNode()
{
}


BaseType * DivisionOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * DivisionOperatorNode::Interpret() const{
    return 0;
}

string DivisionOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DivisionOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</DivisionOperatorNode>\n";

    return xml;
}
