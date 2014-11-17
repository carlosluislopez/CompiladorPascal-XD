#include "expoperationnode.h"

ExpOperationNode::ExpOperationNode()
{
}

ExpOperationNode::~ExpOperationNode()
{
}

BaseType * ExpOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * ExpOperationNode::Interpret() const{
    return 0;
}

string ExpOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ExpOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</ExpOperationNode>\n";

    return xml;
}


