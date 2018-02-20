
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
TARGET = lang_db

DESTDIR = ../../bin

QT += core

SOURCES += Main.cpp \
           DbReader.cpp \
           Rule.cpp \

HEADERS += Rule.h
           DbReader.h \

INCLUDEPATH += $$PWD/..
DEFINES += TEST_DATA=\\\"$$PWD/../testdata\\\"

LIBS += -L$$DESTDIR -llang_model
