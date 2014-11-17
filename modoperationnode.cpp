#include "modoperationnode.h"

ModOperationNode::ModOperationNode()
{
}

ModOperationNode::~ModOperationNode()
{
}



BaseType * ModOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * ModOperationNode::Interpret() const{
    return 0;
}

string ModOperationNode::ToXML(int identation){
    return "";
    this->LeftOperandNode = 0;
}
