#include "sumoperatornode.h"

SumOperatorNode::SumOperatorNode()
{
}

SumOperatorNode::~SumOperatorNode()
{
}

BaseType * SumOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * SumOperatorNode::Interpret() const{
    return 0;
}

string SumOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<SumOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</SumOperatorNode>\n";

    return xml;
}
