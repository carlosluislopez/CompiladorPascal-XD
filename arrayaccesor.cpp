#include "arrayaccesor.h"

ArrayAccesor::ArrayAccesor()
{
    Indexes = 0;
}

ArrayAccesor::~ArrayAccesor()
{
    delete this->Indexes;
}

BaseType *ArrayAccesor::ValidateSemantics(BaseType *sourceType) const
{
    return 0;
}

string ArrayAccesor::ToXML(int identation)
{
    string xml = "";
    xml += util.getMeIdentation(identation) + "<ArrayAccesor>\n";

    xml += util.getMeIdentation(identation + 1) + "<Indexes>\n";
    for (std::list<ExpresionNode*>::iterator it = Indexes->begin(); it != Indexes->end(); it++)
    {
        ExpresionNode *expresion = *it;
        xml += expresion->ToXML(identation + 1);
    }
    xml += util.getMeIdentation(identation + 1) + "</Indexes>\n";

    xml += util.getMeIdentation(identation) + "</ArrayAccesor>\n";
    return xml;
}
