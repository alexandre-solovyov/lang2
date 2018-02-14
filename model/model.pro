
QT -= gui

TARGET = lang_model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ../../bin

SOURCES +=           \
    DepTense.cpp     \
    EG_Forms.cpp     \
    EG_One.cpp       \
    EG_Trans.cpp     \
    Exercise.cpp     \
    Grammar.cpp      \
    GrammarRule.cpp  \
    GrammarSet.cpp   \
    ITense.cpp       \
    LangFile.cpp     \
    Statistics.cpp   \
    StdModel.cpp     \
    StdTense.cpp     \
    Tools.cpp        \

HEADERS += \
    model_global.h   \
    DepTense.h       \
    EG_Forms.h       \
    EG_One.h         \
    EG_Trans.h       \
    Exercise.h       \
    Grammar.h        \
    GrammarRule.h    \
    GrammarSet.h     \
    IGenerator.h     \
    ITense.h         \
    LangFile.h       \
    Statistics.h     \
    StdModel.h       \
    StdTense.h       \
    Tools.h          \

INCLUDEPATH += $$PWD/..
