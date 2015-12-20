#-------------------------------------------------
#
# Project created by QtCreator 2015-11-12T10:01:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myrectitem.cpp \
    mypixmapitem.cpp \
    tlrectitem.cpp \
    trectitem.cpp \
    clrectitem.cpp \
    crectitem.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    myrectitem.h \
    mypixmapitem.h \
    tlrectitem.h \
    trectitem.h \
    clrectitem.h \
    crectitem.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    rsc.qrc
