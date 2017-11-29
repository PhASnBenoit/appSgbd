#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T08:19:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = essaiQMYSQL
TEMPLATE = app

# IMPORTANT A RAJOUTER POUR LA CROSS COMPILATION
#target.path = /home/pi
#INSTALLS += target
#-----------------------------------------------

SOURCES += main.cpp \
    cihmappsgbd.cpp

HEADERS  += \
    cihmappsgbd.h

FORMS    += \
    cihmappsgbd.ui
