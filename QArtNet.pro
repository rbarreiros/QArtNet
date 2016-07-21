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

SOURCES += qartnet.cpp \
    qartnetnode.cpp \
    qartnetpoll.cpp \
    qartnetreply.cpp

HEADERS += qartnet.h\
        qartnet_global.h \
    qartnetnode.h \
    common.h \
    qartnetpoll.h \
    qartnetreply.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
