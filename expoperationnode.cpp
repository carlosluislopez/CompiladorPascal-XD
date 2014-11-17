#include "expoperationnode.h"

ExpOperationNode::ExpOperationNode()
{
}

ExpOperationNode::~ExpOperationNode()
{
}

BaseType * ExpOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * ExpOperationNode::Interpret() const{
    return 0;
}

string ExpOperationNode::ToXML(int identation){
    return "";
}


