#ifndef PARSER_H
#define PARSER_H

#include "ParserException.h"
#include "lexer.h"
#include "utileria.h"
#include <list>
#include "SyntaxTree.h"
#include "Values.h"
#include "Types.h"



using namespace std;

class Parser
{
public:
    Parser(Lexer *lexer);
    list<StatementNode *> * Parse();
private:
    Lexer *_lexer;
    Token *currentToken;
    Utileria util;
    Token *nextToken(list<StatementNode *> *listStatementNode, list<StatementNode*>::iterator iterador);
    list<StatementNode *> * listStatement;
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
    void Lista_SentenciasP(list<StatementNode *> * listStatementNode);

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


    StatementNode *Sentencia();

    StatementNode *Assign();
    StatementNode *If();
    StatementNode *Case();
    StatementNode *For();
    StatementNode *While();
    StatementNode * DoWhile();
    void Procedimientos();
    StatementNode * Print();

    list<CasePNode *> *CaseP();


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
