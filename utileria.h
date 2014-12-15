#ifndef UTILERIA_H
#define UTILERIA_H

#include <utility>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

class Utileria
{
public:
    Utileria();
    string toString(int);
    string toStringFloat(float);
    string toStringBool(bool);
    string toStringChar(char);
    string toLower(string);
    string toLower(char);
    string getMeIdentation(int identation);
    int toIntFromString(string);
    float toFloatFromString(string);
    bool toBoolFromString(string);
};

#endif // UTILERIA_H
