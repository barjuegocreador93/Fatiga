#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T16:11:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = fatiga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../build-fatiga-Desktop-Debug/qcustomplot.cpp \
    ../rainflow/rainflow.cpp \
    archivo.cpp

HEADERS  += mainwindow.h \
    ../build-fatiga-Desktop-Debug/qcustomplot.h \
    ../rainflow/rainflow.h \
    archivo.h

FORMS    += mainwindow.ui
