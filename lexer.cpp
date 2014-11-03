#include "lexer.h"

Lexer::Lexer(ContentReader *contentReader)
{
    stateHTML = true;
    this->contentReader = contentReader;
    currentSymbol = this->contentReader->NextSymbol();

    hexadecimalSymbolsDictionay.insert(make_pair("a", String));
    hexadecimalSymbolsDictionay.insert(make_pair("b", String));
    hexadecimalSymbolsDictionay.insert(make_pair("c", String));
    hexadecimalSymbolsDictionay.insert(make_pair("d", String));
    hexadecimalSymbolsDictionay.insert(make_pair("e", String));
    hexadecimalSymbolsDictionay.insert(make_pair("f", String));

    singleSymbolDictionary.insert(make_pair(string(";"), SemiColon));
    singleSymbolDictionary.insert(make_pair(string(","), Comma));
    singleSymbolDictionary.insert(make_pair(string("."), Dot));
    singleSymbolDictionary.insert(make_pair(string("("), LeftParenthesis));
    singleSymbolDictionary.insert(make_pair(string(")"), RightParenthesis));
    singleSymbolDictionary.insert(make_pair(string("["), LeftBrackets));
    singleSymbolDictionary.insert(make_pair(string("]"), RightBrackets));
    singleSymbolDictionary.insert(make_pair(string("{"), LeftCurlyBrackets));
    singleSymbolDictionary.insert(make_pair(string("}"), RightCurlyBrackets));
    singleSymbolDictionary.insert(make_pair(string("+"), Op_Sum));
    singleSymbolDictionary.insert(make_pair(string("-"), Op_Substract));
    singleSymbolDictionary.insert(make_pair(string("*"), Op_Multiply));
    singleSymbolDictionary.insert(make_pair(string("/"), Op_Divide));

    doubleSymbolDictionary.insert(make_pair(string(":"), Colon));
    doubleSymbolDictionary.insert(make_pair(string("="), Op_Equals));
    doubleSymbolDictionary.insert(make_pair(string(":="), Op_Assign));
    doubleSymbolDictionary.insert(make_pair(string("<>"), Op_NotEquals));
    doubleSymbolDictionary.insert(make_pair(string("<"), Op_LessThan));
    doubleSymbolDictionary.insert(make_pair(string(">"), Op_GreaterThan));
    doubleSymbolDictionary.insert(make_pair(string("<="), Op_LessEqualThan));
    doubleSymbolDictionary.insert(make_pair(string(">="), Op_GreaterEqualThan));
    doubleSymbolDictionary.insert(make_pair(string(".."), Range));

    tripleSymbolDictionary.insert(make_pair(string("<xd"), OP_LeftxD));
    tripleSymbolDictionary.insert(make_pair(string("xd>"), OP_RightxD));

    reservedWordsDictionary.insert(make_pair(string("div"), Rw_Div));
    reservedWordsDictionary.insert(make_pair(string("mod"), Rw_Mod));
    reservedWordsDictionary.insert(make_pair(string("not"), Rw_Not));
    reservedWordsDictionary.insert(make_pair(string("in"), Rw_In));
    reservedWordsDictionary.insert(make_pair(string("or"), Rw_Or));
    reservedWordsDictionary.insert(make_pair(string("and"), Rw_And));
    reservedWordsDictionary.insert(make_pair(string("if"), Rw_If));
    reservedWordsDictionary.insert(make_pair(string("while"), Rw_While));
    reservedWordsDictionary.insert(make_pair(string("read"), Rw_Read));
    reservedWordsDictionary.insert(make_pair(string("print"), Rw_Print));
    reservedWordsDictionary.insert(make_pair(string("else"), Rw_Else));
    reservedWordsDictionary.insert(make_pair(string("then"), Rw_Then));
    reservedWordsDictionary.insert(make_pair(string("array"), Rw_Array));
    reservedWordsDictionary.insert(make_pair(string("packed"), Rw_Packed));
    reservedWordsDictionary.insert(make_pair(string("to"), Rw_To));
    reservedWordsDictionary.insert(make_pair(string("begin"), Rw_Begin));
    reservedWordsDictionary.insert(make_pair(string("end"), Rw_End));

    reservedWordsDictionary.insert(make_pair(string("of"), Rw_Of));
    reservedWordsDictionary.insert(make_pair(string("record"), Rw_Record));
    reservedWordsDictionary.insert(make_pair(string("type"), Rw_Type));
    reservedWordsDictionary.insert(make_pair(string("for"), Rw_For));
    reservedWordsDictionary.insert(make_pair(string("label"), Rw_Label));
    reservedWordsDictionary.insert(make_pair(string("repeat"), Rw_Repeat));
    reservedWordsDictionary.insert(make_pair(string("with"), Rw_With));
    reservedWordsDictionary.insert(make_pair(string("const"), Rw_Const));
    reservedWordsDictionary.insert(make_pair(string("case"), Rw_Case));
    reservedWordsDictionary.insert(make_pair(string("function"), Rw_Function));
    reservedWordsDictionary.insert(make_pair(string("procedure"), Rw_Procedure));
    reservedWordsDictionary.insert(make_pair(string("program"), Rw_Program));
    reservedWordsDictionary.insert(make_pair(string("until"), Rw_Until));
    reservedWordsDictionary.insert(make_pair(string("do"), Rw_Do));
    reservedWordsDictionary.insert(make_pair(string("var"), Rw_Var));
    reservedWordsDictionary.insert(make_pair(string("downto"), Rw_Downto));

    reservedWordsDictionary.insert(make_pair(string("integer"), Rw_Int));
    reservedWordsDictionary.insert(make_pair(string("float"), Rw_Float));
    reservedWordsDictionary.insert(make_pair(string("string"), Rw_String));
    reservedWordsDictionary.insert(make_pair(string("char"), Rw_Char));
    reservedWordsDictionary.insert(make_pair(string("bool"), Rw_Bool));
}

