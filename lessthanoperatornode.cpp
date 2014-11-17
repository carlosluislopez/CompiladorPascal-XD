#include "lessthanoperatornode.h"

LessThanOperatorNode::LessThanOperatorNode()
{
}

LessThanOperatorNode::~LessThanOperatorNode()
{
}


BaseType * LessThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * LessThanOperatorNode::Interpret() const{
    return 0;
}

string LessThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<LessThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</LessThanOperatorNode>\n";

    return xml;
}
