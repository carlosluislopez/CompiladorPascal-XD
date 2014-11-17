#ifndef ASSIGNATIONNODE_H
#define ASSIGNATIONNODE_H

#include "StatementNode.h"
#include "idnode.h"

class AssignationNode : public StatementNode
{
public:
    AssignationNode();
    ~AssignationNode();
    void ValidateSemantics() const;
    void Interpret() const;
    string ToXML(int identation);

    IdNode *LeftValue;
    ExpresionNode *RightValue;
};

#endif // ASSIGNATIONNODE_H
