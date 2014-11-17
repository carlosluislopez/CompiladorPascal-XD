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
    return "";
}
