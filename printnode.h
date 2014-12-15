#ifndef PRINTNODE_H
#define PRINTNODE_H

#include "StatementNode.h"
#include "ExpresionNode.h"

using namespace std;

class PrintNode: public StatementNode
{
public:
    PrintNode();
    ~PrintNode();
    ExpresionNode *Value;
    void ValidateSemantics() const;
    void Interpret();
    string ToXML(int identation);
};
#endif // PRINTNODE_H
