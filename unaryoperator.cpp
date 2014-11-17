#include "unaryoperator.h"

UnaryOperator::UnaryOperator()
{
}

UnaryOperator::~UnaryOperator()
{
}

BaseType * UnaryOperator::ValidateSemantics() const{
    return 0;
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
