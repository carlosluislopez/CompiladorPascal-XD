#include "unaryoperator.h"

UnaryOperator::UnaryOperator()
{
}

UnaryOperator::~UnaryOperator()
{
}

BaseType * UnaryOperator::ValidateSemantics() const{
    BaseType *leftType = OperandNode->ValidateSemantics();
    if(leftType->type != BaseTypeBool)
        throw SemanticException("Solo se puede negar boleanos");

    return new BoolType();
}

ExpresionValue * UnaryOperator::Interpret() const{
    return 0;
}

string UnaryOperator::ToXML(int identation){
    string xml = "";
    xml = util.getMeIdentation(identation) + "<UnaryOperator>\n";
    xml += OperandNode->ToXML(identation + 1);
    xml += util.getMeIdentation(identation) + "</UnaryOperator>\n";

    return xml;
}
