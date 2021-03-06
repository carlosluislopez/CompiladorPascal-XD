#include "assignationnode.h"


AssignationNode::AssignationNode()
{
    LeftValue = 0;
    RightValue = 0;
}

AssignationNode::~AssignationNode()
{
    delete LeftValue;
    delete RightValue;
}

void AssignationNode::ValidateSemantics() const
{
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
