#include "binarynode.h"

BinaryNode::BinaryNode()
{
}

BinaryNode::~BinaryNode()
{
}


BaseType * BinaryNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * BinaryNode::Interpret() const{
    return 0;
}

string BinaryNode::ToXML(int identation){
    return "";
}
