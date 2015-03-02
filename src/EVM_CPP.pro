#-------------------------------------------------
#
# Project created by QtCreator 2014-07-14T00:35:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EVM_CPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videothread.cpp \
    process.cpp \
    magnify.cpp \
    paramcontroler.cpp

HEADERS  += mainwindow.h \
    videothread.h \
    process.h \
    magnify.h \
    error.h \
    paramcontroler.h

FORMS    += mainwindow.ui \
    paramcontroler.ui

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += `pkg-config --libs opencv` -ldl
