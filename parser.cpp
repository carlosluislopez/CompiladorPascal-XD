#include "parser.h"

Parser::Parser(Lexer *lexer)
{
    this->_lexer = lexer;
    validHTML = false;
    this->currentToken = nextToken();
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
    if(currentToken->Type != EndOfFile)
        throw ParserException("Se esperaba fin de codigo; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

}

Token * Parser::nextToken()
{
    Token * tokenTemp = _lexer->NextToken();
    while(tokenTemp->Type == HTML && !validHTML)
    {
        tokenTemp = _lexer->NextToken();
    }
    return tokenTemp;
}

void Parser::Programa()
{
    Lista_DeclaracionTipos();
    Lista_Declaraciones();
    Lista_ProcedimientosFunciones();
    Lista_Sentencias();
}

void Parser::Lista_ProcedimientosFunciones()
{
    while(currentToken->Type == Rw_Procedure
          || currentToken->Type == Rw_Function
         )
    {
        if(currentToken->Type == Rw_Procedure)
        {
            Lista_Procedimientos();
        }else if(currentToken->Type == Rw_Function)
        {
            Lista_Funciones();
        }else{ /* EPSILON */ }
    }
}

void Parser::Lista_DeclaracionTipos()
{
    if(this->currentToken->Type == Rw_Type)
    {
        DeclaracionTipos();
        Lista_DeclaracionTiposP();
    }else{ /* EPSILON */ }
}

void Parser::Lista_DeclaracionTiposP()
{
    if(this->currentToken->Type == Rw_Type || this->currentToken->Type == Id)
    {
        DeclaracionTipos();
        Lista_DeclaracionTiposP();
    }else{ /* EPSILON */ }
}

void Parser::DeclaracionTipos()
{
    if(currentToken->Type == Rw_Type || currentToken->Type == Id)
    {
        if(currentToken->Type == Rw_Type)
            currentToken = nextToken();

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type != Op_Equals)
            throw ParserException("Se esperaba un '='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type == Rw_Array)
            Array();
        else if(currentToken->Type == Rw_Record)
            Record();
        else if(currentToken->Type == LeftParenthesis)
            Enum();
        else if(currentToken->Type == Int)
            Range();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba una ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

    }else{ /* EPSILON */ }
}

void Parser::Array()
{
    if(currentToken->Type == Rw_Array)
    {
        currentToken = nextToken();
        if(currentToken->Type != LeftBrackets && currentToken->Type != Rw_Of)
            throw ParserException("Se esperaba un '[' o 'Of'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        if(currentToken->Type == Rw_Of)
            currentToken = nextToken();

        if(currentToken->Type != LeftBrackets)
            throw ParserException("Se esperaba un '['; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type == Int)
            Range();
        else if(currentToken->Type == Id)
            currentToken = nextToken();
        else
            Tipo();

        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();

        if(currentToken->Type == Rw_Of)
        {
            currentToken = nextToken();
            Tipo();
        }
    }else{ /* EPSILON */ }
}

void Parser::Record(){}

void Parser::Enum()
{
    if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba una Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type == Comma)
            EnumP();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba una ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}

void Parser::EnumP()
{
    currentToken = nextToken();
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();
    if(currentToken->Type == Comma)
        EnumP();
    else if (currentToken->Type == RightParenthesis)
        return;
    else
        throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}

void Parser::Range()
{
    if(this->currentToken->Type == Int)
    {
        currentToken = nextToken();
        if(this->currentToken->Type != Op_Range)
            throw ParserException("Se esperaba un '..'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(this->currentToken->Type != Int)
            throw ParserException("Se esperaba un entero; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}

void Parser::Lista_Declaraciones()
{
    if(this->currentToken->Type == Rw_Var)
    {
        Declaracion();
        Lista_DeclaracionesP();
    }else{ /* EPSILON */ }
}

void Parser::Lista_DeclaracionesP()
{
    if(this->currentToken->Type == Rw_Var || currentToken->Type == Id)
    {
        Declaracion();
        Lista_Declaraciones();
    }else{ /* EPSILON */ }
}

void Parser::Declaracion()
{
    if(currentToken->Type == Rw_Var || currentToken->Type == Id)
    {
        if(currentToken->Type == Rw_Var)
            currentToken = nextToken();

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type == Comma)
            DeclaracionP();
        if (currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Tipo();
        if (currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}

void Parser::DeclaracionP()
{
    currentToken = nextToken();
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();
    if(currentToken->Type == Comma)
        DeclaracionP();
    else if (currentToken->Type == Colon)
        return;
    else
        throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}

void Parser::Tipo()
{
    if(this->currentToken->Type == Rw_Int
       || this->currentToken->Type == Rw_Float
       || this->currentToken->Type == Rw_String
       || this->currentToken->Type == Rw_Char
       || this->currentToken->Type == Rw_Bool
       || this->currentToken->Type == Rw_Integer
       || this->currentToken->Type == Rw_Real
      )
    {
        // Devolver Tipo
        this->currentToken = nextToken();
    }else
    {
        throw ParserException("Se esperaba un tipo de dato valido; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}

void Parser::Lista_Procedimientos()
{
    if(this->currentToken->Type == Rw_Procedure)
    {
        Procedimiento();
        Lista_Procedimientos();
    }else{ /* EPSILON */ }
}

void Parser::Procedimiento()
{
    if(this->currentToken->Type == Rw_Procedure)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Parametros();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        Lista_DeclaracionesP();


        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
    }else{ /* EPSILON */ }
}

void Parser::Parametros()
{
    if(currentToken->Type == Rw_Var || currentToken->Type == Id)
    {
        if(currentToken->Type == Rw_Var)
            currentToken = nextToken();

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type == Comma)
            DeclaracionP();

        if (currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Tipo();

        if(currentToken->Type == Comma)
        {
            currentToken = nextToken();
            Parametros();
        }
    }else{ /* EPSILON */ }
}

void Parser::Lista_Funciones()
{
    if(this->currentToken->Type == Rw_Function)
    {
        Funcion();
        Lista_Funciones();
    }else{ /* EPSILON */ }
}

void Parser::Funcion()
{
    if(this->currentToken->Type == Rw_Function)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Parametros();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        if(currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        Tipo();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        Lista_DeclaracionesP();


        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
    }else{ /* EPSILON */ }
}

void Parser::Lista_Sentencias()
{
    if(this->currentToken->Type != Rw_Begin)
        throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();

    Lista_SentenciasP();

    if(this->currentToken->Type != Rw_End)
        throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();

    if(this->currentToken->Type != Dot)
        throw ParserException("Se esperaba un '.'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();
}

void Parser::Lista_SentenciasP()
{
    if(this->currentToken->Type == Id
       || this->currentToken->Type == Rw_For
       || this->currentToken->Type == Rw_While
       || this->currentToken->Type == Rw_Do
       || this->currentToken->Type == Rw_Print
       || this->currentToken->Type == Rw_If
       || this->currentToken->Type == Rw_Else
       || this->currentToken->Type == Rw_Case
      )
    {
        Sentencia();
        Lista_SentenciasP();
    }else{ /* EPSILON */ }
}

void Parser::Sentencia()
{
    if(currentToken->Type == Rw_Print){
        Print();
    }else if(currentToken->Type == Id){
        Assign();
    }else if(currentToken->Type == Rw_If){
        If();
    }else if(currentToken->Type == Rw_Case){
        Case();
    }else if(currentToken->Type == Rw_For){
        For();
    }else if(currentToken->Type == Rw_Do){
        DoWhile();
    }else if(currentToken->Type == Rw_While){
        While();
    }else{
        throw ParserException("Se esperaba una sentencia valida; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}

void Parser::Assign(){
    if(currentToken->Type == Id){
        ID();
        if(currentToken->Type != Op_Assign)
            throw ParserException("Se esperaba un ':='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionBooleana();
        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}


void Parser::If(){
    if(currentToken->Type == Rw_If){
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Then)
            throw ParserException("Se esperaba un Then; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type == Rw_Else)
        {
            currentToken = nextToken();
            if(currentToken->Type != Rw_Begin)
                throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();

            Lista_SentenciasP();

            if(currentToken->Type != Rw_End)
                throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();
        }

    }else{ /* EPSILON */ }
}


void Parser::Case()
{
    if(currentToken->Type == Rw_Case)
    {
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Of)
            throw ParserException("Se esperaba un 'Of'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        CaseP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
    }else{ /* EPSILON */ }
}


void Parser::CaseP()
{
    if(currentToken->Type == Int
       || currentToken->Type == Char
       || currentToken->Type == Rw_Else
      )
    {
        if(currentToken->Type == Int || currentToken->Type == Char)
        {
            currentToken = nextToken();
            if(currentToken->Type != Colon)
                throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        }
        currentToken = nextToken();
        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        CaseP();

    }else if(currentToken->Type == Rw_End){ /* EPSILON */ }
    else
        throw ParserException("Se esperaba un entero o char; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}


void Parser::For()
{
    if(currentToken->Type == Rw_For)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        ID();
        if(currentToken->Type != Op_Assign)
            throw ParserException("Se esperaba un ':='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionBooleana();

        if(currentToken->Type == Rw_To || currentToken->Type == Rw_Downto)
            currentToken = nextToken();
        else
            throw ParserException("Se esperaba un 'To' o 'Downto'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        ExpresionBooleana();
        if(currentToken->Type != Rw_Do)
            throw ParserException("Se esperaba un 'Do'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        Lista_SentenciasP();
        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}



void Parser::While()
{
    if(currentToken->Type == Rw_While){
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ExpresionBooleana();

        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Do)
            throw ParserException("Se esperaba un 'Do'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

    }else{ /* EPSILON */ }
}



void Parser::DoWhile()
{
    if(currentToken->Type == Rw_Do){
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_While)
            throw ParserException("Se esperaba un 'While'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ExpresionBooleana();

        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

    }else{ /* EPSILON */ }
}


void Parser::Procedimientos(){}


void Parser::Print()
{
    if(currentToken->Type == Rw_Print){
        currentToken = nextToken();
        ExpresionBooleana();
        if (currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else{ /* EPSILON */ }
}


void Parser::ExpresionBooleana()
{
    Expresion();
    ExpresionBooleanaP();
}


void Parser::ExpresionBooleanaP()
{
    if(currentToken->Type == Op_Equals)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }else if(currentToken->Type == Op_LessThan)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }
    else if(currentToken->Type == Op_LessEqualThan)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }
    else if(currentToken->Type == Op_GreaterThan)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }
    else if(currentToken->Type == Op_GreaterEqualThan)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }
    else if(currentToken->Type == Op_NotEquals)
    {
        currentToken = nextToken();
        Expresion();
        ExpresionBooleanaP();
    }else { /* EPSILON */ }
}


void Parser::Expresion()
{
    Factor();
    ExpresionP();
}


void Parser::ExpresionP()
{
    if(currentToken->Type == Op_Sum)
    {
        currentToken = nextToken();
        Factor();
        ExpresionP();
    }else if(currentToken->Type == Op_Substract)
    {
        currentToken = nextToken();
        Factor();
        ExpresionP();
    }else { /* EPSILON */ }
}


void Parser::Factor()
{
    Termino();
    FactorP();
}


void Parser::FactorP()
{
    if(currentToken->Type == Op_Multiply)
    {
        currentToken = nextToken();
        Termino();
        FactorP();
    }
    if(currentToken->Type == Op_Divide)
    {
        currentToken = nextToken();
        Termino();
        FactorP();
    }if(currentToken->Type == Rw_Div)
    {
        currentToken = nextToken();
        Termino();
        FactorP();
    }if(currentToken->Type == Rw_Mod)
    {
        currentToken = nextToken();
        Termino();
        FactorP();
    }if(currentToken->Type == Op_Exp)
    {
        currentToken = nextToken();
        Termino();
        FactorP();
    }else { /* EPSILON */ }
}


void Parser::Termino()
{
    if (currentToken->Type == Rw_Not)
    {
        currentToken = nextToken();
        ExpresionBooleana();
    }else if(currentToken->Type == Id)
    {
        ID();
    }else if(currentToken->Type == Int
             || currentToken->Type == Float
             || currentToken->Type == Bool
             || currentToken->Type == String
             || currentToken->Type == Binary
             || currentToken->Type == Hexadecimal
             || currentToken->Type == Char
            )
    {
        currentToken = nextToken();
    }else if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken();
        ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else if(currentToken->Type == LeftBrackets)
    {
        currentToken = nextToken();
        ExpresionBooleana();
        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else
    {
        throw ParserException("Se esperaba un termino; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}


void Parser::ID()
{
    currentToken = nextToken();
    Lista_Accesor();
}


void Parser::Lista_Accesor()
{
    if (currentToken->Type == Dot
        || currentToken->Type == LeftParenthesis
        || currentToken->Type == LeftBrackets
       )
    {
        SingleAccesor();
        Lista_Accesor();
    }
    else { /* EPSILON */ }
}


void Parser::SingleAccesor()
{
    if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken();
        Lista_Expresiones();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    } else if(currentToken->Type == LeftBrackets)
    {
        currentToken = nextToken();
        Lista_Expresiones();
        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else if(currentToken->Type == Dot)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
    }else
    {
        throw ParserException("Se esperaba un Accesor; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}


void Parser::Lista_Expresiones()
{
    Expresion();
    Lista_ExpresionesP();
}


void Parser::Lista_ExpresionesP()
{
    if (currentToken->Type == Comma)
    {
        currentToken = nextToken();
        Expresion();
        Lista_ExpresionesP();
    }
    else { /* EPSILON */ }
}






