#ifndef PRINTNODE_H
#define PRINTNODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"
#include <iostream>

using namespace std;

class PrintNode: public StatementNode
{
public:
    ExpresionNode *Value;
    void ValidateSemantics();
    void Interpret();

};
#endif // PRINTNODE_H
