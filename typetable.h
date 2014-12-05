#ifndef TYPETABLE_H
#define TYPETABLE_H

#include <list>
#include "string"
#include "TypeDefined.h"
#include "Types.h"
#include "utileria.h"

using namespace std;

class TypeTable
{
private:
    TypeTable();
    static TypeTable* Instance;
    static list<TypeDefined*> * Types;
public:
    ~TypeTable();
    static TypeTable *getInstance();
    static bool IsExist(string name);
    static BaseType * getType(string name);
    static void setType(string name, BaseType* type);
};

#endif // TYPETABLE_H
