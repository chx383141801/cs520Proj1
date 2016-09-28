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
    node.cpp

HEADERS  += mainwindow.h \
    map.h \
    node.h

FORMS    += mainwindow.ui

DISTFILES += \
    map.txt
