QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        helper.cpp \
        main.cpp \
        textmodel.cpp \
        wordslist.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/..

HEADERS += \
    helper.h \
    textmodel.h \
    wordslist.h

DESTDIR = ../../bin
LIBS += -L$$DESTDIR -llang_model

DISTFILES += \
    AddPanel.qml \
    InfoRect.qml \
    main.qml \
    TextField.qml \
    TextVisuArea.qml \
    Word.qml \
    
