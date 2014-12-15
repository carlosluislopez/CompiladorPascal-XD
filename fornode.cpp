#include "fornode.h"

ForNode::ForNode()
{
    Id = 0;
    InitialValue = 0;
    FinalValue = 0;
    Code = 0;
    Increment = true;
    symbolTable = SymbolTable::getInstance();
}

ForNode::~ForNode()
{
    delete Id;
    delete InitialValue;
    delete FinalValue;
    delete Code;
}

void ForNode::ValidateSemantics() const
{
    BaseType *IdType = Id->ValidateSemantics();
    BaseType *InitialType = InitialValue->ValidateSemantics();
    BaseType *FinalType = FinalValue->ValidateSemantics();

    if(IdType->type != BaseTypeInt)
        throw SemanticException("El Id debe ser tipo Entero");

    if(InitialType->type != BaseTypeInt)
        throw SemanticException("El valor inicial debe ser tipo Entero");

    if(FinalType->type != BaseTypeInt)
        throw SemanticException("El valor final debe ser tipo Entero");

    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
}

void ForNode::Interpret()
{
    ExpresionValue *initialValue = InitialValue->Interpret();
    ExpresionValue *finalValue = FinalValue->Interpret();

    Id->AssignValue(initialValue);
    int idValue = util.toIntFromString(symbolTable->getVariableValue(Id->Name)->ToString());
    int finalIntValue = util.toIntFromString(finalValue->ToString());

    if(Increment)
    {
        while(idValue <= finalIntValue){
            for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
            {
                StatementNode *sentence = *it;
                sentence->Interpret();
            }
            idValue++;
            Id->AssignValue(new IntValue(idValue));
        }
    }else{
        while(idValue >= finalIntValue){
            for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
            {
                StatementNode *sentence = *it;
                sentence->Interpret();
            }
            idValue--;
            Id->AssignValue(new IntValue(idValue));
        }
    }
}


string ForNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<ForNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<IdNode>\n";
    xml += this->Id->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</IdNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<InitialValue>\n";
    xml += InitialValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</InitialValue>\n";

    xml += util.getMeIdentation(identation + 1) + "<FinalValue>\n";
    xml += FinalValue->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</FinalValue>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation) + "</ForNode>\n";

    return xml;
}
