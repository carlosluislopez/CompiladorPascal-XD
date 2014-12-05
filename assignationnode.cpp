#include "assignationnode.h"


AssignationNode::AssignationNode()
{
}

AssignationNode::~AssignationNode()
{
}

void AssignationNode::ValidateSemantics() const
{
    LeftValue->ValidateSemantics();
    RightValue->ValidateSemantics();
}

void AssignationNode::Interpret() const
{
}


string AssignationNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<AssignationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftValue>\n";
    xml += LeftValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftValue>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightValue>\n";
    xml += RightValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightValue>\n";

    xml += util.getMeIdentation(identation) + "</AssignationNode>\n";

    return xml;
}
