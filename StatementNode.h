#ifndef STATEMENTNODE_H
#define STATEMENTNODE_H

#include <string>
#include "utileria.h"

using namespace std;

class StatementNode
{
public:
    virtual void ValidateSemantics() const = 0;
    virtual void Interpret() const = 0;
    virtual string ToXML(int identation) = 0;
    Utileria util;
};


#endif // STATEMENTNODE_H
