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
    void Programa();
    void Lista_Declaraciones();
    void Lista_Sentencias();
    void Declaracion();
    void DeclaracionP();
    void Tipo();
    void Sentencia();
    void ExpresionBooleana();
    void ExpresionBooleanaP();
    void Expresion();
    void ExpresionP();
    void Factor();
    void FactorP();
    void Termino();
    void ID();


};

#endif // PARSER_H
