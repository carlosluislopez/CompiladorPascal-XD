#ifndef STATEMENTNODE_H
#define STATEMENTNODE_H

class StatementNode
{
public:
    StatementNode() {}
    ~StatementNode() {}
    virtual void ValidateSemantics() = 0;
    virtual void Interpret() = 0;
};

#endif // STATEMENTNODE_H
