#include "parser.h"

Parser::Parser(Lexer *lexer)
{
    this->_lexer = lexer;
    this->currentToken = this->_lexer->NextToken();
}

void Parser::Parse()
{
//    while(currentToken->Type != EndOfFile)
//    {
//        cout <<"Line: " << currentToken->Line << " \tCol: " << currentToken->Column << "\tType: " << currentToken->Type << " \t" << "\tLexeme: " << currentToken->Lexeme << endl;
//        try
//        {
//            currentToken = this->_lexer->NextToken();
//        }catch(LexicalException &lexEx)
//        {
//            cout << lexEx.what() << '\n';
//            break;
//        }
//    }
    Programa();

}



void Parser::Programa()
{
    Lista_Declaraciones();
    Lista_Sentencias();
}

void Parser::Lista_Declaraciones()
{
    if(this->currentToken->Type == Rw_Type
       || this->currentToken->Type == Rw_Var
       || this->currentToken->Type == Rw_Function
       || this->currentToken->Type == Rw_Procedure
      )
    {
        Declaracion();
        Lista_Declaraciones();
    }
}

void Parser::Declaracion()
{
    currentToken = _lexer->NextToken();
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = _lexer->NextToken();
    if(currentToken->Type == Comma)
        DeclaracionP();
    Tipo();
    if (currentToken->Type != SemiColon)
        throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}

void Parser::DeclaracionP(){
    currentToken = _lexer->NextToken();
    string id = currentToken->Lexeme;
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = _lexer->NextToken();
    if(currentToken->Type == Comma)
        DeclaracionP();
    else if (currentToken->Type == Colon)
        return;
    else
        throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}

void Parser::Tipo(){

}

void Parser::Lista_Sentencias(){}

void Parser::Sentencia(){}

void Parser::ExpresionBooleana(){}

void Parser::ExpresionBooleanaP(){}

void Parser::Expresion(){}

void Parser::ExpresionP(){}

void Parser::Factor(){}

void Parser::FactorP(){}

void Parser::Termino(){}

void Parser::ID(){}

