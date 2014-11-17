#include "lessequalsthanoperatornode.h"

LessEqualsThanOperatorNode::LessEqualsThanOperatorNode()
{
}

LessEqualsThanOperatorNode::~LessEqualsThanOperatorNode()
{
}


BaseType * LessEqualsThanOperatorNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * LessEqualsThanOperatorNode::Interpret() const{
    return 0;
}

string LessEqualsThanOperatorNode::ToXML(int identation){
    return "";
}
