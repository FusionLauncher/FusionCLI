QT       += core gui sql
QT       += network
QT       += webkit


DESTDIR = ../OUT
MOC_DIR = BUILD
OBJECTS_DIR = BUILD


TARGET = FusionCLI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fusioncli.cpp

LIBS += -lLibFusion
LIBS += -L$$PWD/../OUT -lLibFusion

INCLUDEPATH += $$PWD/../LibFusion/LibFusion
DEPENDPATH += $$PWD/../LibFusion/LibFusion

HEADERS += \
    fusioncli.h
