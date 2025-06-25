/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets <i_odinets@protonmail.com>
 *
 * This file is part of QtEtherscan
 *
 * QtEtherscan is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QtEtherscan  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QtEtherscan; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef QT_ETHERSCAN_API_H
#define QT_ETHERSCAN_API_H

#include <QObject>

#include "./qethsc_networking.h"

#include "./types/qethsc_accountbalance.h"
#include "./types/qethsc_dailyblocksize.h"
#include "./types/qethsc_beaconchainwithdrawal.h"
#include "./types/qethsc_block.h"
#include "./types/qethsc_blockandunclerewards.h"
#include "./types/qethsc_contractcreator.h"
#include "./types/qethsc_contractexecutionstatus.h"
#include "./types/qethsc_contractsourcecode.h"
#include "./types/qethsc_dailyblockcountrewards.h"
#include "./types/qethsc_dailyblocktime.h"
#include "./types/qethsc_dailyblockrewards.h"
#include "./types/qethsc_dailygaslimit.h"
#include "./types/qethsc_dailygasprice.h"
#include "./types/qethsc_dailymarketcap.h"
#include "./types/qethsc_dailynetworkdifficulty.h"
#include "./types/qethsc_dailynetworkhashrate.h"
#include "./types/qethsc_dailynetworkutilization.h"
#include "./types/qethsc_dailynewaddresscount.h"
#include "./types/qethsc_dailytotalgas.h"
#include "./types/qethsc_dailytransactioncount.h"
#include "./types/qethsc_dailytransactionfees.h"
#include "./types/qethsc_dailyunclecountrewards.h"
#include "./types/qethsc_erc20tokenholder.h"
#include "./types/qethsc_erc20tokenholding.h"
#include "./types/qethsc_erc20tokentransferevent.h"
#include "./types/qethsc_erc721tokeninventory.h"
#include "./types/qethsc_erc721tokenholding.h"
#include "./types/qethsc_erc721tokentransferevent.h"
#include "./types/qethsc_erc1155tokentransferevent.h"
#include "./types/qethsc_estimatedblockcountdown.h"
#include "./types/qethsc_ether.h"
#include "./types/qethsc_etherprice.h"
#include "./types/qethsc_ether2supply.h"
#include "./types/qethsc_etherhistoricalprice.h"
#include "./types/qethsc_eventlogs.h"
#include "./types/qethsc_gasoracle.h"
#include "./types/qethsc_internaltransaction.h"
#include "./types/qethsc_nodescount.h"
#include "./types/qethsc_nodessize.h"
#include "./types/qethsc_tokeninfo.h"
#include "./types/qethsc_transaction.h"
#include "./types/qethsc_enums.h"

#include "./types/proxy/eth_blocknumber.h"
#include "./types/proxy/eth_gasprice.h"
#include "./types/proxy/eth_block.h"
#include "./types/proxy/eth_transaction.h"
#include "./types/proxy/eth_transactioncount.h"
#include "./types/proxy/eth_transactionhash.h"
#include "./types/proxy/eth_transactionreceipt.h"

namespace QtEtherscan {

/*! @class API "QtEtherscan.h"
 *  @brief API class provides interface to communicate with Etherscan servers
 *  @details For usage examples check examples directory. */

class API : public QObject
{
    Q_OBJECT
public:
    /*! @brief This enum describes etherium networks supported by etherscan */
    enum Network {
        Mainnet,   /*!< @brief Mainnet. Requests will go to URL https://api.etherscan.io/api */
        Goerli,    /*!< @brief Goerli. Requests will go to URL https://api-goerli.etherscan.io/api */
        Kovan,     /*!< @brief Kovan. Requests will go to URL https://api-kovan.etherscan.io/api */
        RInkeby,   /*!< @brief RInkeby. Requests will go to URL https://api-rinkeby.etherscan.io/api */
        Ropsten,   /*!< @brief Ropsten. Requests will go to URL https://api-ropsten.etherscan.io/api */
        Sepolia    /*!< @brief Sepolia. Requests will go to URL https://api-sepolia.etherscan.io/api */
    };

