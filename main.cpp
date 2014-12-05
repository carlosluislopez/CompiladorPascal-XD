#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "lexer.h"
#include "parser.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    string line;

    ifstream myfile ("C:\\Users\\carlo_000\\Desktop\\example.txt");
    //ifstream myfile ("C:\\Users\\clopez\\Documents\\UNITEC\\Compiladores\\example.txt");
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
    Parser *parser = new Parser(lexico);

    try
    {
        list<StatementNode*> *listaStatement = parser->Parse();
        cout << "Sintaxis Correcta" << '\n';

        string xml = "";
        for(std::list<StatementNode*>::iterator it = listaStatement->begin(); it != listaStatement->end(); it++)
        {
            StatementNode *sentence = *it;
            xml += sentence->ToXML(0);
            //sentence->ValidateSemantics();
        }

        cout << xml << '\n';

    }catch(LexicalException &lexEx)
    {
        cout << lexEx.what() << '\n';
    }
    catch(ParserException &parEx)
    {
        cout << parEx.what() << '\n';
    }
    catch(SemanticException &semEx)
    {
        cout << semEx.what() << '\n';
    }

//    while(current->Type != EndOfFile)
//    {
//        cout <<"Line: " << current->Line << " \tCol: " << current->Column << "\tType: " << current->Type << " \t" << "\tLexeme: " << current->Lexeme << endl;
//        try
//        {
//            current = lexico->NextToken();
//        }catch(LexicalException &lexEx)
//        {
//            cout << lexEx.what() << '\n';
//            break;
//        }
//    }
    return a.exec();
}
