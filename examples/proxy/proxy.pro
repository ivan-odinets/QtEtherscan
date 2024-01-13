QT += core
QT -= gui

TARGET = proxy
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../../QtEtherscan.pri)
