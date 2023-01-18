INCLUDEPATH += $$PWD

DEFINES     += QTES_VERSION='\\"0.0.2\\"'

QT          += core network

CONFIG      += c++17

SOURCES += \
    $$PWD/src/api.cpp \
    $$PWD/src/networking.cpp \
    $$PWD/src/types/accountbalance.cpp \
    $$PWD/src/types/block.cpp \
    $$PWD/src/types/blockandunclerewards.cpp \
    $$PWD/src/types/contractexecutionstatus.cpp \
    $$PWD/src/types/erc1155tokentransferevent.cpp \
    $$PWD/src/types/erc20tokentransferevent.cpp \
    $$PWD/src/types/erc721tokentransferevent.cpp \
    $$PWD/src/types/estimatedblockcountdown.cpp \
    $$PWD/src/types/ether2supply.cpp \
    $$PWD/src/types/etherprice.cpp \
    $$PWD/src/types/eventlogs.cpp \
    $$PWD/src/types/gasoracle.cpp \
    $$PWD/src/types/global.cpp \
    $$PWD/src/types/internaltransaction.cpp \
    $$PWD/src/types/nodescount.cpp \
    $$PWD/src/types/nodessize.cpp \
    $$PWD/src/types/transaction.cpp \
    $$PWD/src/types/uncle.cpp

HEADERS += \
    $$PWD/QtEtherscan.h \
    $$PWD/src/api.h \
    $$PWD/src/networking.h \
    $$PWD/src/types/accountbalance.h \
    $$PWD/src/types/block.h \
    $$PWD/src/types/blockandunclerewards.h \
    $$PWD/src/types/contractexecutionstatus.h \
    $$PWD/src/types/erc1155tokentransferevent.h \
    $$PWD/src/types/erc20tokentransferevent.h \
    $$PWD/src/types/erc721tokentransferevent.h \
    $$PWD/src/types/estimatedblockcountdown.h \
    $$PWD/src/types/ether.h \
    $$PWD/src/types/ether2supply.h \
    $$PWD/src/types/etherprice.h \
    $$PWD/src/types/eventlogs.h \
    $$PWD/src/types/gasoracle.h \
    $$PWD/src/types/global.h \
    $$PWD/src/types/internaltransaction.h \
    $$PWD/src/types/nodescount.h \
    $$PWD/src/types/nodessize.h \
    $$PWD/src/types/transaction.h \
    $$PWD/src/types/uncle.h

OTHER_FILES += \
    $$PWD/README.md
