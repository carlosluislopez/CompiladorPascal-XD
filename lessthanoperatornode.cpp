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
    return "";
}
