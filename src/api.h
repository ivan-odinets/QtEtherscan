/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2023 Ivan Odinets
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

#ifndef API_H
#define API_H

#include <QObject>

#include "./networking.h"

#include "./types/accountbalance.h"
#include "./types/block.h"
#include "./types/blockandunclerewards.h"
#include "./types/contractexecutionstatus.h"
#include "./types/erc20tokentransferevent.h"
#include "./types/erc721tokentransferevent.h"
#include "./types/erc1155tokentransferevent.h"
#include "./types/estimatedblockcountdown.h"
#include "./types/ether.h"
#include "./types/etherprice.h"
#include "./types/ether2supply.h"
#include "./types/eventlogs.h"
#include "./types/gasoracle.h"
#include "./types/internaltransaction.h"
#include "./types/nodescount.h"
#include "./types/nodessize.h"
#include "./types/transaction.h"
#include "./types/global.h"

namespace QtEtherscan {

/*!
 * @class API src/api.h
 * @brief API class provides interface to communicate with Etherscan servers
 */

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
        NoError,                       /*!< @brief If the request was successfuul */
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

    /*! @brief This method can be used to get information about errors related to Etherscan API
     *  @return Error::NoError on success and any other value - if failed. */
    Error          errorCode() const                       { return m_errorCode; }

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "accounts" module
     *
     */

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
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-list-of-blocks-mined-by-address */
    BlockList getListOfBlocksMinedByAddress(const QString& address, BlockType blockType, int page, int offset);

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "logs" module
     *
     */

    /*! @brief Returns the event logs from an address, with optional filtering by block range.
     *  @returns EventLogList object
     *  @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address */
    EventLogList getEventLogs(const QString& address, qint32 fromBlock, qint32 toBlock, int page, int offset);

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "transaction" module
     *
     */

    /*! @brief Returns the status code of a contract execution.
     *  @returns ContractExecutionStatus object
     *  @see https://docs.etherscan.io/api-endpoints/stats#check-contract-execution-status */
    ContractExecutionStatus checkContractExecutionStatus(const QString& txHash);

    /*! @brief Returns the status code of a transaction execution.
     *  @returns bool
     *  @see https://docs.etherscan.io/api-endpoints/stats#check-transaction-receipt-status */
    bool checkTransactionReceiptStatus(const QString& txHash);

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "blocks" module
     *
     */

    /*! @brief Returns the block reward and 'Uncle' block rewards.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-block-and-uncle-rewards-by-blockno */
    BlockAndUncleRewards getBlockAndUncleRewards(qint32 blockNumber);

    /*! @brief Returns the estimated time remaining, in seconds, until a certain block is mined.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-estimated-block-countdown-time-by-blockno */
    EstimatedBlockCountdown getEstimatedBlockCountdown(qint32 blockNumber);

    /*! @brief Returns the block number that was mined at a certain timestamp.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-block-number-by-timestamp */
    qint32 getBlockNumberByTimestamp(const QDateTime& timestamp,Closest closest);
    qint32 getBlockNumberByTimestamp(qint64 timestamp,Closest closest);

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "tokens" module
     *
     */

    /*! @brief Returns the current amount of an ERC-20 token in circulation.
     *  @return QString containing total supply of token in the token's smallest decimal representation. Eg. a token with
     *          a balance of 215.241526476136819398 and 18 decimal places will be returned as 215241526476136819398
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-erc20-token-totalsupply-by-contractaddress */
    QString getERC20TokenTotalSupply(const QString& contractAddress);

    /*! @brief Returns the current balance of an ERC-20 token of an address.
     *  @return QString containing balance of token in the token's smallest decimal representation. Eg. a token with a
     *          balance of 215.241526476136819398 and 18 decimal places will be returned as 215241526476136819398
     *  @see https://docs.etherscan.io/api-endpoints/tokens#get-erc20-token-account-balance-for-tokencontractaddress */
    QString getERC20TokenAccountBalance(const QString& contractAddress, const QString& address);

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "gas" module
     *
     */

    /*! @brief Returns the estimated time, in seconds, for a transaction to be confirmed on the blockchain.
     *  @param gasPrce in Wei
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-estimation-of-confirmation-time */
    quint32 getEstimationOfConfirmationTime(quint64 gasPrice);

    /*! @brief Returns the current Safe, Proposed and Fast gas prices.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-gas-oracle */
    GasOracle getGasOracle();

    /*
     **********************************************************************************************************************
     *
     * Implemented API methods from "stats" module
     *
     */

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

private:
    QJsonObject              makeApiCall(const QUrlQuery& urlQuery);
    qint64                   responseInt(const QJsonObject& response);
    QString                  responseString(const QJsonObject& response);
    template<class C> C      responseObject(const QJsonObject& response);
    Error                    getErrorCode(const QJsonObject& response);

    Networking     m_net;
    QString        m_apiKey;
    Network        m_activeEtheriumNetwork;

    Error          m_errorCode;
    QString        m_errorMessage;
};

} // namespace QtEtherscan

#endif // API_H
