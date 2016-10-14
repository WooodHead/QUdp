QT += core network
QT -= gui

CONFIG += c++14

LIBS += -ltjlutils

TARGET = QUdp
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += include/

TEMPLATE = app

SOURCES += src/main.cpp \
           src/qudpserver.cpp

HEADERS += include/qudpserver.h \
    include/qabstractpacketprocessor.h \
    include/qudppacketprocessor.h
