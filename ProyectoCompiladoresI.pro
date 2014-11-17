#-------------------------------------------------
#
# Project created by QtCreator 2014-10-13T13:38:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ProyectoCompiladoresI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    token.cpp \
    contentreader.cpp \
    lexer.cpp \
    parser.cpp \
    utileria.cpp \
    printnode.cpp \
    stringtype.cpp \
    fieldaccesor.cpp \
    arrayaccesor.cpp \
    idnode.cpp \
    intnode.cpp \
    floatnode.cpp \
    boolnode.cpp \
    stringnode.cpp \
    binarynode.cpp \
    hexadecimalnode.cpp \
    charnode.cpp \
    multiplyoperatornode.cpp \
    divisionoperatornode.cpp \
    sumoperatornode.cpp \
    substractoperatornode.cpp \
    equalsoperatornode.cpp \
    greaterequalsthanoperatornode.cpp \
    greaterthanoperatornode.cpp \
    lessequalsthanoperatornode.cpp \
    lessthanoperatornode.cpp \
    notequalsoperatornode.cpp \
    unaryoperator.cpp \
    notoperatornode.cpp \
    divisionintegeroperationnode.cpp \
    modoperationnode.cpp \
    expoperationnode.cpp

HEADERS += \
    token.h \
    lexicalexception.h \
    contentreader.h \
    lexer.h \
    parser.h \
    ParserException.h \
    utileria.h \
    StatementNode.h \
    printnode.h \
    ExpresionValue.h \
    BaseType.h \
    ExpresionNode.h \
    stringtype.h \
    Accesor.h \
    fieldaccesor.h \
    arrayaccesor.h \
    idnode.h \
    intnode.h \
    floatnode.h \
    boolnode.h \
    stringnode.h \
    binarynode.h \
    hexadecimalnode.h \
    charnode.h \
    BinaryOperatorNode.h \
    multiplyoperatornode.h \
    divisionoperatornode.h \
    sumoperatornode.h \
    substractoperatornode.h \
    equalsoperatornode.h \
    greaterequalsthanoperatornode.h \
    greaterthanoperatornode.h \
    lessequalsthanoperatornode.h \
    lessthanoperatornode.h \
    notequalsoperatornode.h \
    unaryoperator.h \
    notoperatornode.h \
    ExpresionTree.h \
    SyntaxTree.h \
    divisionintegeroperationnode.h \
    modoperationnode.h \
    expoperationnode.h
