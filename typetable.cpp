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
    {
        Instance = new TypeTable();
        Instance->Types = new list<TypeDefined*>();
    }
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
    throw SemanticException("No existe el tipo de datos: '" + name +"'");
    return 0;
}

void TypeTable::setType(string name, BaseType *type){
    TypeDefined * newType = new TypeDefined();
    newType->Name = name;
    newType->Type = type;

    if(IsExist(name))
        throw SemanticException("Ya esta definido el tipo de dato: '" + name +"'");

    Types->insert(Types->end(), newType);
}
