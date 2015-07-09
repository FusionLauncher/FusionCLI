#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T15:33:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = FusionCLI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

unix|win32: LIBS += -lLibFusion

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LibFusion/release/ -lLibFusion
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LibFusion/debug/ -lLibFusion
else:unix: LIBS += -L$$PWD/../LibFusion/ -lLibFusion

INCLUDEPATH += $$PWD/../LibFusion
DEPENDPATH += $$PWD/../LibFusion
