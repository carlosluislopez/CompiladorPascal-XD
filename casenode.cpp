#include "casenode.h"

CaseNode::CaseNode()
{
    Condition = 0;
    CaseList = 0;
    CodeElse = 0;
}

CaseNode::~CaseNode()
{
    delete Condition;
    delete CaseList;
    delete CodeElse;
}


void CaseNode::ValidateSemantics() const
{
    BaseType *typeCondition = Condition->ValidateSemantics();
    if(!(typeCondition->type == BaseTypeInt || typeCondition->type == BaseTypeChar))
        throw SemanticException("La condicion del case debe ser Int o Char");

    for(std::list<CasePNode*>::iterator it = CaseList->begin(); it != CaseList->end(); it++)
    {
        CasePNode *caseP = *it;
        if(typeCondition->type != caseP->Condition->ValidateSemantics()->type)
            throw SemanticException("Las condiciones de cada caso deben ser del mismo tipo");
        caseP->ValidateSemantics();
    }

    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->ValidateSemantics();
    }
}

void CaseNode::Interpret()
{
    BaseType *typeCondition = Condition->ValidateSemantics();
    ExpresionValue *conditionValue = Condition->Interpret();

    for(std::list<CasePNode*>::iterator it = CaseList->begin(); it != CaseList->end(); it++)
    {
        CasePNode *caseP = *it;
        ExpresionValue *casepValue = caseP->Condition->Interpret();
        if(typeCondition->type == BaseTypeInt)
        {
            if(util.toIntFromString(casepValue->ToString()) == util.toIntFromString(conditionValue->ToString()))
            {
                caseP->Interpret();
                return;
            }
        }

        if(typeCondition->type == BaseTypeChar)
        {
            if(casepValue->ToString()[0] == conditionValue->ToString()[0])
            {
                caseP->Interpret();
                return;
            }
        }
    }

    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        sentence->Interpret();
    }
}


string CaseNode::ToXML(int identation)
{
    string xml = "";

    xml += util.getMeIdentation(identation) + "<CaseNode>\n";

    xml += util.getMeIdentation(identation + 1) + "<Condition>\n";
    xml += this->Condition->ToXML(identation + 2);
    xml += util.getMeIdentation(identation + 1) + "</Condition>\n";

    xml += util.getMeIdentation(identation + 1) + "<Case>\n";
    for(std::list<CasePNode*>::iterator it = CaseList->begin(); it != CaseList->end(); it++)
    {
        CasePNode *caseP = *it;
        xml += caseP->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</Case>\n";

    xml += util.getMeIdentation(identation + 1) + "<CodeElse>\n";
    for(std::list<StatementNode*>::iterator it = CodeElse->begin(); it != CodeElse->end(); it++)
    {
        StatementNode *sentence = *it;
        xml += sentence->ToXML(identation + 2);
    }
    xml += util.getMeIdentation(identation + 1) + "</CodeElse>\n";

    xml += util.getMeIdentation(identation) + "</CaseNode>\n";

    return xml;
}
