#include "notoperatornode.h"

NotOperatorNode::NotOperatorNode()
{
    OperandNode = 0;
}

NotOperatorNode::~NotOperatorNode()
{
    delete OperandNode;
}
