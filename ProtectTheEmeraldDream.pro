#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T13:30:44
#
#-------------------------------------------------

QT       += core gui \
           multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProtectTheEmeraldDream
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    level.cpp \
    player.cpp \
    button.cpp \
    wrath.cpp \
    input.cpp \
    enemies.cpp

HEADERS  += \
    game.h \
    level.h \
    player.h \
    button.h \
    wrath.h \
    input.h \
    enemies.h

FORMS    +=

CONFIG += c++11

RESOURCES += \
    res.qrc
