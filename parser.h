#ifndef PARSER_H
#define PARSER_H

#include "ParserException.h"
#include "lexer.h"
#include "utileria.h"
#include <list>
#include "StatementNode.h"
#include "BaseType.h"
#include "ExpresionValue.h"
#include "SyntaxTree.h"



using namespace std;

class Parser
{
public:
    Parser(Lexer *lexer);
    void Parse();
private:
    Lexer *_lexer;
    Token *currentToken;
    Utileria util;
    Token *nextToken();
    bool validHTML;
    void Programa();

    void Lista_DeclaracionTipos();
    void Lista_DeclaracionTiposP();

    void Lista_Declaraciones();
    void Lista_DeclaracionesP();
    void Lista_ProcedimientosFunciones();
    void Lista_Procedimientos();
    void Lista_Funciones();
    void Lista_Sentencias();
    void Lista_SentenciasP();

    void Array();
    void Record();
    void Enum();
    void Range();

    void EnumP();

    void Parametros();

    void DeclaracionTipos();
    void Declaracion();
    void DeclaracionP();
    void Tipo();

    void Procedimiento();
    void Funcion();


    void Sentencia();

    void Assign();
    void If();
    void Case();
    void For();
    void While();
    void DoWhile();
    void Procedimientos();
    void Print();

    void CaseP();


    ExpresionNode *ExpresionBooleana();
    ExpresionNode *ExpresionBooleanaP(ExpresionNode *paramNode);
    ExpresionNode *Expresion();
    ExpresionNode * ExpresionP(ExpresionNode *paramNode);
    ExpresionNode *Factor();
    ExpresionNode * FactorP(ExpresionNode *paramNode);
    ExpresionNode * Termino();
    IdNode * ID();
    Accesor *Lista_Accesor();
    Accesor *SingleAccesor();
    list<ExpresionNode*> * Lista_Expresiones();
    list<ExpresionNode*> *Lista_ExpresionesP();


};

#endif // PARSER_H
