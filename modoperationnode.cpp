#include "modoperationnode.h"

ModOperationNode::ModOperationNode()
{
}

ModOperationNode::~ModOperationNode()
{
}



BaseType * ModOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * ModOperationNode::Interpret() const{
    return 0;
}

string ModOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ModOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</ModOperationNode>\n";

    return xml;
}
