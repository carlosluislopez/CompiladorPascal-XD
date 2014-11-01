#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "lexer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    string line;
    ifstream myfile ("C:\\Users\\carlo_000\\Desktop\\example.txt");

    string contenido = "";

    if (myfile.is_open())
    {
        while (getline (myfile, line))
        {
            //cout << line << '\n';
            contenido.append(line);
            contenido.append("\n");
        }
        myfile.close();

        cout << contenido << '\n';
    }
    else cout << "Unable to open file";

    ContentReader *reader = new ContentReader();
    reader->Content = contenido;

    Lexer *lexico = new Lexer(reader);

    Token *current = new Token();
    try
    {
        current = lexico->NextToken();
    }catch(LexicalException &lexEx)
    {
        cout << lexEx.what() << '\n';
    }

    while(current->Type != EndOfFile)
    {
        cout <<"Line: " << current->Line << " \tCol: " << current->Column << "\tType: " << current->Type << " \t" << "\tLexeme: " << current->Lexeme << endl;
        try
        {
            current = lexico->NextToken();
        }catch(LexicalException &lexEx)
        {
            cout << lexEx.what() << '\n';
            break;
        }
    }
    return a.exec();
}
