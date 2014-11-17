#include "intnode.h"

IntNode::IntNode()
{
}

IntNode::~IntNode()
{
}


BaseType * IntNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * IntNode::Interpret() const{
    return 0;
}

string IntNode::ToXML(int identation){
    return "";
}
