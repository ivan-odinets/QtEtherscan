INCLUDEPATH += $$PWD

DEFINES     += QTES_VERSION='\\"0.0.4\\"'

QT          += core network

CONFIG      += c++17

SOURCES += \
    $$PWD/src/qethsc_api.cpp \
    $$PWD/src/qethsc_networking.cpp \
    $$PWD/src/types/proxy/eth_block.cpp \
    $$PWD/src/types/proxy/eth_log.cpp \
    $$PWD/src/types/proxy/eth_response.cpp \
    $$PWD/src/types/proxy/eth_transaction.cpp \
    $$PWD/src/types/proxy/eth_transactionreceipt.cpp \
    $$PWD/src/types/qethsc_accountbalance.cpp \
    $$PWD/src/types/qethsc_beaconchainwithdrawal.cpp \
    $$PWD/src/types/qethsc_block.cpp \
    $$PWD/src/types/qethsc_blockandunclerewards.cpp \
    $$PWD/src/types/qethsc_contractcreator.cpp \
    $$PWD/src/types/qethsc_contractexecutionstatus.cpp \
    $$PWD/src/types/qethsc_contractsourcecode.cpp \
    $$PWD/src/types/qethsc_dailyblockcountrewards.cpp \
    $$PWD/src/types/qethsc_dailyblockrewards.cpp \
    $$PWD/src/types/qethsc_dailyblocksize.cpp \
    $$PWD/src/types/qethsc_dailyblocktime.cpp \
    $$PWD/src/types/qethsc_dailygaslimit.cpp \
    $$PWD/src/types/qethsc_dailygasprice.cpp \
    $$PWD/src/types/qethsc_dailymarketcap.cpp \
    $$PWD/src/types/qethsc_dailynetworkdifficulty.cpp \
    $$PWD/src/types/qethsc_dailynetworkhashrate.cpp \
    $$PWD/src/types/qethsc_dailynetworkutilization.cpp \
    $$PWD/src/types/qethsc_dailynewaddresscount.cpp \
    $$PWD/src/types/qethsc_dailytotalgas.cpp \
    $$PWD/src/types/qethsc_dailytransactioncount.cpp \
    $$PWD/src/types/qethsc_dailytransactionfees.cpp \
    $$PWD/src/types/qethsc_dailyunclecountrewards.cpp \
    $$PWD/src/types/qethsc_erc1155tokentransferevent.cpp \
    $$PWD/src/types/qethsc_erc20tokenholder.cpp \
    $$PWD/src/types/qethsc_erc20tokenholding.cpp \
    $$PWD/src/types/qethsc_erc20tokentransferevent.cpp \
    $$PWD/src/types/qethsc_erc721tokenholding.cpp \
    $$PWD/src/types/qethsc_erc721tokeninventory.cpp \
    $$PWD/src/types/qethsc_erc721tokentransferevent.cpp \
    $$PWD/src/types/qethsc_estimatedblockcountdown.cpp \
    $$PWD/src/types/qethsc_ether.cpp \
    $$PWD/src/types/qethsc_ether2supply.cpp \
    $$PWD/src/types/qethsc_etherhistoricalprice.cpp \
    $$PWD/src/types/qethsc_etherprice.cpp \
    $$PWD/src/types/qethsc_eventlogs.cpp \
    $$PWD/src/types/qethsc_gasoracle.cpp \
    $$PWD/src/types/qethsc_internaltransaction.cpp \
    $$PWD/src/types/qethsc_nodescount.cpp \
    $$PWD/src/types/qethsc_nodessize.cpp \
    $$PWD/src/types/qethsc_tokeninfo.cpp \
    $$PWD/src/types/qethsc_transaction.cpp \
    $$PWD/src/types/qethsc_uncle.cpp

HEADERS += \
    $$PWD/QtEtherscan.h \
    $$PWD/src/qethsc_api.h \
    $$PWD/src/qethsc_networking.h \
    $$PWD/src/types/proxy/eth_block.h \
    $$PWD/src/types/proxy/eth_blocknumber.h \
    $$PWD/src/types/proxy/eth_gasprice.h \
    $$PWD/src/types/proxy/eth_helper.h \
    $$PWD/src/types/proxy/eth_log.h \
    $$PWD/src/types/proxy/eth_response.h \
    $$PWD/src/types/proxy/eth_transaction.h \
    $$PWD/src/types/proxy/eth_transactioncount.h \
    $$PWD/src/types/proxy/eth_transactionhash.h \
    $$PWD/src/types/proxy/eth_transactionreceipt.h \
    $$PWD/src/types/qethsc_accountbalance.h \
    $$PWD/src/types/qethsc_beaconchainwithdrawal.h \
    $$PWD/src/types/qethsc_block.h \
    $$PWD/src/types/qethsc_blockandunclerewards.h \
    $$PWD/src/types/qethsc_constants.h \
    $$PWD/src/types/qethsc_contractcreator.h \
    $$PWD/src/types/qethsc_contractexecutionstatus.h \
    $$PWD/src/types/qethsc_contractsourcecode.h \
    $$PWD/src/types/qethsc_dailyblockcountrewards.h \
    $$PWD/src/types/qethsc_dailyblockrewards.h \
    $$PWD/src/types/qethsc_dailyblocksize.h \
    $$PWD/src/types/qethsc_dailyblocktime.h \
    $$PWD/src/types/qethsc_dailygaslimit.h \
    $$PWD/src/types/qethsc_dailygasprice.h \
    $$PWD/src/types/qethsc_dailymarketcap.h \
    $$PWD/src/types/qethsc_dailynetworkdifficulty.h \
    $$PWD/src/types/qethsc_dailynetworkhashrate.h \
    $$PWD/src/types/qethsc_dailynetworkutilization.h \
    $$PWD/src/types/qethsc_dailynewaddresscount.h \
    $$PWD/src/types/qethsc_dailytotalgas.h \
    $$PWD/src/types/qethsc_dailytransactioncount.h \
    $$PWD/src/types/qethsc_dailytransactionfees.h \
    $$PWD/src/types/qethsc_dailyunclecountrewards.h \
    $$PWD/src/types/qethsc_enums.h \
    $$PWD/src/types/qethsc_erc1155tokentransferevent.h \
    $$PWD/src/types/qethsc_erc20tokenholder.h \
    $$PWD/src/types/qethsc_erc20tokenholding.h \
    $$PWD/src/types/qethsc_erc20tokentransferevent.h \
    $$PWD/src/types/qethsc_erc721tokenholding.h \
    $$PWD/src/types/qethsc_erc721tokeninventory.h \
    $$PWD/src/types/qethsc_erc721tokentransferevent.h \
    $$PWD/src/types/qethsc_estimatedblockcountdown.h \
    $$PWD/src/types/qethsc_ether.h \
    $$PWD/src/types/qethsc_ether2supply.h \
    $$PWD/src/types/qethsc_etherhistoricalprice.h \
    $$PWD/src/types/qethsc_etherprice.h \
    $$PWD/src/types/qethsc_eventlogs.h \
    $$PWD/src/types/qethsc_gasoracle.h \
    $$PWD/src/types/qethsc_internaltransaction.h \
    $$PWD/src/types/qethsc_jsonobjectslist.h \
    $$PWD/src/types/qethsc_nodescount.h \
    $$PWD/src/types/qethsc_nodessize.h \
    $$PWD/src/types/qethsc_tokeninfo.h \
    $$PWD/src/types/qethsc_transaction.h \
    $$PWD/src/types/qethsc_uncle.h

OTHER_FILES += \
    $$PWD/README.md
