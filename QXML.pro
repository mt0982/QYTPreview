#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T10:31:27
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QXML
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documentparser.cpp

HEADERS  += mainwindow.h \
    documentparser.h

FORMS    += mainwindow.ui
