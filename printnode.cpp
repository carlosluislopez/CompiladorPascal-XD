#include "printnode.h"

void PrintNode::ValidateSemantics()
{
    Value->ValidateSemantics();
}

void PrintNode::Interpret()
{
    //ExpresionValue *value = Value->Interpret();
    //cout<<value<<endl;
}


string PrintNode::ToXML(int identation)
{
    string xml = "";

    xml = util.getMeIdentation(identation);
    xml += "<PrintNode>\n";
    xml += Value->ToXML(identation + 1);
    xml += util.getMeIdentation(identation);
    xml += "</PrintNode>\n";

    return xml;
}
