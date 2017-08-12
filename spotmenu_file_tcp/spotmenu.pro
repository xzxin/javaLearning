#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T03:50:16
#
#-------------------------------------------------

QT       += core gui

TARGET = spotmenu
TEMPLATE = app


SOURCES += main.cpp\
        spotmenu.cpp \
    qcustomplot.cpp \
    spi_io_qt.c \
    serial.c \
    usartrcv.c \
    tcp.cpp \
    filewrite.cpp

HEADERS  += spotmenu.h \
    qcustomplot.h \
    spi_io_qt.h \
    spidev.h \
    serial.h \
    usartrcv.h \
    filewrite.h \
    tcp.h

FORMS    += spotmenu.ui
