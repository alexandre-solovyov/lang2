
QT -= gui

TARGET = model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += model.cpp \
           eg_one.cpp \

HEADERS += model.h \
           model_global.h \
           exercise.h \
           igenerator.h \ 
           eg_one.h \