    /*! @brief This enum holds information about what exactly error happened */
    enum Error {
        NoError,                       /*!< @brief If the request was successfull */
        NetworkError,                  /*!< @brief If during request some networking error happened */

        NoRecorsFoundError,            /*!< @brief Corresponds to "result":"No records found" */
        NoTransactionsFoundError,      /*!< @brief Corresponds to "message":"No transactions found" */
        ProRequiredError,              /*!< @brief Corresponds to "result":"Sorry, it looks like you are trying to
                                                   access an API Pro endpoint. Contact us to upgrade to API Pro." */
        MaxRateError,                  /*!< @brief Corresponds to "result":"Max rate limit reached, please use API
                                        *          Key for higher rate limit */
        InvalidAPIKeyError,            /*!< @brief Corresponds to "result":"Invalid API Key"*/
        InvalidAddressFormatError,     /*!< @brief Corresponds to "result":"Error! Invalid address format" */

        InvalidModuleNameError,        /*!< @brief Corresponds to "result":"Error! Missing Or invalid Module name" */
        InvalidActionNameError,        /*!< @brief Corresponds to "result":"Error! Missing Or invalid Action name" */
        InvalidParameterError,         /*!< @brief Corresponds to "result":"Error! Missing or invalid parameter" */

        UnknownError                   /*!< @brief Corresponds to any other error which have happened */
    };

    explicit API(QObject *parent = nullptr);
    explicit API(const QString& apiKey, QObject *parent = nullptr);
    ~API() {}

    /*! @brief This method can be used to set Etherscan API token
     *  @details After setting new api key - all requests made to Etherscan servers will be done using this key. For
     *           creating those keys check [etherscan docs](https://docs.etherscan.io/getting-started/viewing-api-usage-statistics#creating-an-api-key)
     *  @param QString newApiKey*/
    void           setApiKey(const QString& newApiKey)     { m_apiKey = newApiKey; }

    /*! @brief This method returns API token being used by this QtEtherscan::API object. */
    QString        apiKey() const                          { return m_apiKey; }

    /*! @brief This method can be used to configure proxy, through which communication with etherscan servers will be done
     *  @param QNetworkProxy newProxy - new proxy configuration */
    void           setProxy(const QNetworkProxy& newProxy) { m_net.setProxy(newProxy); }

    /*! @brief This method can be used to get information about currently configured proxy.
     *  @return QNetworkProxy object, representing current proxy configuration */
    QNetworkProxy  proxy() const                           { return m_net.proxy(); }

    /*! @brief This method allows to setup a timeout for requests to Etherscan servers.
     *  @param quint32 timeout (in mseconds) after which request will be aborted. Pass 0 to disable timeout */
    void           setRequestTimeout(quint32 msec)         { m_net.setRequestTimeout(msec); }

    /*! @brief This method returns information about timeout */
    quint32        requestTimeout() const                  { return m_net.requestTimeout(); }

    /*! @brief This method can be used to setup with what Etherium network this instantce of QtEtherscan object will interact.
     *         By default QtEtherscan object will use Mainnet as a "target" network
     *  @param etheriumNetwork represented by one of the values from enum QtEtherscan::Network */
    void           setEtheriumNetwork(Network etheriumNetwork);

    /*! @brief This method allows to check with what Etherium network this instantce of QtEtherscan object will interact
     *  @returns QtEtherscan::Network value */
    Network        etheriumNetwork() const                 { return m_activeEtheriumNetwork; }

    /*! @brief This method can be used to get information about errors related to Etherscan API.
     *  @details If the last request to etherscan.io servers failed due to whatever reason - this method should return
     *           value from enum QtEtherscan::API::Error which is representing occured error. If the last request was
     *           successfull - this method should return QtEtherscan::API::NoError value. */
    Error          errorCode() const                       { return m_errorCode; }

    /*! @brief This method can be used to get detailed information about errors related to Etherscan API
     *  @details If the last request to etherscan.io servers failed due to whatever reason - this method should return
     *           error description provided by etherscan.io server. If the last request was successfull - this method
     *           should return empty QString.
     *  @return QString containing error message given by Etherscan */
    QString        errorMessage() const                    { return m_errorMessage; }

