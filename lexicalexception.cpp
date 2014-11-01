#include "lexicalexception.h"

LexicalException::LexicalException(string s)
{
    msg = s;
}


string LexicalException::message()
{
    return msg;
}
