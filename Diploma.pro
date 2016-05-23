#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T13:51:02
#
#-------------------------------------------------

QT       += core gui network location positioning sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diploma
TEMPLATE = app
MOBILITY = multimedia

SOURCES += main.cpp\
        mainwindow.cpp \
    tiles.cpp \
    parentpixmapgraph.cpp \
    applicationsettings.cpp \
    database.cpp \
    tilescache.cpp

HEADERS  += mainwindow.h \
    tiles.h \
    parentpixmapgraph.h \
    applicationsettings.h \
    database.h \
    tilescache.h

FORMS    += mainwindow.ui \
    applicationsettings.ui
