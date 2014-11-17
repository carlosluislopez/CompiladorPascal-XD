#include "boolnode.h"

BoolNode::BoolNode()
{
}

BoolNode::~BoolNode()
{
}


BaseType * BoolNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * BoolNode::Interpret() const{
    return 0;
}

string BoolNode::ToXML(int identation){
    return "";
}
