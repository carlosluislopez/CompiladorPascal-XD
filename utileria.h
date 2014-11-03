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
    string toLower(string);
    string toLower(char);
};

#endif // UTILERIA_H
