#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T15:11:23
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QArtNet
TEMPLATE = lib

DEFINES += QARTNET_LIBRARY

SOURCES += qartnet.cpp

HEADERS += qartnet.h\
        qartnet_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
