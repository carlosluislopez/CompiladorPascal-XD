#include "sumoperatornode.h"

SumOperatorNode::SumOperatorNode()
{
}

SumOperatorNode::~SumOperatorNode()
{
}

BaseType * SumOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * SumOperatorNode::Interpret() const{
    return 0;
}

string SumOperatorNode::ToXML(int identation){
    return "";
}
