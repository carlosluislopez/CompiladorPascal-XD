#include "expoperationnode.h"

ExpOperationNode::ExpOperationNode()
{
}

ExpOperationNode::~ExpOperationNode()
{
}

BaseType * ExpOperationNode::ValidateSemantics() const{
    BaseType * leftType = LeftOperandNode->ValidateSemantics();
    BaseType * rightType = RightOperandNode->ValidateSemantics();

    if(leftType == 0 || rightType == 0)
        throw SemanticException("Para el operador 'exp' sus operandos deben estar definidos");

    if(!(leftType->type == BaseTypeInt || leftType->type == BaseTypeFloat))
        throw SemanticException("No se puede elevar tipos distintos a numeros");

    if(!(rightType->type == BaseTypeInt || rightType->type == BaseTypeFloat))
        throw SemanticException("No se puede elevar tipos distintos a numeros");

    if((leftType->type == rightType->type) && (leftType->type == BaseTypeInt || leftType->type == BaseTypeFloat))
        return leftType;

    if((leftType->type != rightType->type))
        return new FloatType();

    throw SemanticException("No se puede elevar tipos distintos a numeros");
}

ExpresionValue * ExpOperationNode::Interpret() const{
    return 0;
}

string ExpOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ExpOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</ExpOperationNode>\n";

    return xml;
}


