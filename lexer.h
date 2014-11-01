#ifndef LEXER_H
#define LEXER_H

#include "contentreader.h"
#include "token.h"
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexicalexception.h"

using namespace std;

class Lexer
{
public:
    Lexer(ContentReader *contentReader);
    Lexer(){}
    ~Lexer(){}
    Token * NextToken();
private:
    ContentReader *contentReader;
    char currentSymbol;
    typedef map<std::string, TokenType> Mapa;
    Mapa singleSymbolDictionary;
    Mapa doubleSymbolDictionary;
    Mapa tripleSymbolDictionary;
    Mapa reservedWordsDictionary;
    Mapa hexadecimalSymbolsDictionay;

    bool containsKey(Mapa, std::string);
    std::string toString(int);
	std::string toLower(string);
    std::string toLower(char);
    bool stateHTML;
    Token * NextHTMLToken();

};

#endif // LEXER_H
