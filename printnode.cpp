#include "printnode.h"

PrintNode::PrintNode(){

}

PrintNode::~PrintNode(){

}

void PrintNode::ValidateSemantics() const
{
    Value->ValidateSemantics();
}

void PrintNode::Interpret()
{
    ExpresionValue *value = Value->Interpret();
    cout<<value->ToString()<<endl;
}


string PrintNode::ToXML(int identation)
{
    string xml = "";

    xml = util.getMeIdentation(identation) + "<PrintNode>\n";
    xml += Value->ToXML(identation + 1);
    xml += util.getMeIdentation(identation) + "</PrintNode>\n";

    return xml;
}
