#ifndef SEMANTICEXCEPTION_H
#define SEMANTICEXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

class SemanticException
{
public:
    //LexicalException();
    SemanticException(const string m = "Semantic Exception") : msg(m) { }
    //~LexicalException(void);
    const char* what() { return msg.c_str(); }
private:
    string msg;
};

#endif // SEMANTICEXCEPTION_H
