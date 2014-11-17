#include "equalsoperatornode.h"

EqualsOperatorNode::EqualsOperatorNode()
{
}

EqualsOperatorNode::~EqualsOperatorNode()
{
}


BaseType * EqualsOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * EqualsOperatorNode::Interpret() const{
    return 0;
}

string EqualsOperatorNode::ToXML(int identation){
    return "";
}
