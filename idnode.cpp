#include "idnode.h"

IdNode::IdNode()
{
    symbolTable = SymbolTable::getInstance();
}


IdNode::~IdNode()
{
}

BaseType * IdNode::ValidateSemantics() const
{
    BaseType *type = symbolTable->getVariableType(Name);
    if(type == 0)
        throw SemanticException("No esta definido el Id: '" + Name +"';");
    return type;
}

ExpresionValue * IdNode::Interpret()
{
    return symbolTable->getVariableValue(Name);
}

void IdNode::AssignValue(ExpresionValue *value){
    symbolTable->setValueVariable(Name, value);
}

string IdNode::ToXML(int identation)
{
    string xml = "";

    xml = util.getMeIdentation(identation) + "<IdNode>\n";
    xml += util.getMeIdentation(identation + 1) + Name + "\n";
    xml += util.getMeIdentation(identation) + "</IdNode>\n";

    return xml;
}
