#include "symboltable.h"

SymbolTable *SymbolTable::Instance = 0;
TypeTable *SymbolTable::Types = 0;
list<Variable*> *SymbolTable::GlobalVariables = 0;
list<Variable*> *SymbolTable::LocalVariables = 0;

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

SymbolTable *SymbolTable::getInstance(){
    if(Instance == 0)
    {
        Instance = new SymbolTable();
        Instance->Types = TypeTable::getInstance();

        IntType * intType = new IntType();
        intType->type = BaseTypeInt;

        FloatType * floatType = new FloatType();
        floatType->type = BaseTypeFloat;

        BoolType * boolType = new BoolType();
        boolType->type = BaseTypeBool;

        StringType * stringType = new StringType();
        stringType->type = BaseTypeString;

        CharType * charType = new CharType();
        charType->type = BaseTypeChar;

        Instance->addType("integer", intType);
        Instance->addType("float", floatType);
        Instance->addType("bool", boolType);
        Instance->addType("string", stringType);
        Instance->addType("char", charType);

        Instance->GlobalVariables = new list<Variable*>();
        Instance->LocalVariables = new list<Variable*>();
    }
    return Instance;
}

bool SymbolTable::IsExistType(string typeName)
{
    return Types->IsExist(typeName);
}


BaseType * SymbolTable::getBaseType(string typeName)
{
    return Types->getType(typeName);
}


void SymbolTable::addType(string name, BaseType* type)
{
    if(IsExistType(name))
        throw SemanticException("Ya habia definido el tipo: " + name + ";");

    Types->setType(name, type);
}


bool SymbolTable::IsExist(string variableName)
{
    Utileria ut;
    for(std::list<Variable*>::iterator it = LocalVariables->begin(); it != LocalVariables->end(); it++)
    {
        Variable *var = *it;
        if(ut.toLower(var->Name) == ut.toLower(variableName))
            return true;
    }

    for(std::list<Variable*>::iterator it = GlobalVariables->begin(); it != GlobalVariables->end(); it++)
    {
        Variable *var = *it;
        if(ut.toLower(var->Name) == ut.toLower(variableName))
            return true;
    }

    return false;
}


BaseType * SymbolTable::getVariableType(string variableName){
    Utileria ut;
    for(std::list<Variable*>::iterator it = LocalVariables->begin(); it != LocalVariables->end(); it++)
    {
        Variable *var = *it;
        if(ut.toLower(var->Name) == ut.toLower(variableName))
            return var->Type;
    }

    for(std::list<Variable*>::iterator it = GlobalVariables->begin(); it != GlobalVariables->end(); it++)
    {
        Variable *var = *it;
        if(ut.toLower(var->Name) == ut.toLower(variableName))
            return var->Type;
    }

    return 0;
}


void SymbolTable::addGlobalVariable(string name, BaseType* type){
    Variable *newVariable = new Variable();
    newVariable->Name = name;
    newVariable->Type = type;
    GlobalVariables->insert(GlobalVariables->end(), newVariable);
}


void SymbolTable::addLocalVariable(string name, BaseType* type){
    Variable *newVariable = new Variable();
    newVariable->Name = name;
    newVariable->Type = type;
    LocalVariables->insert(LocalVariables->end(), newVariable);
}



