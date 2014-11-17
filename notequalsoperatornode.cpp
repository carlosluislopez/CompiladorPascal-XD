#include "notequalsoperatornode.h"

NotEqualsOperatorNode::NotEqualsOperatorNode()
{
}

NotEqualsOperatorNode::~NotEqualsOperatorNode()
{
}

BaseType * NotEqualsOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * NotEqualsOperatorNode::Interpret() const{
    return 0;
}

string NotEqualsOperatorNode::ToXML(int identation){
    return "";
}
