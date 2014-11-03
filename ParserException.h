#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class ParserException
{
public:
    //LexicalException();
    ParserException(const string m = "Lexical Exception") : msg(m) { }
    //~LexicalException(void);
    const char* what() {return msg.c_str(); }
private:
    string msg;
};

#endif // PARSEREXCEPTION_H
