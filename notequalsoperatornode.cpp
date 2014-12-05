#include "notequalsoperatornode.h"

NotEqualsOperatorNode::NotEqualsOperatorNode()
{
}

NotEqualsOperatorNode::~NotEqualsOperatorNode()
{
}

BaseType * NotEqualsOperatorNode::ValidateSemantics() const{
    return new BoolType();
}

ExpresionValue * NotEqualsOperatorNode::Interpret() const{
    return 0;
}

string NotEqualsOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<NotEqualsOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</NotEqualsOperatorNode>\n";

    return xml;
}
