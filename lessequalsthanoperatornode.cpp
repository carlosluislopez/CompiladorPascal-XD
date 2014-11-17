#include "lessequalsthanoperatornode.h"

LessEqualsThanOperatorNode::LessEqualsThanOperatorNode()
{
}

LessEqualsThanOperatorNode::~LessEqualsThanOperatorNode()
{
}


BaseType * LessEqualsThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * LessEqualsThanOperatorNode::Interpret() const{
    return 0;
}

string LessEqualsThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<LessEqualsThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</LessEqualsThanOperatorNode>\n";

    return xml;
}
