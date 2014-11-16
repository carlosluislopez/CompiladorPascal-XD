#include "utileria.h"

Utileria::Utileria()
{
}


std::string Utileria::toString(int obj)
{
    std::ostringstream objStream;
    objStream << obj;
    std::string objStr(objStream.str());
    return objStr;
}

string Utileria::toLower(string symbol)
{
    std::locale loc;
    std::string result;
    result = "";
    for (std::string::size_type i = 0; i < symbol.length(); ++i)
       result+= std::tolower(symbol[i], loc);

    return result;
}

string Utileria::toLower(char symbol)
{
    std::locale loc;
    std::string result;
    result = "";

    result+= std::tolower(symbol, loc);

    return result;
}


string Utileria::getMeIdentation(int identation)
{
    std::string str = "";
    for (int i = 0; i < identation; i++)
        str += " ";
    return str;
}
