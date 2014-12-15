#include "dowhilenode.h"

DoWhileNode::DoWhileNode()
{
    Condition = 0;
    Code = 0;
}

DoWhileNode::~DoWhileNode()
{
    delete Condition;
    delete Code;
}

void DoWhileNode::ValidateSemantics() const
{
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
    BaseType *typeCondition = Condition->ValidateSemantics();
    if(typeCondition->type != BaseTypeBool)
        throw SemanticException("La condicion debe ser una Expresion Boleana");
}

void DoWhileNode::Interpret()
{
    ExpresionValue *conditionValue = Condition->Interpret();
    bool result = util.toBoolFromString(conditionValue->ToString());
    do
    {
        for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
        {
            StatementNode *sentence = *it;
            sentence->Interpret();
        }
        conditionValue = Condition->Interpret();
        result = util.toBoolFromString(conditionValue->ToString());
    }while(result);
}


string DoWhileNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<DoWhileNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Code>\n";
    for(std::list<StatementNode*>::iterator it = Code->begin(); it != Code->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Code>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation) + "</DoWhileNode>\n";

    return xml;
}
