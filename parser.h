#ifndef PARSER_H
#define PARSER_H

#include "ParserException.h"
#include "lexer.h"
#include "utileria.h"

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


    void ExpresionBooleana();
    void ExpresionBooleanaP();
    void Expresion();
    void ExpresionP();
    void Factor();
    void FactorP();
    void Termino();
    void ID();
    void Lista_Accesor();
    void SingleAccesor();
    void Lista_Expresiones();
    void Lista_ExpresionesP();


};

#endif // PARSER_H
