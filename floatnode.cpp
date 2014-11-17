#include "floatnode.h"

FloatNode::FloatNode()
{
}

FloatNode::~FloatNode()
{
}


BaseType * FloatNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * FloatNode::Interpret() const{
    return 0;
}

string FloatNode::ToXML(int identation){
    return "";
}
