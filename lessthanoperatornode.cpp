#include "lessthanoperatornode.h"

LessThanOperatorNode::LessThanOperatorNode()
{
}

LessThanOperatorNode::~LessThanOperatorNode()
{
}


BaseType * LessThanOperatorNode::ValidateSemantics() const{
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

    if(leftTypeBaseType->type != rightTypeBaseType->type)
        throw SemanticException("Esta tratando de comparar tipos invalidos");

    return new BoolType();
}

ExpresionValue * LessThanOperatorNode::Interpret(){
    ExpresionValue *leftValue = LeftOperandNode->Interpret();
    ExpresionValue *rightValue = RightOperandNode->Interpret();

    BaseType * leftTypeBaseType = LeftOperandNode->ValidateSemantics();
    int result = false;
    if(leftTypeBaseType->type == BaseTypeInt)
        result = (util.toIntFromString(leftValue->ToString()) < util.toIntFromString(rightValue->ToString()));

    if(leftTypeBaseType->type == BaseTypeFloat)
        result = (util.toFloatFromString(leftValue->ToString()) < util.toFloatFromString(rightValue->ToString()));

    if(leftTypeBaseType->type == BaseTypeString)
        result = (leftValue->ToString() < rightValue->ToString());

    if(leftTypeBaseType->type == BaseTypeChar)
        result = (leftValue->ToString().c_str()[0] < rightValue->ToString().c_str()[0]);

    if(leftTypeBaseType->type == BaseTypeBool)
        result = (util.toBoolFromString(leftValue->ToString()) < util.toBoolFromString(rightValue->ToString()));

    return new BoolValue(result);
}

string LessThanOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<LessThanOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</LessThanOperatorNode>\n";

    return xml;
}
