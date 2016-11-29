#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T14:33:11
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Process_Manager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    gerenciador_cpu.cpp \
    read.cpp \
    gerenciador_mem.cpp \
    gerenciador_energy.cpp \
    gerenciador.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    include_lib.h \
    processo.h \
    gerenciador_mem.h \
    gerenciador_cpu.h \
    gerenciador_energy.h \
    gerenciador.h

FORMS    += mainwindow.ui

CONFIG += c++11

