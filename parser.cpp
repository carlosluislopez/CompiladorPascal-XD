#include "parser.h"

Parser::Parser(Lexer *lexer)
{
    listStatement = new list<StatementNode*>();
    this->_lexer = lexer;
    validHTML = false;
    this->currentToken = nextToken(listStatement, listStatement->end());
}

list<StatementNode *> *Parser::Parse()
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

    //list<StatementNode *> * listStatement = Programa();
    Programa();
    if(currentToken->Type != EndOfFile)
        throw ParserException("Se esperaba fin de codigo; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

    return listStatement;
}

Token * Parser::nextToken(list<StatementNode *> *listStatementNode, list<StatementNode*>::iterator iterador)
{
    Token * tokenTemp = _lexer->NextToken();
    while(tokenTemp->Type == HTML && !validHTML)
    {
        StringNode * stringNode = new StringNode();
        PrintNode * statementNode = new PrintNode();

        stringNode->Value = tokenTemp->Lexeme;
        statementNode->Value = stringNode;
        listStatementNode->insert(iterador, statementNode);

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
            currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != Op_Equals)
            throw ParserException("Se esperaba un '='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());

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
        currentToken = nextToken(this->listStatement, this->listStatement->end());

    }else{ /* EPSILON */ }
}

void Parser::Array()
{
    if(currentToken->Type == Rw_Array)
    {
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != LeftBrackets && currentToken->Type != Rw_Of)
            throw ParserException("Se esperaba un '[' o 'Of'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        if(currentToken->Type == Rw_Of)
            currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type != LeftBrackets)
            throw ParserException("Se esperaba un '['; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type == Int)
            Range();
        else if(currentToken->Type == Id)
            currentToken = nextToken(this->listStatement, this->listStatement->end());
        else
            Tipo();

        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type == Rw_Of)
        {
            currentToken = nextToken(this->listStatement, this->listStatement->end());
            Tipo();
        }
    }else{ /* EPSILON */ }
}

void Parser::Record(){}

void Parser::Enum()
{
    if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba una Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type == Comma)
            EnumP();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba una ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
    }else{ /* EPSILON */ }
}

void Parser::EnumP()
{
    currentToken = nextToken(this->listStatement, this->listStatement->end());
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken(this->listStatement, this->listStatement->end());
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
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(this->currentToken->Type != Op_Range)
            throw ParserException("Se esperaba un '..'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(this->currentToken->Type != Int)
            throw ParserException("Se esperaba un entero; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
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
            currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type == Comma)
            DeclaracionP();
        if (currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Tipo();
        if (currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
    }else{ /* EPSILON */ }
}

void Parser::DeclaracionP()
{
    currentToken = nextToken(this->listStatement, this->listStatement->end());
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken(this->listStatement, this->listStatement->end());
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
        this->currentToken = nextToken(this->listStatement, this->listStatement->end());
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
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Parametros();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Lista_DeclaracionesP();


        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());

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
            currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type == Comma)
            DeclaracionP();

        if (currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Tipo();

        if(currentToken->Type == Comma)
        {
            currentToken = nextToken(this->listStatement, this->listStatement->end());
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
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Parametros();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
        if(currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Tipo();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Lista_DeclaracionesP();


        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());
        Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken(this->listStatement, this->listStatement->end());

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken(this->listStatement, this->listStatement->end());
    }else{ /* EPSILON */ }
}

void Parser::Lista_Sentencias()
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
        list<StatementNode*>::iterator iterador = this->listStatement->end();
        StatementNode *statementNode = Sentencia(this->listStatement, this->listStatement->end());
        listStatement->insert(iterador, statementNode);
        Lista_Sentencias();
    }else{ /* EPSILON */ }
}

void Parser::Lista_SentenciasP(list<StatementNode *> * listStatementNode)
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
        list<StatementNode*>::iterator iterador = listStatementNode->end();
        StatementNode *statementNode = Sentencia(listStatementNode, listStatementNode->end());
        Lista_SentenciasP(listStatementNode);
        listStatementNode->insert(iterador, statementNode);
    }else
    {
        return new list<StatementNode*>();
        /* EPSILON */
    }
}

