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

std::string Utileria::toStringFloat(float obj)
{
    std::ostringstream objStream;
    objStream << obj;
    std::string objStr(objStream.str());
    return objStr;
}


std::string Utileria::toStringBool(bool obj)
{
    std::ostringstream objStream;
    objStream << boolalpha << obj;
    std::string objStr(objStream.str());
    return objStr;
}

std::string Utileria::toStringChar(char obj)
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
    for (int i = 0; i < (identation * 4); i++)
        str += " ";
    return str;
}



int Utileria::toIntFromString(string text)
{
    int result;
    stringstream convert(text);

    if (!(convert >> result) )
        result = 0;

    return result;
}

float Utileria::toFloatFromString(string text)
{
    float result;
    stringstream convert(text);

    if (!(convert >> result) )
        result = 0;

    return result;
}


bool Utileria::toBoolFromString(string text)
{
    bool result = false;
    if(toLower(text) == "true")
        return true;

    if(toLower(text) == "false")
        return false;

    return result;
}








