#include "idnode.h"

IdNode::IdNode()
{
}


IdNode::~IdNode()
{
}

BaseType * IdNode::ValidateSemantics() const
{
    return 0;
}

ExpresionValue * IdNode::Interpret() const
{
    return 0;
}

string IdNode::ToXML(int identation)
{
    string xml = "";

    xml = util.getMeIdentation(identation);
    xml += "<IdNode>";
    xml += Name;
    xml += util.getMeIdentation(identation);
    xml += "</IdNode>\n";

    return xml;
}
