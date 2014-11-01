#ifndef LEXICALEXCEPTION_H
#define LEXICALEXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class LexicalException
{
public:
    //LexicalException();
    LexicalException(const string m = "Lexical Exception") : msg(m) { }
    //~LexicalException(void);
    const char* what() {return msg.c_str(); }
private:
    string msg;
};

#endif // LEXICALEXCEPTION_H
