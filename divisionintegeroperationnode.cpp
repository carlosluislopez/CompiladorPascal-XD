#include "divisionintegeroperationnode.h"

DivisionIntegerOperationNode::DivisionIntegerOperationNode()
{
}

DivisionIntegerOperationNode::~DivisionIntegerOperationNode()
{
}

BaseType * DivisionIntegerOperationNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * DivisionIntegerOperationNode::Interpret() const{
    return 0;
}

string DivisionIntegerOperationNode::ToXML(int identation){
    return "";
}
