#include "charnode.h"

CharNode::CharNode()
{
}

CharNode::~CharNode()
{
}


BaseType * CharNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * CharNode::Interpret() const{
    return 0;
}

string CharNode::ToXML(int identation){
    return "";
}
