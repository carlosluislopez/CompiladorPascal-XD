#include "parser.h"

Parser::Parser(Lexer *lexer)
{
    this->_lexer = lexer;
    validHTML = false;
    symbolTable = SymbolTable::getInstance();

    this->currentToken = nextToken();
}

list<StatementNode *> *Parser::Parse()
{
    list<StatementNode *> * listStatement = Programa();
    if(currentToken->Type != EndOfFile)
        throw ParserException("Se esperaba fin de codigo; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));

    return listStatement;
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

list<StatementNode *> * Parser::Programa()
{
    Lista_DeclaracionTipos();
    Lista_Declaraciones();
    Lista_ProcedimientosFunciones();
    list<StatementNode *> * listStatement = Lista_Sentencias();
    return listStatement;
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
        string id = currentToken->Lexeme;
        currentToken = nextToken();
        if(currentToken->Type != Op_Equals)
            throw ParserException("Se esperaba un '='; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        BaseType *type = 0;
        if(currentToken->Type == Rw_Array)
            type = Array();
        else if(currentToken->Type == Rw_Record)
            type = Record();
        else if(currentToken->Type == LeftParenthesis)
            type = Enum();
        else if(currentToken->Type == Int)
            type = Range();
        else
            type = Tipo();

        symbolTable->addType(id, type);

        if(currentToken->Type != SemiColon)
            throw ParserException("Se esperaba una ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

    }else{ /* EPSILON */ }
}

BaseType * Parser::Array()
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
    return 0;
}

BaseType * Parser::Record(){ return 0; }

BaseType *Parser::Enum()
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
    return 0;
}

BaseType * Parser::EnumP()
{
    currentToken = nextToken();
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    currentToken = nextToken();
    if(currentToken->Type == Comma)
        EnumP();
    else if (currentToken->Type == RightParenthesis)
        return 0;
    else
        throw ParserException("Se esperaba un ')'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    return 0;
}

BaseType * Parser::Range()
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
    return 0;
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

        string id = currentToken->Lexeme;
        int line = currentToken->Line;
        int col = currentToken->Column;

        list<string> *listId = 0;
        currentToken = nextToken();
        if(currentToken->Type == Comma)
            listId = DeclaracionP();
        if (currentToken->Type != Colon)
            throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();
        BaseType *type = Tipo();
        if (currentToken->Type != SemiColon)
            throw ParserException("Se esperaba un ';'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
        currentToken = nextToken();

        if(listId == 0)
            listId = new list<string>();

        listId->insert(listId->begin(), id);

        for(std::list<string>::iterator it = listId->begin(); it != listId->end(); it++)
        {
            string name = *it;
            if(symbolTable->IsExist(name))
                throw SemanticException("Ya esta definido el Id: " + name + "; Line: " + util.toString(line) + ", Column: " + util.toString(col));

            symbolTable->addGlobalVariable(id, type);
        }

        //if(symbolTable->IsExist(id))
        //    throw SemanticException("Ya esta definido el Id: " + id + "; Line: " + util.toString(line) + ", Column: " + util.toString(col));

        //symbolTable->addGlobalVariable(id, type);

    }else{ /* EPSILON */ }
}

list<string> * Parser::DeclaracionP()
{
    list<string> *listId = 0;
    currentToken = nextToken();
    if(currentToken->Type != Id)
        throw ParserException("Se esperaba un id; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    string id = currentToken->Lexeme;
    currentToken = nextToken();
    if(currentToken->Type == Comma)
        listId = DeclaracionP();
    else if (currentToken->Type == Colon)
    {
        if(listId == 0)
        {
            listId = new list<string>();
        }
        listId->insert(listId->begin(), id);
        return listId;
    }
    else
    {
        throw ParserException("Se esperaba un ':'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
    return new list<string>();
}

BaseType * Parser::Tipo()
{
    if(symbolTable->IsExistType(currentToken->Lexeme))
    {
        string tempLexeme = currentToken->Lexeme;
        currentToken = nextToken();
        return symbolTable->getBaseType(tempLexeme);
    }else{
        throw SemanticException("No existe el tipo de dato: " + currentToken->Lexeme + "; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
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

list<StatementNode *> * Parser::Lista_Sentencias()
{
//    if(this->currentToken->Type != Rw_Begin)
//        throw ParserException("Se esperaba un 'Begin'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
//    currentToken = nextToken();

    list<StatementNode*> *listStatement = Lista_SentenciasP();

//    if(this->currentToken->Type != Rw_End)
//        throw ParserException("Se esperaba un 'End'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
//    currentToken = nextToken();

//    if(this->currentToken->Type != Dot)
//        throw ParserException("Se esperaba un '.'; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
//    currentToken = nextToken();

    return listStatement;
}

list<StatementNode *> * Parser::Lista_SentenciasP()
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

        StatementNode *statementNode = Sentencia();
        list<StatementNode*> *listStatement = Lista_SentenciasP();
        listStatement->insert(listStatement->begin(), statementNode);

        return listStatement;
    }else
    {
        return new list<StatementNode*>();
        /* EPSILON */
    }
}

StatementNode * Parser::Sentencia()
{
    if(currentToken->Type == Rw_Print){
        return Print();
    }else if(currentToken->Type == Id){
        return Assign();
    }else if(currentToken->Type == Rw_If){
        return If();
    }else if(currentToken->Type == Rw_Case){
        return Case();
    }else if(currentToken->Type == Rw_For){
        return For();
    }else if(currentToken->Type == Rw_Do){
        return DoWhile();
    }else if(currentToken->Type == Rw_While){
        return While();
    }else{
        throw ParserException("Se esperaba una sentencia valida; Line: " + util.toString(currentToken->Line) + ", Column: " + util.toString(currentToken->Column));
    }
}

StatementNode * Parser::Assign(){
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

        return ExpresionBooleanaP(operatorNode);
    }else if(currentToken->Type == Op_LessThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        LessThanOperatorNode *operatorNode = new LessThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_LessEqualThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        LessEqualsThanOperatorNode *operatorNode = new LessEqualsThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_GreaterThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        GreaterThanOperatorNode *operatorNode = new GreaterThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;

        return ExpresionBooleanaP(operatorNode);

    }
    else if(currentToken->Type == Op_GreaterEqualThan)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        GreaterEqualsThanOperatorNode *operatorNode = new GreaterEqualsThanOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;

        return ExpresionBooleanaP(operatorNode);
    }
    else if(currentToken->Type == Op_NotEquals)
    {
        currentToken = nextToken();

        ExpresionNode *expresionNode = Expresion();
        NotEqualsOperatorNode *operatorNode = new NotEqualsOperatorNode();
        operatorNode->LeftOperandNode = paramNode;
        operatorNode->RightOperandNode = expresionNode;

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
        currentToken = nextToken();
        return intNode;
    }else if(currentToken->Type == Float)
    {
        FloatNode * floatNode = new FloatNode();
        floatNode->Value = currentToken->Lexeme;
        currentToken = nextToken();
        return floatNode;
    }else if(currentToken->Type == Bool)
    {
        BoolNode * boolNode = new BoolNode();
        boolNode->Value = currentToken->Lexeme;
        currentToken = nextToken();
        return boolNode;
    }else if(currentToken->Type == String)
    {
        StringNode * stringNode = new StringNode();
        stringNode->Value = currentToken->Lexeme;
        currentToken = nextToken();
        return stringNode;
    }else if(currentToken->Type == Binary)
    {
        BinaryNode * binaryNode = new BinaryNode();
        binaryNode->Value = currentToken->Lexeme;
        currentToken = nextToken();
        return binaryNode;
    }else if(currentToken->Type == Hexadecimal)
    {
        HexadecimalNode * hexadecimalNode = new HexadecimalNode();
        hexadecimalNode->Value = currentToken->Lexeme;
        currentToken = nextToken();
        return hexadecimalNode;
    }else if(currentToken->Type == Char)
    {
        CharNode * charNode = new CharNode();
        charNode->Value = currentToken->Lexeme;
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