StatementNode * Parser::Sentencia(list<StatementNode*> * listStatement, list<StatementNode*>::iterator iterador)
{
    if(currentToken->Type == Rw_Print){
        return Print(listStatement, iterador);
    }else if(currentToken->Type == Id){
        return Assign(listStatement, iterador);
    }else if(currentToken->Type == Rw_If){
        return If(listStatement, iterador);
    }else if(currentToken->Type == Rw_Case){
        return Case(listStatement, iterador);
    }else if(currentToken->Type == Rw_For){
        return For(listStatement, iterador);
    }else if(currentToken->Type == Rw_Do){
        return DoWhile(listStatement, iterador);
    }else if(currentToken->Type == Rw_While){
        return While(listStatement, iterador);
    }else{
        throw ParserException("Se esperaba una sentencia valida; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}

StatementNode * Parser::Assign(list<StatementNode*> * listStatement, list<StatementNode*>::iterator iterador){
    if(currentToken->Type == Id){
        IdNode * idNode = ID();
        if(currentToken->Type != Op_Assign)
            throw ParserException("Se esperaba un ':='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionNode *expresionNode = ExpresionBooleana();
        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        AssignationNode *statementNode = new AssignationNode();
        statementNode->LeftValue = idNode;
        statementNode->RightValue = expresionNode;

        return statementNode;

    }else
    {
        throw ParserException("Se esperaba una sentencia de asignacion; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}


StatementNode * Parser::If(){
    if(currentToken->Type == Rw_If){
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionNode *Condition = ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Then)
            throw ParserException("Se esperaba un Then; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        list<StatementNode*> *Code = Lista_SentenciasP();

        IfNode *ifNode = new IfNode();
        ifNode->Condition = Condition;
        ifNode->Code = Code;


        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type == Rw_Else)
        {
            currentToken = nextToken();
            if(currentToken->Type != Rw_Begin)
                throw ParserException("Se esperaba un Begin; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();

            list<StatementNode*> *CodeElse = Lista_SentenciasP();
            ifNode->CodeElse = CodeElse;

            if(currentToken->Type != Rw_End)
                throw ParserException("Se esperaba un End; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();
        }

        return ifNode;
    }else
    {
        throw ParserException("Se esperaba una sentencia If; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}


StatementNode *Parser::Case()
{
    if(currentToken->Type == Rw_Case)
    {
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionNode *Condition = ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Of)
            throw ParserException("Se esperaba un 'Of'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        list<CasePNode*>* casepList = CaseP();
        list<StatementNode*> *CodeElse;

        if(currentToken->Type == Rw_Else)
        {
            currentToken = nextToken();
            if(currentToken->Type != Rw_Begin)
                throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

            currentToken = nextToken();
            CodeElse = Lista_SentenciasP();

            if(currentToken->Type != Rw_End)
                throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();

            if(currentToken->Type != SemiColon)
                throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
            currentToken = nextToken();
        }

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        CaseNode *caseNode = new CaseNode();
        caseNode->Condition = Condition;
        caseNode->CaseList = casepList;
        caseNode->CodeElse = CodeElse;

        return caseNode;

    }else
    {
        throw ParserException("Se esperaba una sentencia Case; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}


list<CasePNode *> * Parser::CaseP()
{
    if(currentToken->Type == Rw_Else)
        return new list<CasePNode *>();

    if(currentToken->Type == Int || currentToken->Type == Char)
    {
        ExpresionNode *Condition;
        if(currentToken->Type == Int)
        {
            IntNode *intNode = new IntNode();
            intNode->Value = currentToken->Lexeme;

            Condition = intNode;

            currentToken = nextToken();
            if(currentToken->Type != Colon)
                throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        }else if(currentToken->Type == Char)
        {
            CharNode *charNode = new CharNode();
            charNode->Value = currentToken->Lexeme;

            Condition = charNode;

            currentToken = nextToken();
            if(currentToken->Type != Colon)
                throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        }
        currentToken = nextToken();
        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        currentToken = nextToken();
        list<StatementNode*> *Code = Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        CasePNode *casePNode = new CasePNode();
        casePNode->Code = Code;
        casePNode->Condition = Condition;

        list<CasePNode*> *listCase = CaseP();

        listCase->insert(listCase->begin(), casePNode);

        return listCase;

    }else if(currentToken->Type == Rw_End)
    {
        return new list<CasePNode *>();
        /* EPSILON */
    }
    else
        throw ParserException("Se esperaba un entero o char; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
}


StatementNode * Parser::For()
{
    if(currentToken->Type == Rw_For)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        IdNode * idNode = ID();
        if(currentToken->Type != Op_Assign)
            throw ParserException("Se esperaba un ':='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        ExpresionNode *initialValue = ExpresionBooleana();

        if(currentToken->Type == Rw_To || currentToken->Type == Rw_Downto)
            currentToken = nextToken();
        else
            throw ParserException("Se esperaba un 'To' o 'Downto'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

        ExpresionNode *finalValue = ExpresionBooleana();
        if(currentToken->Type != Rw_Do)
            throw ParserException("Se esperaba un 'Do'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        list<StatementNode*> *code = Lista_SentenciasP();
        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ForNode *forNode = new ForNode();
        forNode->Id = idNode;
        forNode->InitialValue = initialValue;
        forNode->FinalValue = finalValue;
        forNode->Code = code;

        return forNode;
    }else
    {
        throw ParserException("Se esperaba una sentencia de For; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}



StatementNode * Parser::While()
{
    if(currentToken->Type == Rw_While){
        currentToken = nextToken();
        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ExpresionNode *Condition = ExpresionBooleana();

        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Do)
            throw ParserException("Se esperaba un 'Do'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        list<StatementNode*> *Code = Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        WhileNode *whileNode = new WhileNode();
        whileNode->Condition = Condition;
        whileNode->Code = Code;

        return whileNode;

    }else
    {
        throw ParserException("Se esperaba una sentencia de While; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}



StatementNode * Parser::DoWhile()
{
    if(currentToken->Type == Rw_Do){
        currentToken = nextToken();

        if(currentToken->Type != Rw_Begin)
            throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        list<StatementNode*> *Code = Lista_SentenciasP();

        if(currentToken->Type != Rw_End)
            throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != Rw_While)
            throw ParserException("Se esperaba un 'While'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != LeftParenthesis)
            throw ParserException("Se esperaba un '('; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ExpresionNode *Condition = ExpresionBooleana();

        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        DoWhileNode *doWhileNode = new DoWhileNode();
        doWhileNode->Code = Code;
        doWhileNode->Condition = Condition;

        return doWhileNode;
    }else
    {
        throw ParserException("Se esperaba una sentencia de DoWhile; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}


void Parser::Procedimientos(){}


StatementNode *Parser::Print()
{
    if(currentToken->Type == Rw_Print)
    {
        currentToken = nextToken();
        ExpresionNode *expresionNode = ExpresionBooleana();
        if (currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        PrintNode * statementNode = new PrintNode();
        statementNode->Value = expresionNode;

        return statementNode;

    }else
    {
        throw ParserException("Se esperaba una sentencia Print; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        /* EPSILON */
    }
}


ExpresionNode * Parser::ExpresionBooleana()
{
    ExpresionNode *expresionNode = Expresion();
    expresionNode->TypeNode = BooleanExpresionNodeType;
    return ExpresionBooleanaP(expresionNode);
}


ExpresionNode * Parser::ExpresionBooleanaP(ExpresionNode *paramNode)
{
    if(currentToken->Type == Op_Equals)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        EqualsOperatorNode *operatorNode = new EqualsOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);
    }else if(currentToken->Type == Op_LessThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        LessThanOperatorNode *operatorNode = new LessThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_LessEqualThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        LessEqualsThanOperatorNode *operatorNode = new LessEqualsThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_GreaterThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        GreaterThanOperatorNode *operatorNode = new GreaterThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);

    }
    else if(currentToken->Type == Op_GreaterEqualThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        GreaterEqualsThanOperatorNode *operatorNode = new GreaterEqualsThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_NotEquals)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        NotEqualsOperatorNode *operatorNode = new NotEqualsOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;
        operatorNode->TypeNode = BooleanExpresionNodeType;

        return ExpresionBooleanaP(operatorNode);
    }else
    {
        return paramNode;
        /* EPSILON */
    }
}


ExpresionNode * Parser::Expresion()
{
    ExpresionNode * factor = Factor();
    return ExpresionP(factor);
}


ExpresionNode * Parser::ExpresionP(ExpresionNode *paramNode)
{
    if(currentToken->Type == Op_Sum)
    {
        currentToken = nextToken();

        ExpresionNode * factor = Factor();
        SumOperatorNode *operatorNode = new SumOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = factor;

        return ExpresionP(operatorNode);
    }else if(currentToken->Type == Op_Substract)
    {
        currentToken = nextToken();

        ExpresionNode * factor = Factor();
        SubstractOperatorNode *operatorNode = new SubstractOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = factor;

        return ExpresionP(operatorNode);
    }else
    {
        return paramNode;
        /* EPSILON */
    }
}


ExpresionNode * Parser::Factor()
{
    ExpresionNode * termino = Termino();
    return FactorP(termino);
}


ExpresionNode *Parser::FactorP(ExpresionNode *paramNode)
{
    if(currentToken->Type == Op_Multiply)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        MultiplyOperatorNode *operatorNode = new MultiplyOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = termino;

        return FactorP(operatorNode);
    }
    if(currentToken->Type == Op_Divide)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        DivisionOperatorNode *operatorNode = new DivisionOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = termino;

        return FactorP(operatorNode);

    }if(currentToken->Type == Rw_Div)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        DivisionIntegerOperationNode *operatorNode = new DivisionIntegerOperationNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = termino;

        return FactorP(operatorNode);
    }if(currentToken->Type == Rw_Mod)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        ModOperationNode *operatorNode = new ModOperationNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = termino;

        return FactorP(operatorNode);
    }if(currentToken->Type == Op_Exp)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        ExpOperationNode *operatorNode = new ExpOperationNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = termino;

        return FactorP(operatorNode);
    }else
    {
        return paramNode;
        /* EPSILON */
    }
}


ExpresionNode *Parser::Termino()
{
    if (currentToken->Type == Rw_Not)
    {
        currentToken = nextToken();

        ExpresionNode * termino = Termino();
        NotOperatorNode * notOperatorNode = new NotOperatorNode();
        notOperatorNode->OperandNode = termino;

        return notOperatorNode;
    }else if(currentToken->Type == Id)
    {
        return ID();
    }else if(currentToken->Type == Int)
    {
        IntNode * intNode = new IntNode();
        intNode->Value = currentToken->Lexeme;
        intNode->TypeNode = IntNodeType;
        currentToken = nextToken();
        return intNode;
    }else if(currentToken->Type == Float)
    {
        FloatNode * floatNode = new FloatNode();
        floatNode->Value = currentToken->Lexeme;
        floatNode->TypeNode = FloatNodeType;
        currentToken = nextToken();
        return floatNode;
    }else if(currentToken->Type == Bool)
    {
        BoolNode * boolNode = new BoolNode();
        boolNode->Value = currentToken->Lexeme;
        boolNode->TypeNode = BoolNodeType;
        currentToken = nextToken();
        return boolNode;
    }else if(currentToken->Type == String)
    {
        StringNode * stringNode = new StringNode();
        stringNode->Value = currentToken->Lexeme;
        stringNode->TypeNode = StringNodeType;
        currentToken = nextToken();
        return stringNode;
    }else if(currentToken->Type == Binary)
    {
        BinaryNode * binaryNode = new BinaryNode();
        binaryNode->Value = currentToken->Lexeme;
        binaryNode->TypeNode = BinaryNodeType;
        currentToken = nextToken();
        return binaryNode;
    }else if(currentToken->Type == Hexadecimal)
    {
        HexadecimalNode * hexadecimalNode = new HexadecimalNode();
        hexadecimalNode->Value = currentToken->Lexeme;
        hexadecimalNode->TypeNode = HexadecimalNodeType;
        currentToken = nextToken();
        return hexadecimalNode;
    }else if(currentToken->Type == Char)
    {
        CharNode * charNode = new CharNode();
        charNode->Value = currentToken->Lexeme;
        charNode->TypeNode = CharNodeType;
        currentToken = nextToken();
        return charNode;
    }else if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken();
        ExpresionNode * expresionNode = ExpresionBooleana();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        return expresionNode;
    }else if(currentToken->Type == LeftBrackets)
    {
        currentToken = nextToken();
        ExpresionNode * expresionNode = ExpresionBooleana();
        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        return expresionNode;
    }else
    {
        throw ParserException("Se esperaba un termino; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}


IdNode * Parser::ID()
{
    string name = currentToken->Lexeme;
    currentToken = nextToken();
    Accesor * accesorList = Lista_Accesor();

    IdNode * id = new IdNode();
    id->Name = name;
    id->AccesorList = accesorList;
    id->TypeNode = IdNodeType;

    return id;
}


Accesor * Parser::Lista_Accesor()
{
    if (currentToken->Type == Dot
        || currentToken->Type == LeftParenthesis
        || currentToken->Type == LeftBrackets
       )
    {
        Accesor * accesor = SingleAccesor();
        Accesor * accesorList = Lista_Accesor();
        accesor->Next = accesorList;

        return accesor;
    }
    else
    {
        return 0;
        /* EPSILON */
    }
}


Accesor * Parser::SingleAccesor()
{
    if(currentToken->Type == LeftParenthesis)
    {
        currentToken = nextToken();
        list<ExpresionNode*> *listExpresion = Lista_Expresiones();
        if(currentToken->Type != RightParenthesis)
            throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ArrayAccesor * array = new ArrayAccesor();
        array->Indexes = listExpresion;
        return array;

    } else if(currentToken->Type == LeftBrackets)
    {
        currentToken = nextToken();
        list<ExpresionNode*> *listExpresion = Lista_Expresiones();
        if(currentToken->Type != RightBrackets)
            throw ParserException("Se esperaba un ']'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        ArrayAccesor * array = new ArrayAccesor();
        array->Indexes = listExpresion;
        return array;

    }else if(currentToken->Type == Dot)
    {
        currentToken = nextToken();
        if(currentToken->Type != Id)
            throw ParserException("Se esperaba un Id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        string id = currentToken->Lexeme;
        currentToken = nextToken();

        FieldAccesor *field = new FieldAccesor();
        field->Id = id;

        return field;
    }else
    {
        throw ParserException("Se esperaba un Accesor; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}


list<ExpresionNode *> *Parser::Lista_Expresiones()
{
    ExpresionNode *nodeExpresion = Expresion();
    list<ExpresionNode*> *listExpresion = Lista_ExpresionesP();

    listExpresion->insert(listExpresion->begin(), nodeExpresion);
    return listExpresion;
}


list<ExpresionNode*> *Parser::Lista_ExpresionesP()
{
    if (currentToken->Type == Comma)
    {
        currentToken = nextToken();
        ExpresionNode *nodeExpresion = Expresion();
        list<ExpresionNode*> *listExpresion = Lista_ExpresionesP();

        listExpresion->insert(listExpresion->begin(), nodeExpresion);

        return listExpresion;
    }
    else
    {
        return new list<ExpresionNode*>();
        //EPSILON
    }
}






