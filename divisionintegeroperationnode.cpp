#include "divisionintegeroperationnode.h"

DivisionIntegerOperationNode::DivisionIntegerOperationNode()
{
}

DivisionIntegerOperationNode::~DivisionIntegerOperationNode()
{
}

BaseType * DivisionIntegerOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * DivisionIntegerOperationNode::Interpret() const{
    return 0;
}

string DivisionIntegerOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DivisionIntegerOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</DivisionIntegerOperationNode>\n";

    return xml;
}
