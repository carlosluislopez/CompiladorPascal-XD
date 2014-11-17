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

    xml = util.getMeIdentation(identation) + "<IdNode>\n";
    xml += util.getMeIdentation(identation + 1) + Name + "\n";
    xml += util.getMeIdentation(identation) + "</IdNode>\n";

    return xml;
}
