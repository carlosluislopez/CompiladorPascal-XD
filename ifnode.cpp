#include "ifnode.h"

IfNode::IfNode()
{
    Condition = 0;
    Code = 0;
    CodeElse = 0;
}

IfNode::~IfNode()
{
    delete Condition;
    delete Code;
    delete CodeElse;
}

void IfNode::ValidateSemantics() const
{
    BaseType *typeCondition = Condition->ValidateSemantics();
    if(typeCondition->type == BaseTypeBool)
        throw SemanticException("La condicion debe ser una expresion boleana");

    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }

    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
}

void IfNode::Interpret()
{
    ExpresionValue *conditionValue = Condition->Interpret();
    bool result = util.toBoolFromString(conditionValue->ToString());
    if(result)
    {
        if(Code == 0)
            return;
        for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
        {
            StatementNode *sentence = *it;
            sentence->Interpret();
        }
    }else{
        if(CodeElse == 0)
            return;
        for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
        {
            StatementNode *sentence = *it;
            sentence->Interpret();
        }
    }
}


string IfNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<IfNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation + 1) + "<CodeElse>\n";
    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</CodeElse>\n";

    xml += util.getMeIdentation(identation) + "</IfNode>\n";

    return xml;
}
