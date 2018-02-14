
QT -= gui

TARGET = lang_model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ../../bin

SOURCES += Model.cpp \
           Grammar.cpp \
           GrammarRule.cpp \
           GrammarSet.cpp \
           EG_One.cpp \
           EG_Trans.cpp \
           Exercise.cpp \
           ITense.cpp \
           DepTense.cpp \
           Statistics.cpp \
           StdTense.cpp \
           Tools.cpp \

HEADERS += Model.h \
           model_global.h \
           Grammar.h \
           Context.h \
           Exercise.h \
           GrammarRule.h \
           GrammarSet.h \
           IGenerator.h \ 
           ITense.h \
           DepTense.h \
           Statistics.h \
           StdTense.h \
           EG_One.h \
           EG_Trans.h \
           Tools.h \

INCLUDEPATH += $$PWD/..
