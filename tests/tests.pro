
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
TARGET = lang_tests

DESTDIR = ../../bin

QT += core
QT += gui

SOURCES += Main.cpp \
           TestLangFile.cpp \
           TestGrammar.cpp \
           TestStatistics.cpp \
           TestTools.cpp \

HEADERS += tests.h \

INCLUDEPATH += $$PWD/..
DEFINES += TEST_DATA=\\\"$$PWD/../testdata\\\"

LIBS += -L$$DESTDIR -llang_model
