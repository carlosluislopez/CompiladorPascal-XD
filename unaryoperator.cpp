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
    return "";
}
