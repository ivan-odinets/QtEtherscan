QT += core
QT -= gui

TARGET = balance_monitor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../../QtEtherscan.pri)
