#ifndef BINARYOPERATORNODE_H
#define BINARYOPERATORNODE_H


#include "ExpresionNode.h"
#include "Types.h"


using namespace std;

class BinaryOperatorNode : public ExpresionNode
{
public:
    ExpresionNode *LeftOperandNode;
    ExpresionNode *RightOperandNode;
};

#endif // BINARYOPERATORNODE_H
