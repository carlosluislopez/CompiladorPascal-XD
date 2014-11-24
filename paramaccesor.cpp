#include "paramaccesor.h"

ParamAccesor::ParamAccesor()
{
    Params = 0;
}

ParamAccesor::~ParamAccesor()
{
    delete Params;
}

BaseType *ParamAccesor::ValidateSemantics(BaseType *sourceType) const
{
    return 0;
}

string ParamAccesor::ToXML(int identation)
{
    string xml = "";
    xml += util.getMeIdentation(identation) + "<ParamAccesor>\n";

    xml += util.getMeIdentation(identation + 1) + "<Params>\n";
    for(std::list<ExpresionNode*>::iterator it = Params->begin(); it != Params->end(); it++)
    {
        ExpresionNode *expresion = *it;
        xml += expresion->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Params>\n";

    xml += util.getMeIdentation(identation) + "</ParamAccesor>\n";
    return xml;
}
