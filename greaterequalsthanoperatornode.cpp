#include "greaterequalsthanoperatornode.h"

GreaterEqualsThanOperatorNode::GreaterEqualsThanOperatorNode()
{
}

GreaterEqualsThanOperatorNode::~GreaterEqualsThanOperatorNode()
{
}

BaseType * GreaterEqualsThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * GreaterEqualsThanOperatorNode::Interpret() const{
    return 0;
}

string GreaterEqualsThanOperatorNode::ToXML(int identation){
    return "";
}
