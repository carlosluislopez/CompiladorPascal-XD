#include "contentreader.h"

ContentReader::ContentReader()
{
    CurrentLine = 1;
    CurrentColumn = 0;
    currentPosition=0;
}

char ContentReader::NextSymbol()
{
    if (currentPosition < Content.length())
    {
        char currentSymbol = Content[currentPosition++];
        if (currentSymbol == '\n')
        {
            CurrentLine++;
            CurrentColumn = 1;
        }
        else
            CurrentColumn++;

        //putchar (tolower(c));
        //return tolower(currentSymbol);// currentSymbol;
        return currentSymbol;// currentSymbol;
    }
    else
    {
        return '\0';
    }
}

unsigned int ContentReader::GetCurrentPosition()
{
    return this->currentPosition;
}

