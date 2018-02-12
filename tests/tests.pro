
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread

QT += core
QT += gui

SOURCES += main.cpp \
           TestModel.cpp \
           TestGrammar.cpp \

INCLUDEPATH += $$PWD/..
DEFINES += TEST_DATA=\\\"$$PWD/../testdata\\\"

CONFIG(debug)
{
  LIBS += -L$$OUT_PWD/../model/debug -lmodel
}

CONFIG(release)
{
  LIBS += -L$$OUT_PWD/../model/release -lmodel
}

