#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T19:58:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TilesPuzzle
TEMPLATE = app


SOURCES += main.cpp \
    puzzle.cpp \
    tile.cpp \
    option.cpp \
    moves.cpp \
    timer.cpp

HEADERS  += \
    puzzle.h \
    tile.h \
    option.h \
    moves.h \
    timer.h

FORMS    +=

RESOURCES += \
    images.qrc
