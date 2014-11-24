#include "multiplyoperatornode.h"

MultiplyOperatorNode::MultiplyOperatorNode()
{
    LeftOperandNode = 0;
    RightOperandNode = 0;
}

MultiplyOperatorNode::~MultiplyOperatorNode()
{
    delete LeftOperandNode;
    delete RightOperandNode;
}

BaseType * MultiplyOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * MultiplyOperatorNode::Interpret() const{
    return 0;
}

string MultiplyOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<MultiplyOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</MultiplyOperatorNode>\n";

    return xml;
}
