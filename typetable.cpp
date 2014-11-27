#include "typetable.h"

TypeTable * TypeTable::Instance = 0;
list<TypeDefined*> * TypeTable::Types = 0;

TypeTable::TypeTable()
{
}

TypeTable::~TypeTable()
{
}

TypeTable * TypeTable::getInstance(){
    if(Instance == 0)
        Instance = new TypeTable();
    return Instance;
}

bool TypeTable::IsExist(string name)
{
    Utileria ut;
    for(std::list<TypeDefined*>::iterator it = Types->begin(); it != Types->end(); it++)
    {
        TypeDefined *type = *it;
        if(ut.toLower(type->Name) == ut.toLower(name))
            return true;
    }
    return false;
}

BaseType * TypeTable::getType(string name)
{
    Utileria ut;
    for(std::list<TypeDefined*>::iterator it = Types->begin(); it != Types->end(); it++)
    {
        TypeDefined *type = *it;
        if(ut.toLower(type->Name) == ut.toLower(name))
            return type->Type;
    }
    return 0;
}

void TypeTable::setType(string name, BaseType *type){
    TypeDefined * newType = new TypeDefined();
    newType->Name = name;
    newType->Type = type;

    if(Types == 0)
        Types = new list<TypeDefined*>();

    Types->insert(Types->end(), newType);
}
