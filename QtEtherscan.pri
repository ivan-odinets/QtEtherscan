INCLUDEPATH += $$PWD

DEFINES     += QTES_VERSION='\\"0.0.1\\"'

QT          += core network

CONFIG      += c++17

SOURCES += \
    $$PWD/src/networking.cpp \
    $$PWD/src/qtetherscan.cpp \
    $$PWD/src/types/accountbalance.cpp

HEADERS += \
    $$PWD/QtEtherscan.h \
    $$PWD/src/networking.h \
    $$PWD/src/qtetherscan.h \
    $$PWD/src/types/accountbalance.h \
    $$PWD/src/types/etherbalance.h

OTHER_FILES += \
    $$PWD/README.md
