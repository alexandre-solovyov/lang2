
QT -= gui

TARGET = model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += model.cpp

HEADERS += model.h \
           model_global.h 
