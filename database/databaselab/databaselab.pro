#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T12:40:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = databaselab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    dbconnector.cpp \
    showdata.cpp \
    caigoulog.cpp \
    showdingd.cpp \
    form.cpp \
    mycombobox.cpp \
    chuhuolog.cpp \
    sell.cpp \
    showsell.cpp

HEADERS += \
        widget.h \
    dbconnector.h \
    showdata.h \
    caigoulog.h \
    showdingd.h \
    form.h \
    mycombobox.h \
    chuhuolog.h \
    sell.h \
    showsell.h

FORMS += \
        widget.ui \
    showdata.ui \
    caigoulog.ui \
    showcaigou.ui \
    showdingd.ui \
    form.ui \
    chuhuolog.ui \
    sell.ui \
    showsell.ui

QT+=sql

CONFIG +=console

DISTFILES +=

RESOURCES += \
    background.qrc
