#include "stringnode.h"

StringNode::StringNode()
{
}

StringNode::~StringNode()
{
}

BaseType * StringNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * StringNode::Interpret() const{
    return 0;
}

string StringNode::ToXML(int identation){
    return "";
}
