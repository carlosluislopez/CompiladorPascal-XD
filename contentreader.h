#ifndef CONTENTREADER_H
#define CONTENTREADER_H

#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

class ContentReader
{
public:
    ContentReader();
    char NextSymbol();
    string Content;
    unsigned int CurrentLine;
    unsigned int CurrentColumn;
    unsigned int GetCurrentPosition();
private:
    unsigned int currentPosition;
};

#endif // CONTENTREADER_H
