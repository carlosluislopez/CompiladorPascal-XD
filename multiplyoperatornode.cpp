#include "multiplyoperatornode.h"

MultiplyOperatorNode::MultiplyOperatorNode()
{
}

MultiplyOperatorNode::~MultiplyOperatorNode()
{
}

BaseType * MultiplyOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * MultiplyOperatorNode::Interpret() const{
    return 0;
}

string MultiplyOperatorNode::ToXML(int identation){
    return "";
    this->LeftOperandNode = 0;
}
