#-------------------------------------------------
#
# Project created by QtCreator 2016-09-24T16:37:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    map.cpp \
    doastar.cpp \
    node.cpp \
    weightedastar.cpp \
    pathdisplay.cpp \
    sequentialheuristics.cpp \
    integretedheuristics.cpp

HEADERS  += mainwindow.h \
    map.h \
    doastar.h \
    node.h \
    weightedastar.h \
    pathdisplay.h \
    minihp.h \
    sequentialheuristics.h \
    integretedheuristics.h

FORMS    += mainwindow.ui \
    pathdisplay.ui

DISTFILES += \
    map.txt
