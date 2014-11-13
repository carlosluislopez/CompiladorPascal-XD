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
    printnode.cpp

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
    ExpresionNode.h