bool Lexer::containsKey(Mapa mapa, string symbol)
{
    Mapa::iterator it = mapa.find(symbol);
    TokenType type;
    if(it != mapa.end())
    {
       type = it->second;
       return true;
    }
    return false;
}

std::string Lexer::toString(int obj)
{
    std::ostringstream objStream;
    objStream << obj;
    std::string objStr(objStream.str());
    return objStr;
}

string Lexer::toLower(string symbol)
{
    std::locale loc;
    std::string result;
    result = "";
    for (std::string::size_type i=0; i<symbol.length(); ++i)
       result+= std::tolower(symbol[i], loc);

    return result;
}

string Lexer::toLower(char symbol)
{
    std::locale loc;
    std::string result;
    result = "";

    result+= std::tolower(symbol, loc);

    return result;
}

Token * Lexer::NextToken()
 {
    string lexeme = "";
    int currentState = 0;
    Token *token = new Token();

    token->Column = contentReader->CurrentColumn;
    token->Line = contentReader->CurrentLine;

    string symbol;

    while (true)
    {
        if(stateHTML)
        {
            Token *tokenTemp = NextHTMLToken();
            if(tokenTemp != 0 && tokenTemp->Lexeme.length() > 0)
            {
                return tokenTemp;
            }
        }

        symbol = "";
        symbol += currentSymbol;
        switch (currentState)
        {
            case 0:
                if(isalpha(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 1;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '\0')
                {
                    currentState = 16;
                }
                else if (isspace(currentSymbol))
                {
                    currentState = 0;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (isdigit(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 3;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if(containsKey(this->singleSymbolDictionary, toLower(symbol)))
                {
                    lexeme += currentSymbol;
                    currentState = 7;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (containsKey(doubleSymbolDictionary, toLower(symbol)))
                {
                    lexeme += currentSymbol;
                    currentState = 8;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '\"')
                {
                    //lexeme += currentSymbol;
                    currentState = 20;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '\'')
                {
                    //lexeme += currentSymbol;
                    currentState = 30;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '%')
                {
                    //lexeme += currentSymbol;
                    currentState = 40;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '$')
                {
                    //lexeme += currentSymbol;
                    currentState = 50;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    throw LexicalException("Symbol " + symbol + " is not recognized; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                }
                break;
            case 1:
                if (isalnum(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 1;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 2;
                break;
            case 2:
                if(containsKey(reservedWordsDictionary, toLower(lexeme)))
                {
                    token->Lexeme = lexeme;
                    token->Type = reservedWordsDictionary[toLower(lexeme)];
                    return token;
                }
                else if (containsKey(tripleSymbolDictionary, toLower(lexeme + currentSymbol)))
                {
                    lexeme += currentSymbol;
                    currentState = 11;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    token->Lexeme = lexeme;
                    token->Type = Id;
                    return token;
                }
                break;
            case 3:
                if (isdigit(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 3;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (currentSymbol == '.')
                {
                    lexeme += currentSymbol;
                    currentState = 4;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 6;
                break;
            case 4:
                if (isdigit(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 5;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    throw LexicalException("A digit was expected; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                }
                break;
            case 5:
                if (isdigit(currentSymbol))
                {
                    lexeme += currentSymbol;
                    currentState = 5;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 12;
                break;
            case 6:
                token->Lexeme = lexeme;
                token->Type = Int;
                return token;
                break;
            case 7:
                if ((lexeme + symbol)=="//")
                {
                    lexeme="";
                    currentState = 60;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if ((lexeme + symbol)=="(*")
                {
                    lexeme = currentSymbol;
                    currentState = 61;
                    currentSymbol = contentReader->NextSymbol();
                }else
                {
                    token->Lexeme = lexeme;
                    token->Type = singleSymbolDictionary[toLower(lexeme)];
                    return token;
                }
                break;
            case 8:
                if (containsKey(doubleSymbolDictionary, toLower(lexeme)))
                {
                    lexeme += currentSymbol;
                    currentState = 9;
                    currentSymbol = contentReader->NextSymbol();
                }
                else if (containsKey(tripleSymbolDictionary, toLower((lexeme + symbol))))
                {
                    lexeme += currentSymbol;
                    currentState = 10;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 9;
                break;
            case 9:
                token->Lexeme = lexeme;
                token->Type = doubleSymbolDictionary[toLower(lexeme)];
                return token;
                break;
            case 10:
                if (toLower(currentSymbol) != "d")
                    throw LexicalException("D is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));

                lexeme += currentSymbol;
                currentSymbol = contentReader->NextSymbol();
                token->Type = tripleSymbolDictionary[toLower(lexeme)];

                if(token->Type == OP_RightxD)
                    stateHTML = true;;
                currentState = 0;
                break;
            case 11:
                token->Lexeme = lexeme;
                token->Type = tripleSymbolDictionary[toLower(lexeme)];

                if(token->Type == OP_RightxD)
                    stateHTML = true;

                currentState = 0;
                break;
            case 12:
                token->Lexeme = lexeme;
                token->Type = Float;
                return token;
                break;
            case 16:
                token->Type = EndOfFile;
                return token;
                break;
            case 20:
                if (currentSymbol == '\"')
                {
                    //lexeme += currentSymbol;
                    currentState = 21;
                    currentSymbol = contentReader->NextSymbol();
                }
                else  if (currentSymbol=='\0' || currentSymbol=='\n')
                {
                    throw LexicalException("\" is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                }
                else
                {
                    lexeme += currentSymbol;
                    currentState = 20;
                    currentSymbol = contentReader->NextSymbol();
                }
                break;
            case 21:
                if (currentSymbol == '\"')
                {
                    lexeme += currentSymbol;
                    currentState = 20;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 22;
                break;
            case 22:
                token->Lexeme = lexeme;
                token->Type = String;
                return token;
                break;
            case 30:
                if (currentSymbol == '\'')
                {
                    //lexeme += currentSymbol;
                    currentState = 31;
                    currentSymbol = contentReader->NextSymbol();
                }
                else  if (currentSymbol=='\0' || currentSymbol=='\n')
                {
                    throw LexicalException("\' is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                }
                else
                {
                    lexeme += currentSymbol;
                    currentState = 30;
                    currentSymbol = contentReader->NextSymbol();
                }
                break;
            case 31:
                if (currentSymbol == '\'')
                {
                    lexeme += currentSymbol;
                    currentState = 30;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    currentState = 32;
                break;
            case 32:
                token->Lexeme = lexeme;
                token->Type = String;
                return token;
                break;
            case 40:
                if (currentSymbol=='0' || currentSymbol=='1')
                {
                    lexeme += currentSymbol;
                    currentState = 41;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    throw LexicalException("0 or 1 is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                break;
            case 41:
                if (currentSymbol=='0' || currentSymbol=='1')
                {
                    lexeme += currentSymbol;
                    currentState = 41;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    currentState = 43;
                }
                break;
            case 43:
                token->Lexeme = lexeme;
                token->Type = Binary;
                return token;
                break;
            case 50:
                if (isdigit(currentSymbol) || containsKey(hexadecimalSymbolsDictionay, toLower(currentSymbol)))
                {
                    lexeme += currentSymbol;
                    currentState = 51;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                    throw LexicalException("A to F is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                break;
            case 51:
                if (isdigit(currentSymbol) || containsKey(hexadecimalSymbolsDictionay, toLower(currentSymbol)))
                {
                    lexeme += currentSymbol;
                    currentState = 51;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    currentState = 52;
                }
                break;
            case 52:
                token->Lexeme = lexeme;
                token->Type = Hexadecimal;
                return token;
                break;
            case 60:
                if (currentSymbol == '\n' || currentSymbol == '\0')
                {
                    currentState = 0;
                    currentSymbol = contentReader->NextSymbol();
                }
                else
                {
                    currentSymbol = contentReader->NextSymbol();
                    currentState = 60;
                }
                break;
            case 61:
                if ((lexeme + symbol)=="*)")
                {
                    lexeme = "";
                    currentState = 0;
                    currentSymbol = contentReader->NextSymbol();
                }
                else  if (currentSymbol=='\0')
                {
                    throw LexicalException("* is not found; Line: " + toString(contentReader->CurrentLine) + ", Column: " + toString(contentReader->CurrentColumn));
                }
                else
                {
                    lexeme = currentSymbol;
                    currentSymbol = contentReader->NextSymbol();
                    currentState = 61;
                }
                break;
            default:
                break;
        }
    }
    return token;
 }

Token * Lexer::NextHTMLToken(){
    string lexeme = "";
    Token *token = new Token();

    token->Column = contentReader->CurrentColumn;
    token->Line = contentReader->CurrentLine;

    string xd = "";

    while (true)
    {
        if(xd.length() < 3){
            xd += currentSymbol;
        }
        else{
            for (std::string::size_type i = 1; i < xd.length(); ++i)
            {
                xd[i-1] = xd[i];
            }
            xd[xd.length()-1] = currentSymbol;
        }

        if(containsKey(this->tripleSymbolDictionary, toLower(xd)))
        {
            currentSymbol = contentReader->NextSymbol();
            TokenType type;
            type = tripleSymbolDictionary[toLower(xd)];
            stateHTML = false;

            string lexemTemp = lexeme.substr(0, lexeme.length()-3);

            token->Lexeme = lexemTemp;
            token->Type = HTML;
            return token;
        }

        lexeme += currentSymbol;
        currentSymbol = contentReader->NextSymbol();

        if (currentSymbol == '\0')
        {
            stateHTML = false;
            token->Lexeme = lexeme;
            token->Type = HTML;
            return token;
        }
    }
    return token;
}
