#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T10:31:27
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QXML
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documentparser.cpp \
    networkmanager.cpp \
    imagenetworkmanager.cpp

HEADERS  += mainwindow.h \
    documentparser.h \
    networkmanager.h \
    imagenetworkmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
