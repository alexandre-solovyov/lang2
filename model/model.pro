
QT -= gui

TARGET = model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += model.cpp \
           grammar.cpp \
           eg_one.cpp \
           eg_trans.cpp \

HEADERS += model.h \
           model_global.h \
           grammar.h \
           exercise.h \
           igenerator.h \ 
           eg_one.h \
           eg_trans.h \

