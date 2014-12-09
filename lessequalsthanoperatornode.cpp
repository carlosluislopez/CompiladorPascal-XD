#include "lessequalsthanoperatornode.h"

LessEqualsThanOperatorNode::LessEqualsThanOperatorNode()
{
}

LessEqualsThanOperatorNode::~LessEqualsThanOperatorNode()
{
}


BaseType * LessEqualsThanOperatorNode::ValidateSemantics() const{
    BaseType * leftTypeBaseType = LeftOperandNode->ValidateSemantics();
    BaseType * rightTypeBaseType = RightOperandNode->ValidateSemantics();

    if(!(leftTypeBaseType->type == BaseTypeInt ||
       leftTypeBaseType->type == BaseTypeFloat ||
       leftTypeBaseType->type == BaseTypeString ||
       leftTypeBaseType->type == BaseTypeChar ||
       leftTypeBaseType->type == BaseTypeBool
      ))
        throw SemanticException("Esta tratando de comparar tipos invalidos");

    if(!(rightTypeBaseType->type == BaseTypeInt ||
       rightTypeBaseType->type == BaseTypeFloat ||
       rightTypeBaseType->type == BaseTypeString ||
       rightTypeBaseType->type == BaseTypeChar ||
       rightTypeBaseType->type == BaseTypeBool
      ))
        throw SemanticException("Esta tratando de comparar tipos invalidos");

    return new BoolType();
}

ExpresionValue * LessEqualsThanOperatorNode::Interpret() const{
    return 0;
}

string LessEqualsThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<LessEqualsThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</LessEqualsThanOperatorNode>\n";

    return xml;
}
