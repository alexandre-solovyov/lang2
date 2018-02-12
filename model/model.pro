
QT -= gui

TARGET = model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += model.cpp \
           grammar.cpp \
           grammarrule.cpp \
           grammarset.cpp \
           eg_one.cpp \
           eg_trans.cpp \
           exercise.cpp \
           itense.cpp \
           deptense.cpp \
           stdtense.cpp \

HEADERS += model.h \
           model_global.h \
           grammar.h \
           context.h \
           exercise.h \
           grammarrule.h \
           grammarset.h \
           igenerator.h \ 
           itense.h \
           deptense.h \
           stdtense.h \
           eg_one.h \
           eg_trans.h \

INCLUDEPATH += $$PWD/..
