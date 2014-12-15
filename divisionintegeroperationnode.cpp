#include "divisionintegeroperationnode.h"

DivisionIntegerOperationNode::DivisionIntegerOperationNode()
{
}

DivisionIntegerOperationNode::~DivisionIntegerOperationNode()
{
}

BaseType * DivisionIntegerOperationNode::ValidateSemantics() const{
    BaseType * leftType = LeftOperandNode->ValidateSemantics();
    BaseType * rightType = RightOperandNode->ValidateSemantics();

    if(leftType == 0 || rightType == 0)
        throw SemanticException("Para el operador 'div' sus operandos deben estar definidos");

    if(!(leftType->type == BaseTypeInt && rightType->type == BaseTypeInt))
        throw SemanticException("No se puede dividir tipos distintos a entero");

    return new IntType();
}

ExpresionValue * DivisionIntegerOperationNode::Interpret(){
    ExpresionValue *leftValue = LeftOperandNode->Interpret();
    ExpresionValue *rightValue = RightOperandNode->Interpret();

    int result = util.toIntFromString(leftValue->ToString()) / util.toIntFromString(rightValue->ToString());

    return new IntValue(result);
}

string DivisionIntegerOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DivisionIntegerOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</DivisionIntegerOperationNode>\n";

    return xml;
}
