#include "substractoperatornode.h"

SubstractOperatorNode::SubstractOperatorNode()
{
}

SubstractOperatorNode::~SubstractOperatorNode()
{
}


BaseType * SubstractOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * SubstractOperatorNode::Interpret() const{
    return 0;
}

string SubstractOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<SubstractOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</SubstractOperatorNode>\n";

    return xml;
}
