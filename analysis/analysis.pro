
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
TARGET = lang_analysis

DESTDIR = ../../bin

QT += core

SOURCES += Main.cpp \

INCLUDEPATH += $$PWD/..
DEFINES += TEST_DATA=\\\"$$PWD/../testdata\\\"

LIBS += -L$$DESTDIR -llang_model
