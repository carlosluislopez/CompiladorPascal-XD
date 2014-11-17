#include "arrayaccesor.h"

ArrayAccesor::ArrayAccesor()
{
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
    xml += util.getMeIdentation(identation);
    xml += "<ArrayAccesor>\n";
    xml += util.getMeIdentation(identation);

//    for (std::list<ExpresionNode*>::iterator it = Indexes->begin(); it != Indexes->end(); it++)
//    {
//        xml += ((ExpresionNode*)it)->ToXML(identation + 1);
//    }

    xml += util.getMeIdentation(identation);
    xml += "</ArrayAccesor>\n";
    return xml;
}
