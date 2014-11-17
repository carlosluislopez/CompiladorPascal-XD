#include "greaterthanoperatornode.h"

GreaterThanOperatorNode::GreaterThanOperatorNode()
{
}


GreaterThanOperatorNode::~GreaterThanOperatorNode()
{
}

BaseType * GreaterThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * GreaterThanOperatorNode::Interpret() const{
    return 0;
}

string GreaterThanOperatorNode::ToXML(int identation){
    return "";
}
