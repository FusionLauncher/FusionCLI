QT       += core gui sql
QT       += network
QT       += webkit

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QT       += webkitwidgets
#endif


DESTDIR = ../OUT
MOC_DIR = ../BUILD
OBJECTS_DIR = ../BUILD


TARGET = FusionCLI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fusioncli.cpp

LIBS += -lLibFusion
LIBS += -L$$PWD/../OUT -lLibFusion

INCLUDEPATH += $$PWD/../LibFusion
DEPENDPATH += $$PWD/../LibFusion

HEADERS += \
    fusioncli.h
