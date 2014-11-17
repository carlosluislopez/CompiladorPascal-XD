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
    return "";
}
