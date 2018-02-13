
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
TARGET = lang_tests

DESTDIR = ../../bin

QT += core
QT += gui

SOURCES += main.cpp \
           TestModel.cpp \
           TestGrammar.cpp \
           TestStatistics.cpp \

INCLUDEPATH += $$PWD/..
DEFINES += TEST_DATA=\\\"$$PWD/../testdata\\\"

LIBS += -L$$DESTDIR -llang_model
