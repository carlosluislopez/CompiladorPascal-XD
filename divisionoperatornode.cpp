#include "divisionoperatornode.h"

DivisionOperatorNode::DivisionOperatorNode()
{
}

DivisionOperatorNode::~DivisionOperatorNode()
{
}

BaseType * DivisionOperatorNode::ValidateSemantics() const{
    BaseType * leftType = LeftOperandNode->ValidateSemantics();
    BaseType * rightType = RightOperandNode->ValidateSemantics();

    if(leftType == 0 || rightType == 0)
        throw SemanticException("Para el operador '/' sus operandos deben estar definidos");

    if(!(leftType->type == BaseTypeInt || leftType->type == BaseTypeFloat))
        throw SemanticException("No se puede dividir tipos distintos a numeros");

    if(!(rightType->type == BaseTypeInt || rightType->type == BaseTypeFloat))
        throw SemanticException("No se puede dividir tipos distintos a numeros");

    return new FloatType();
}

ExpresionValue * DivisionOperatorNode::Interpret() const{
    return 0;
}

string DivisionOperatorNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DivisionOperatorNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</DivisionOperatorNode>\n";

    return xml;
}
