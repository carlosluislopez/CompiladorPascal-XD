#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "typetable.h"
#include "Variable.h"


using namespace std;

class SymbolTable
{
private:
    SymbolTable();
    static SymbolTable* Instance;
    static TypeTable * Types;
    static list<Variable*> * GlobalVariables;
    static list<Variable*> * LocalVariables;
public:
    ~SymbolTable();
    static SymbolTable *getInstance();

    static bool IsExistType(string typeName);
    static BaseType * getBaseType(string typeName);
    static void addType(string name, BaseType* type);

    static bool IsExist(string variableName);
    static BaseType * getVariableType(string variableName);
    static void addGlobalVariable(string name, BaseType* type);
    static void addLocalVariable(string name, BaseType* type);
};

#endif // SYMBOLTABLE_H
