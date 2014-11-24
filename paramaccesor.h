#ifndef PARAMACCESOR_H
#define PARAMACCESOR_H

#include "Accesor.h"
#include "ExpresionNode.h"

class ParamAccesor : public Accesor
{
public:
    ParamAccesor();
    ~ParamAccesor();
    BaseType *ValidateSemantics(BaseType *sourceType) const;
    string ToXML(int identation);
    list<ExpresionNode*> *Params;
};

#endif // PARAMACCESOR_H
