#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T13:51:02
#
#-------------------------------------------------

QT       += core gui network location positioning
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diploma
TEMPLATE = app
MOBILITY = multimedia

SOURCES += main.cpp\
        mainwindow.cpp \
    tiles.cpp \
    parentpixmapgraph.cpp

HEADERS  += mainwindow.h \
    tiles.h \
    parentpixmapgraph.h

FORMS    += mainwindow.ui
