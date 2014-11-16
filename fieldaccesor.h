#ifndef FIELDACCESOR_H
#define FIELDACCESOR_H

#include "Accesor.h"

class FieldAccesor : public Accesor
{
public:
    FieldAccesor();
    ~FieldAccesor();
    BaseType *ValidateSemantics(BaseType *sourceType) const;
    string ToXML(int identation);
    string Id;
};

#endif // FIELDACCESOR_H
