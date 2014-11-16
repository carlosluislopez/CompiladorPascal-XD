#ifndef ARRAYACCESOR_H
#define ARRAYACCESOR_H

#include "Accesor.h"
#include "ExpresionNode.h"

class ArrayAccesor : public Accesor
{
public:
    ArrayAccesor();
    ~ArrayAccesor();
    BaseType *ValidateSemantics(BaseType *sourceType) const;
    string ToXML(int identation);
    list<ExpresionNode*> *Indexes;
};

#endif // ARRAYACCESOR_H
