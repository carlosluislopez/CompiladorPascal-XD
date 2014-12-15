#include "hexadecimalnode.h"

HexadecimalNode::HexadecimalNode()
{
}

HexadecimalNode::~HexadecimalNode()
{
}


BaseType * HexadecimalNode::ValidateSemantics() const{
    return 0;
}

ExpresionValue * HexadecimalNode::Interpret(){
    return 0;
}

string HexadecimalNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation);
    xml += "<HexadecimalNode>\n";
    xml += util.getMeIdentation(identation + 1);
    xml += Value + "\n";
    xml += util.getMeIdentation(identation);
    xml += "</HexadecimalNode>\n";

    return xml;
}
