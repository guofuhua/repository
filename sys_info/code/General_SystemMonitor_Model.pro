#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T09:09:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = General_SystemMonitor_Model
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp         \
    SysInfo/QSysMem.cpp \
    SysInfo/CSysMemInfoElement.cpp \
    SysInfo/CGetProcessInfo.cpp \
    SysInfo/QRegisterProcess.cpp \
    SysInfo/CGetCPUInfo.cpp \
    SysInfo/QGetCPUInfo.cpp \
    SysInfo/CSysInfoElement.cpp


HEADERS +=              \
    SysInfo/QSysMem.h \
    SysInfo/CSysMemInfoElement.h \
    SysInfo/CGetProcessInfo.h \
    SysInfo/QRegisterProcess.h \
    SysInfo/CGetCPUInfo.h \
    SysInfo/QGetCPUInfo.h \
    SysInfo/CSysInfoElement.h


INCLUDEPATH +=../../../../Common
INCLUDEPATH +=../../../../ProjectCommon
