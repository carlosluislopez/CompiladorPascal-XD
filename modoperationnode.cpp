#include "modoperationnode.h"

ModOperationNode::ModOperationNode()
{
}

ModOperationNode::~ModOperationNode()
{
}



BaseType * ModOperationNode::ValidateSemantics() const{
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

ExpresionValue * ModOperationNode::Interpret(){
    return 0;
}

string ModOperationNode::ToXML(int identation){
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ModOperationNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<LeftOperandNode>\n";
    xml += LeftOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</LeftOperandNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<RightOperandNode>\n";
    xml += RightOperandNode->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</RightOperandNode>\n";

    xml += util.getMeIdentation(identation) + "</ModOperationNode>\n";

    return xml;
}
