
include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread

QT += core

SOURCES += main.cpp \
           TestModel.cpp \

INCLUDEPATH += $$PWD/..

CONFIG(debug)
{
  LIBS += -L$$OUT_PWD/../model/Debug -lmodel
}

