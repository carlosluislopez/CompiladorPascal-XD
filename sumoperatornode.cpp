#include "sumoperatornode.h"

SumOperatorNode::SumOperatorNode()
{
}

SumOperatorNode::~SumOperatorNode()
{
}

BaseType * SumOperatorNode::ValidateSemantics() const{
    BaseType * leftType = LeftOperandNode->ValidateSemantics();
    BaseType * rightType = RightOperandNode->ValidateSemantics();

    if(leftType == 0 || rightType == 0)
        throw SemanticException("Para el operador '+' sus operandos deben estar definidos");

    if(!(leftType->type == BaseTypeInt || leftType->type == BaseTypeFloat || leftType->type == BaseTypeString))
        throw SemanticException("Solo se puede usar el operador '+' en numeros y cadenas");

    if(!(rightType->type == BaseTypeInt || rightType->type == BaseTypeFloat || rightType->type == BaseTypeString))
        throw SemanticException("Solo se puede usar el operador '+' en numeros y cadenas");

    if(leftType->type == BaseTypeString || rightType->type == BaseTypeString)
        return new StringType();

    if((leftType->type == rightType->type) && (leftType->type == BaseTypeInt || leftType->type == BaseTypeFloat))
        return leftType;

    if((leftType->type != rightType->type))
        return new FloatType();

    throw SemanticException("No se puede sumar tipos distintos a numeros");
}

ExpresionValue * SumOperatorNode::Interpret() const{
    return 0;
}

string SumOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<SumOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</SumOperatorNode>\n";

    return xml;
}