    /*! @brief This method can be used to call API methods "manualy". For example, for now this can be used to call PRO
     *         API methods, which are not yet implemented. NOTE - if calling this method, you will need to add your
     *         ethersan.io API token manually.
     *  @param query - QUrlQuery populated with propper parameters.
     *  @return QJsonObject containing whole reply from etherscan.io servers. */
    QJsonObject call(const QUrlQuery& query);

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from etherscan.io "accounts" module.
     *  @{ */

    /*! @brief Returns the Ether balance of a given address.
     *  @returns EtherBalance object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-a-single-address */
    EtherBalance getEtherBalance(const QString& address, Tag tag = Latest);

    /*! @brief Returns the balance of the accounts from a list of addresses.
     *  @returns AccountBalanceList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-multiple-addresses-in-a-single-call */
    AccountBalanceList getEtherBalance(const QStringList& addresses, Tag tag = Latest);

    /*! @brief Returns the list of transactions performed by an address, with optional pagination. This API endpoint returns
     *         a maximum of 10000 records only.
     *  @returns TransactionList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-normal-transactions-by-address */
    TransactionList getListOfNomalTransactions(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of internal transactions performed by an address, with optional pagination. This API endpoint
     *         returns a maximum of 10000 records only.
     *  @returns InternalTransactionList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-internal-transactions-by-address */
    InternalTransactionList getListOfInternalTransactions(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of internal transactions performed within a transaction. This API endpoint returns a
     *         maximum of 10000 records only.
     *  @returns InternalTransactionList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-internal-transactions-by-transaction-hash */
    InternalTransactionList getListOfInternalTransactions(const QString& txhash);

    /*! @brief Returns the list of internal transactions performed within a block range, with optional pagination.
     *         This API endpoint returns a maximum of 10000 records only.
     *  @returns InternalTransactionList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-internal-transactions-by-block-range */
    InternalTransactionList getListOfInternalTransactions(qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of ERC-20 tokens transferred by an address, with optional filtering by token contract.
     *  @details ERC-20 transfers from an address, specify the address parameter. ERC-20 transfers from a contract address,
     *           specify the contract address parameter. ERC-20 transfers from an address filtered by a token contract,
     *           specify both address and contract address parameters.
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc20-token-transfer-events-by-address */
    ERC20TokenTransferEventList getListOfERC20TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of ERC-721 ( NFT ) tokens transferred by an address, with optional filtering by token contract.
     *  @details ERC-721 transfers from an address, specify the address parameter. ERC-721 transfers from a contract address,
     *           specify the contract address parameter. ERC-721 transfers from an address filtered by a token contract,
     *           specify both address and contract address parameters.
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc721-token-transfer-events-by-address */
    ERC721TokenTransferEventList getListOfERC721TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of ERC-1155 ( Multi Token Standard ) tokens transferred by an address, with optional filtering by token contract.
     *  @details ERC-1155 transfers from an address, specify the address parameter. ERC-1155 transfers from a contract address,
     *           specify the contract address parameter. ERC-1155 transfers from an address filtered by a token contract,
     *           specify both address and contract address parameters.
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc721-token-transfer-events-by-address */
    ERC1155TokenTransferEventList getListOfERC1155TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the list of blocks mined by an address.
     *  @returns BlockList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-list-of-blocks-mined-by-address
     *  @deprecated */
    Q_DECL_DEPRECATED_X("This method will is going to be replaced by getListOfBlocksValidatedByAddress instead.")
    BlockList getListOfBlocksMinedByAddress(const QString& address, BlockType blockType, int page, int offset);

    /*! @brief Returns the list of blocks validated by an address.
     *  @returns BlockList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-list-of-blocks-validated-by-address */
    BlockList getListOfBlocksValidatedByAddress(const QString& address, BlockType blockType, int page, int offset);

    /*! @brief Returns the beacon chain withdrawals made to an address.
     *  @returns BeaconChainWithdrawalList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-beacon-chain-withdrawals-by-address-and-block-range */
    BeaconChainWithdrawalList getBeaconChainWithdrawals(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort);

    /*! @brief Returns the balance of an address at a certain block height. **NOTE** This is etherscan.io PRO method. To get
     *         any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-historical-ether-balance-for-a-single-address-by-blockno */
    EtherBalance getHistoricalEtherBalance(const QString& address, qint32 blockNumber);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "contracts" module.
     *  @{ */

    /*! @brief Returns the Contract Application Binary Interface ( ABI ) of a verified smart contract.
     *  @returns QJsonArray object containing reply from etherscan.io
     *  @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-abi-for-verified-contract-source-codes */
    QJsonArray getContratABI(const QString& address);


    /*! @brief Returns the Solidity source code of a verified smart contract.
     *  @returns ContractSourceCode object
     *  @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-source-code-for-verified-contract-source-codes */
    ContractSourceCode getContractSourceCode(const QString& address);

    /*! @brief Returns a contract's deployer address and transaction hash it was created, up to 5 at a time.
     *  @returns ContractCreatorList object
     *  @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-creator-and-creation-tx-hash */
    ContractCreatorList getContractCreatorList(const QStringList& addresses);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "transactions" module.
     *  @{ */

    /*! @brief Returns the status code of a contract execution.
     *  @returns ContractExecutionStatus object
     *  @see https://docs.etherscan.io/api-endpoints/stats#check-contract-execution-status */
    ContractExecutionStatus checkContractExecutionStatus(const QString& txHash);

    /*! @brief Returns the status code of a transaction execution.
     *  @details For failed transactions false and for successful true is returned
     *  @returns bool
     *  @see https://docs.etherscan.io/api-endpoints/stats#check-transaction-receipt-status */
    bool checkTransactionReceiptStatus(const QString& txHash);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "blocks" module.
     *  @{ */

    /*! @brief Returns the block reward and 'Uncle' block rewards.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-block-and-uncle-rewards-by-blockno */
    BlockAndUncleRewards getBlockAndUncleRewards(qint32 blockNumber);

    /*! @brief Returns the estimated time remaining, in seconds, until a certain block is mined.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-estimated-block-countdown-time-by-blockno */
    EstimatedBlockCountdown getEstimatedBlockCountdown(qint32 blockNumber);

    /*! @brief Returns the block number that was mined at a certain timestamp.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-block-number-by-timestamp */
    qint32 getBlockNumberByTimestamp(const QDateTime& timestamp,Closest closest);

    /*! @overload */
    qint32 getBlockNumberByTimestamp(qint64 timestamp,Closest closest);

    /*! @brief Returns the daily average block size within a date range. **NOTE** This is etherscan.io PRO method. To
     *         get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-block-size */
    DailyBlockSizeList getDailyAverageBlockSize(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyBlockSizeList getDailyAverageBlockSize(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the number of blocks mined daily and the amount of block rewards. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-count-and-rewards */
    DailyBlockCountRewardsList getDailyBlockCountRewards(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyBlockCountRewardsList getDailyBlockCountRewards(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the amount of block rewards distributed to miners daily. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-rewards */
    DailyBlockRewardsList getDailyBlockRewards(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyBlockRewardsList getDailyBlockRewards(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the daily average of time needed for a block to be successfully mined. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-time-for-a-block-to-be-included-in-the-ethereum-blockchain */
    DailyBlockTimeList getDailyAverageTimeForBlock(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyBlockTimeList getDailyAverageTimeForBlock(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the number of 'Uncle' blocks mined daily and the amount of 'Uncle' block rewards. **NOTE** This is
     *         etherscan.io PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-uncle-block-count-and-rewards */
    DailyUncleCountRewardsList getDailyUncleCountRewards(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyUncleCountRewardsList getDailyUncleCountRewards(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "logs" module.
     *  @{ */

    /*! @brief Returns the event logs from an address, with optional filtering by block range.
     *  @returns EventLogList object
     *  @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address */
    EventLogList getEventLogs(const QString& address, qint32 fromBlock, qint32 toBlock, int page, int offset);

    /*! @brief Returns the events log in a block range, filtered by topics.
     *  @returns EventLogList object
     *  @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-topics */
    EventLogList getEventLogsByTopics(const QMap<QString,QString>& topics, qint32 fromBlock, qint32 toBlock, int page, int offset);

    /*! @brief Returns the event logs from an address, filtered by topics and block range.
     *  @returns EventLogList object
     *  @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address-filtered-by-topics */
    EventLogList getEventLogsByAddressTopics(const QMap<QString,QString>& topics, const QString& address, qint32 fromBlock, qint32 toBlock, int page, int offset);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "proxy" module.
     *  @{ */

    /*! @brief Returns the number of most recent block.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_blocknumber */
    Proxy::BlockNumberResponse eth_blockNumber();

    /*! @brief Returns information about a block by block number.
     *  @param boolean If true it returns the full transaction objects, if false only the hashes of the transactions.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber */
    Proxy::BlockResponse eth_getBlockByNumber(const QString blockNumberString, bool boolean = true);

    /*! @overload */
    Proxy::BlockResponse eth_getBlockByNumber(qint32 blockNumber, bool boolean = true);

    /*! @brief Returns information about a uncle by block number.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getunclebyblocknumberandindex */
    Proxy::BlockResponse eth_getUncleByBlockNumberAndIndex(const QString& blockNumberString,const QString& indexString);

    /*! @overload */
    Proxy::BlockResponse eth_getUncleByBlockNumberAndIndex(qint32 blockNumber,qint32 index);

    /*! @brief Returns the number of transactions in a block.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblocktransactioncountbynumber */
    Proxy::TransactionCountResponse eth_getBlockTransactionCountByNumber(const QString& blockNumberString);

    /*! @overload */
    Proxy::TransactionCountResponse eth_getBlockTransactionCountByNumber(qint32 blockNumber);

    /*! @brief Returns the information about a transaction requested by transaction hash.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionbyhash */
    Proxy::TransactionResponse eth_getTransactionByHash(const QString& txHash);

    /*! @brief Returns information about a transaction by block number and transaction index position.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionbyblocknumberandindex */
    Proxy::TransactionResponse eth_getTransactionByBlockNumberAndIndex(const QString& blockNumberString, const QString& index);

    /*! @overload */
    Proxy::TransactionResponse eth_getTransactionByBlockNumberAndIndex(qint32 blockNumber, qint32 index);

    /*! @brief Returns the number of transactions performed by an address.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactioncount */
    Proxy::TransactionCountResponse eth_getTransactionCount(const QString& address, Tag tag = Latest);

    /*! @brief Submits a pre-signed transaction for broadcast to the Ethereum network.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_sendrawtransaction */
    Proxy::TransactionHashResponse eth_sendRawTransaction(const QString& hex);

    /*! @brief Returns the receipt of a transaction by transaction hash.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionreceipt*/
    Proxy::TransactionReceiptResponse eth_getTransactionReceipt(const QString& txHash);

    /*! @brief Executes a new message call immediately without creating a transaction on the block chain.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_call */
    Proxy::StringResponse eth_call(const QString& to, const QString& data, Tag tag = Latest);

    /*! @brief Returns code at a given address.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getcode */
    Proxy::StringResponse eth_getCode(const QString& address, Tag tag = Latest);

    /*! @brief Returns the value from a storage position at a given address.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getstorageat */
    Proxy::StringResponse eth_getStorageAt(const QString& address, const QString& positionString, Tag tag = Latest);

    /*! @brief Returns the current price per gas in wei.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gasprice */
    Proxy::GasPriceResponse eth_gasPrice();

    /*! @brief Makes a call or transaction, which won't be added to the blockchain and returns the used gas.
     *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_estimategas */
    Proxy::StringResponse eth_estimateGas(const QString& data, const QString& to,const QString& value,const QString& gasPrice, const QString& gas);

    /*! @overload */
    Proxy::StringResponse eth_estimateGas(const QString& data, const QString& to,const QString& value,quint64 gasPrice, quint64 gas);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "tokens" module.
     *  @{ */

    /*! @brief Returns the current amount of an ERC-20 token in circulation.
     *  @return QString containing total supply of token in the token's smallest decimal representation. Eg. a token with
     *          a balance of 215.241526476136819398 and 18 decimal places will be returned as 215241526476136819398
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-erc20-token-totalsupply-by-contractaddress */
    QString getERC20TokenTotalSupply(const QString& contractAddress);

    /*! @brief Returns the current balance of an ERC-20 token of an address.
     *  @return QString containing balance of token in the token's smallest decimal representation. Eg. a token with a
     *          balance of 215.241526476136819398 and 18 decimal places will be returned as 215241526476136819398
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-erc20-token-account-balance-for-tokencontractaddress */
    QString getERC20TokenAccountBalance(const QString& contractAddress, const QString& address, Tag tag);

    /*! @brief Returns the amount of an ERC-20 token in circulation at a certain block height. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-historical-erc20-token-totalsupply-by-contractaddress-and-blockno */
    QString getHistoricalERC20TokenSupply(const QString& contractAddress, qint32 blockNumber);

    /*! @brief Returns the balance of an ERC-20 token of an address at a certain block height. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-historical-erc20-token-account-balance-for-tokencontractaddress-by-blockno */
    QString getHistoricalERC20TokenBalance(const QString& contractAddress, const QString& address, qint32 blockNumber);

    /*! @brief Return the current ERC20 token holders and number of tokens held. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-token-holder-list-by-contract-address */
    ERC20TokenHolderList getERC20TokenHolders(const QString& contractAddress, int page, int offset);

    /*! @brief Returns project information and social media links of an ERC20/ERC721/ERC1155 token. **NOTE** This is
     *         etherscan.io PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-token-info-by-contractaddress */
    TokenInfo getTokenInfo(const QString& contractAddress);

    /*! @brief Returns the ERC-20 tokens and amount held by an address. **NOTE** This is etherscan.io PRO method. To get
     *         any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc20-token-holding */
    ERC20TokenHoldingList getERC20TokenHolding(const QString& address, int page, int offset);

    /*! @brief Returns the ERC-721 tokens and amount held by an address. **NOTE** This is etherscan.io PRO method. To get
     *         any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-holding */
    ERC721TokenHoldingList getERC721TokenHolding(const QString& address, int page, int offset);

    /*! @brief Returns the ERC-721 token inventory of an address, filtered by contract address. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-inventory-by-contract-address */
    ERC721TokenInventoryList getERC721TokenInventory(const QString& address,const QString& contractAddress, int page, int offset);

    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "gas" module.
     *  @{ */

    /*! @brief Returns the estimated time, in seconds, for a transaction to be confirmed on the blockchain.
     *  @param gasPrce in Wei
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-estimation-of-confirmation-time */
    quint32 getEstimationOfConfirmationTime(quint64 gasPrice);

    /*! @brief Returns the current Safe, Proposed and Fast gas prices.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-gas-oracle */
    GasOracle getGasOracle();

    /*! @brief Returns the historical daily average gas limit of the Ethereum network. **NOTE** This is etherscan.io PRO
     *         method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-limit */
    DailyGasLimitList getDailyAverageGasLimit(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyGasLimitList getDailyAverageGasLimit(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the total amount of gas used daily for transctions on the Ethereum network. **NOTE** This is
     *         etherscan.io PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-ethereum-daily-total-gas-used */
    DailyTotalGasList getDailyTotalGasAmount(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyTotalGasList getDailyTotalGasAmount(const QDate& startDate, const QDate& endDate, Sort sort);

    /*! @brief Returns the daily average gas price used on the Ethereum network. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-price */
    DailyGasPriceList getDailyAverageGasPrice(const QString& startDate, const QString& endDate, Sort sort);

    /*! @overload */
    DailyGasPriceList getDailyAverageGasPrice(const QDate& startDate, const QDate& endDate, Sort sort);


    /*! @} */

    /*!
     *********************************************************************************************************************
     *  @name Implemented API methods from "stats" module.
     *  @{ */

    /*! @brief Returns the current amount of Ether in circulation excluding ETH2 Staking rewards and EIP1559 burnt fees.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-total-supply-of-ether */
    EtherBalance getTotalSupplyOfEther();

    /*! @brief Returns the current amount of Ether in circulation, ETH2 Staking rewards and EIP1559 burnt fees statistics.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-total-supply-of-ether-2 */
    Ether2Supply getTotalSupplyOfEther2();

    /*! @brief Returns the latest price of 1 ETH.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-last-price */
    EtherPrice getEtherLastPrice();

    /*! @brief Returns the size of the Ethereum blockchain, in bytes, over a date range.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ethereum-nodes-size */
    NodesSize getEtheriumNodesSize(const QDate& startDate, const QDate& endDate, ClientType clientType = Geth, Syncmode syncmode = Default, Sort sort = Asc);

    /*! @overload */
    NodesSize getEtheriumNodesSize(const QString& startDate, const QString& endDate, ClientType clientType = Geth, Syncmode syncmode = Default, Sort sort = Asc);

    /*! @brief Returns the total number of discoverable Ethereum nodes.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-total-nodes-count */
    NodesCount getTotalNodesCount();

    /*! @brief Returns the amount of transaction fees paid to miners per day. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-transaction-fee */
    DailyTransactionFeesList getDailyNetworkTransactionFee(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyTransactionFeesList getDailyNetworkTransactionFee(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the number of new Ethereum addresses created per day. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-new-address-count */
    DailyNewAddressCountList getDailyNewAddressCount(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyNewAddressCountList getDailyNewAddressCount(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the daily average gas used over gas limit, in percentage. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-utilization */
    DailyNetworkUtilizationList getDailyNetworkUtilization(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyNetworkUtilizationList getDailyNetworkUtilization(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the historical measure of processing power of the Ethereum network. **NOTE** This is etherscan.io
     *         PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-hash-rate */
    DailyNetworkHashrateList getDailyNetworkHashrate(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyNetworkHashrateList getDailyNetworkHashrate(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the number of transactions performed on the Ethereum blockchain per day. **NOTE** This is
     *         etherscan.io PRO method. To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-transaction-count */
    DailyTransactionCountList getDailyTransactionCount(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyTransactionCountList getDailyTransactionCount(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the historical mining difficulty of the Ethereum network. **NOTE** This is etherscan.io PRO method.
     *         To get any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-difficulty */
    DailyNetworkDifficultyList getDailyNetworkDifficulty(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyNetworkDifficultyList getDailyNetworkDifficulty(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the historical Ether daily market capitalization. **NOTE** This is etherscan.io PRO method. To get
     *         any results with this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-daily-market-cap#define */
    DailyMarketCapList getHistoricalEtherMarketCapitalization(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    DailyMarketCapList getHistoricalEtherMarketCapitalization(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @brief Returns the historical price of 1 ETH. **NOTE** This is etherscan.io PRO method. To get any results with
     *         this method you need to get proper API key.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-price */
    EtherHistoricalPriceList getEtherHistoricalPrice(const QString& startDate, const QString& endDate, Sort sort = Asc);

    /*! @overload */
    EtherHistoricalPriceList getEtherHistoricalPrice(const QDate& startDate, const QDate& endDate, Sort sort = Asc);

    /*! @} */

private:
    QJsonObject              makeApiCall(const QUrlQuery& urlQuery);
    qint64                   responseInt(const QJsonObject& response);
    QString                  responseString(const QJsonObject& response);
    template<class C> C      responseObject(const QJsonObject& response);
    template<class C> C      proxyResponse(const QJsonObject& response);
    Error                    getErrorCode(const QJsonObject& response);

    static QString           tagToString(Tag tag);

    Networking     m_net;
    QString        m_apiKey;
    Network        m_activeEtheriumNetwork;

    Error          m_errorCode;
    QString        m_errorMessage;
};

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_API_H
