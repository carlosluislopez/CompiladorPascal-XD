#include "fieldaccesor.h"

FieldAccesor::FieldAccesor()
{
}


FieldAccesor::~FieldAccesor(){}

BaseType *FieldAccesor::ValidateSemantics(BaseType *sourceType) const
{
    return 0;
}

string FieldAccesor::ToXML(int identation)
{
    string xml = "";
    xml += util.getMeIdentation(identation);

    xml += "<FieldAccesor>";
    xml += Id;
    xml += "</FieldAccesor>\n";
    return xml;
}
