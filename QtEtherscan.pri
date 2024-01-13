INCLUDEPATH += $$PWD

DEFINES     += QTES_VERSION='\\"0.0.3\\"'

QT          += core network

CONFIG      += c++17

SOURCES += \
    $$PWD/src/api.cpp \
    $$PWD/src/networking.cpp \
    $$PWD/src/types/accountbalance.cpp \
    $$PWD/src/types/beaconchainwithdrawal.cpp \
    $$PWD/src/types/block.cpp \
    $$PWD/src/types/blockandunclerewards.cpp \
    $$PWD/src/types/contractcreator.cpp \
    $$PWD/src/types/contractexecutionstatus.cpp \
    $$PWD/src/types/contractsourcecode.cpp \
    $$PWD/src/types/erc1155tokentransferevent.cpp \
    $$PWD/src/types/erc20tokentransferevent.cpp \
    $$PWD/src/types/erc721tokentransferevent.cpp \
    $$PWD/src/types/estimatedblockcountdown.cpp \
    $$PWD/src/types/ether2supply.cpp \
    $$PWD/src/types/etherprice.cpp \
    $$PWD/src/types/eventlogs.cpp \
    $$PWD/src/types/gasoracle.cpp \
    $$PWD/src/types/proxy/eth_block.cpp \
    $$PWD/src/types/proxy/eth_log.cpp \
    $$PWD/src/types/proxy/eth_transaction.cpp \
    $$PWD/src/types/internaltransaction.cpp \
    $$PWD/src/types/nodescount.cpp \
    $$PWD/src/types/nodessize.cpp \
    $$PWD/src/types/proxy/eth_transactionreceipt.cpp \
    $$PWD/src/types/transaction.cpp \
    $$PWD/src/types/uncle.cpp

HEADERS += \
    $$PWD/QtEtherscan.h \
    $$PWD/src/api.h \
    $$PWD/src/networking.h \
    $$PWD/src/types/accountbalance.h \
    $$PWD/src/types/beaconchainwithdrawal.h \
    $$PWD/src/types/block.h \
    $$PWD/src/types/blockandunclerewards.h \
    $$PWD/src/types/constants.h \
    $$PWD/src/types/contractcreator.h \
    $$PWD/src/types/contractexecutionstatus.h \
    $$PWD/src/types/contractsourcecode.h \
    $$PWD/src/types/enums.h \
    $$PWD/src/types/erc1155tokentransferevent.h \
    $$PWD/src/types/erc20tokentransferevent.h \
    $$PWD/src/types/erc721tokentransferevent.h \
    $$PWD/src/types/estimatedblockcountdown.h \
    $$PWD/src/types/ether.h \
    $$PWD/src/types/ether2supply.h \
    $$PWD/src/types/etherprice.h \
    $$PWD/src/types/eventlogs.h \
    $$PWD/src/types/gasoracle.h \
    $$PWD/src/types/jsonobjectslist.h \
    $$PWD/src/types/proxy/eth_block.h \
    $$PWD/src/types/proxy/eth_blocknumber.h \
    $$PWD/src/types/proxy/eth_gasprice.h \
    $$PWD/src/types/proxy/eth_helper.h \
    $$PWD/src/types/proxy/eth_log.h \
    $$PWD/src/types/proxy/eth_response.h \
    $$PWD/src/types/proxy/eth_transaction.h \
    $$PWD/src/types/internaltransaction.h \
    $$PWD/src/types/nodescount.h \
    $$PWD/src/types/nodessize.h \
    $$PWD/src/types/proxy/eth_transactioncount.h \
    $$PWD/src/types/proxy/eth_transactionhash.h \
    $$PWD/src/types/proxy/eth_transactionreceipt.h \
    $$PWD/src/types/transaction.h \
    $$PWD/src/types/uncle.h

OTHER_FILES += \
    $$PWD/README.md
