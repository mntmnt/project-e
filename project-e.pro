#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T15:34:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectCE
TEMPLATE = app

*-g++* {
QMAKE_CXXFLAGS += -std=gnu++11 #-std=c++0x,gnu++0x
}


SOURCES += main.cpp \
    win_specific.cpp

HEADERS  += \
    tray_icon.h \
    activity_driver.h

RESOURCES += \
    resources.qrc
