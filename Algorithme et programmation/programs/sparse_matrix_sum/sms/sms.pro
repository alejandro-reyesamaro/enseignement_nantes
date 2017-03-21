#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T14:51:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = sms
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    parser.cpp

HEADERS += \
    parser.h \
    types.h

OTHER_FILES += \
    test.txt
