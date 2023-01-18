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

#include "./api.h"

#include <QUrlQuery>
#include <QJsonDocument>

namespace QtEtherscan {

/*
 **********************************************************************************************************************
 *
 * Configuration and setup
 *
 */

API::API(QObject *parent)
    : QObject(parent)
{
    setEtheriumNetwork(Mainnet);
}

API::API(const QString& apiKey,QObject* parent)
    : QObject(parent),m_apiKey(apiKey)
{
    setEtheriumNetwork(Mainnet);
}

void API::setEtheriumNetwork(Network etheriumNetwork)
{
    switch (etheriumNetwork) {
    case Mainnet:
        m_net.setApiHost(QLatin1String("https://api.etherscan.io/api"));
        return;
    case Goerli:
        m_net.setApiHost(QLatin1String("https://api-goerli.etherscan.io/api"));
        return;
    case Kovan:
        m_net.setApiHost(QLatin1String("https://api-kovan.etherscan.io/api"));
        return;
    case RInkeby:
        m_net.setApiHost(QLatin1String("https://api-rinkeby.etherscan.io/api"));
        return;
    case Ropsten:
        m_net.setApiHost(QLatin1String("https://api-ropsten.etherscan.io/api"));
        return;
    case Sepolia:
        m_net.setApiHost(QLatin1String("https://api-sepolia.etherscan.io/api"));
        return;
    }
    Q_ASSERT(false);
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "accounts" module
 *
 */

EtherBalance API::getEtherBalance(const QString& address, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("account") },
        { QLatin1String("action"),     QLatin1String("balance") },
        { QLatin1String("tag"),        tagToString(tag) },
        { QLatin1String("address"),    address }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EtherBalance>(makeApiCall(query));
}

AccountBalanceList API::getEtherBalance(const QStringList& addresses, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("account") },
        { QLatin1String("action"),     QLatin1String("balancemulti") },
        { QLatin1String("tag"),        tagToString(tag) },
        { QLatin1String("address"),    addresses.join(",") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<AccountBalanceList>(makeApiCall(query));
}

TransactionList API::getListOfNomalTransactions(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txlist") },
        { QLatin1String("address"),         address },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset) },
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<TransactionList>(makeApiCall(query));
}

InternalTransactionList API::getListOfInternalTransactions(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txlistinternal") },
        { QLatin1String("address"),         address },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset) },
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<InternalTransactionList>(makeApiCall(query));
}

InternalTransactionList API::getListOfInternalTransactions(const QString& txhash)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txlistinternal") },
        { QLatin1String("txhash"),          txhash }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<InternalTransactionList>(makeApiCall(query));
}

InternalTransactionList API::getListOfInternalTransactions(qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txlistinternal") },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)},
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<InternalTransactionList>(makeApiCall(query));
}

ERC20TokenTransferEventList API::getListOfERC20TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("tokentx") },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)},
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!address.isEmpty())         query.addQueryItem(QLatin1String("address"),address);
    if (!contractAddress.isEmpty()) query.addQueryItem(QLatin1String("contractAddress"),contractAddress);

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC20TokenTransferEventList>(makeApiCall(query));
}

ERC721TokenTransferEventList API::getListOfERC721TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("tokennfttx") },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)},
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!address.isEmpty())         query.addQueryItem(QLatin1String("address"),address);
    if (!contractAddress.isEmpty()) query.addQueryItem(QLatin1String("contractAddress"),contractAddress);

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC721TokenTransferEventList>(makeApiCall(query));
}

ERC1155TokenTransferEventList API::getListOfERC1155TokenTransfers(const QString& address, const QString& contractAddress, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("token1155tx") },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)},
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!address.isEmpty())         query.addQueryItem(QLatin1String("address"),address);
    if (!contractAddress.isEmpty()) query.addQueryItem(QLatin1String("contractAddress"),contractAddress);

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC1155TokenTransferEventList>(makeApiCall(query));
}

BlockList API::getListOfBlocksMinedByAddress(const QString& address, BlockType blockType, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txlist") },
        { QLatin1String("address"),         address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset) },
        { QLatin1String("blocktype"),       (blockType == UnclesType) ? QLatin1String("uncles") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<BlockList>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "logs" module
 *
 */

EventLogList API::getEventLogs(const QString& address, qint32 fromBlock, qint32 toBlock, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("logs") },
        { QLatin1String("action"),     QLatin1String("getLogs") },
        { QLatin1String("address"),    address },
        { QLatin1String("fromBlock"),  QString::number(fromBlock) },
        { QLatin1String("toBlock"),    QString::number(toBlock) },
        { QLatin1String("page"),       QString::number(page) },
        { QLatin1String("offset"),     QString::number(offset) },
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EventLogList>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "transaction" module
 *
 */

ContractExecutionStatus API::checkContractExecutionStatus(const QString& txHash)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("transaction")},
        { QLatin1String("action"),     QLatin1String("getstatus") },
        { QLatin1String("txhash"),     txHash}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ContractExecutionStatus>(makeApiCall(query));
}

bool API::checkTransactionReceiptStatus(const QString& txHash)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("transaction") },
        { QLatin1String("action"),     QLatin1String("gettxreceiptstatus") },
        { QLatin1String("txhash"),     txHash }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    QJsonObject response = makeApiCall(query);
    m_errorCode = getErrorCode(response);

    //According to https://docs.etherscan.io/api-endpoints/stats#check-transaction-receipt-status
    //Tip: The status field returns 0 for failed transactions and 1 for successful transactions.
    return m_errorCode == NoError ? (response.value("status").toString() == QLatin1String("1")) : false;
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "blocks" module
 *
 */

BlockAndUncleRewards API::getBlockAndUncleRewards(qint32 blockNumber)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("getblockreward") },
        { QLatin1String("blockno"),    QString::number(blockNumber)}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<BlockAndUncleRewards>(makeApiCall(query));

}

EstimatedBlockCountdown API::getEstimatedBlockCountdown(qint32 blockNumber)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("getblockcountdown") },
        { QLatin1String("blockno"),    QString::number(blockNumber) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EstimatedBlockCountdown>(makeApiCall(query));
}

qint32 API::getBlockNumberByTimestamp(const QDateTime& timestamp,Closest closest)
{
    return getBlockNumberByTimestamp(timestamp.toSecsSinceEpoch(),closest);
}

qint32 API::getBlockNumberByTimestamp(qint64 timestamp,Closest closest)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("getblocknobytime") },
        { QLatin1String("timestamp"),  QString::number(timestamp) },
        { QLatin1String("closest"),    (closest == Before) ? QLatin1String("before") : QLatin1String("after") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseInt(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "tokens" module
 *
 */

QString API::getERC20TokenTotalSupply(const QString& contractAddress)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("stats") },
        { QLatin1String("action"),          QLatin1String("tokensupply")},
        { QLatin1String("contractaddress"), contractAddress}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseString(makeApiCall(query));
}

QString API::getERC20TokenAccountBalance(const QString& contractAddress, const QString& address)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("tokenbalance") },
        { QLatin1String("contractaddress"), contractAddress},
        { QLatin1String("address"),         address}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseString(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "gas" module
 *
 */

quint32 API::getEstimationOfConfirmationTime(quint64 gasPrice)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("gastracker") },
        { QLatin1String("action"),     QLatin1String("gasestimate") },
        { QLatin1String("gaspreice"),  QString::number(gasPrice) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseInt(makeApiCall(query));
}

GasOracle API::getGasOracle()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("gastracker") },
        { QLatin1String("action"),     QLatin1String("gasoracle") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<GasOracle>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "stats" module
 *
 */

EtherBalance API::getTotalSupplyOfEther()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("ethsupply") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EtherBalance>(makeApiCall(query));
}

Ether2Supply API::getTotalSupplyOfEther2()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("ethsupply2") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<Ether2Supply>(makeApiCall(query));
}

EtherPrice API::getEtherLastPrice()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("ethprice") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EtherPrice>(makeApiCall(query));
}

NodesSize API::getEtheriumNodesSize(const QDate& startDate, const QDate& endDate, ClientType clientType, Syncmode syncmode, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("chainsize") },
        { QLatin1String("startdate"),  startDate.toString(Qt::ISODate) },
        { QLatin1String("enddate"),    endDate.toString(Qt::ISODate) },
        { QLatin1String("clienttype"), (clientType == Geth) ? QLatin1String("geth") : QLatin1String("parity") },
        { QLatin1String("syncmode"),   (syncmode == Default) ? QLatin1String("default") : QLatin1String("archive") },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<NodesSize>(makeApiCall(query));
}

NodesSize API::getEtheriumNodesSize(const QString& startDate, const QString& endDate, ClientType clientType, Syncmode syncmode, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("chainsize") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("clienttype"), (clientType == Geth) ? QLatin1String("geth") : QLatin1String("parity") },
        { QLatin1String("syncmode"),   (syncmode == Default) ? QLatin1String("default") : QLatin1String("archive") },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<NodesSize>(makeApiCall(query));
}

NodesCount API::getTotalNodesCount()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("nodecount") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<NodesCount>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Internal methods
 *
 */

QJsonObject API::makeApiCall(const QUrlQuery& urlQuery)
{
    return QJsonDocument::fromJson(m_net.request(urlQuery)).object();
}

template<class C>
C API::responseObject(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? C(response.value("result")) : C();
}

QString API::responseString(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? response.value("result").toString() : QString();
}

qint64 API::responseInt(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? response.value("result").toString().toDouble() : 0;
}

API::Error API::getErrorCode(const QJsonObject& jsonObject)
{
    if (jsonObject.isEmpty())
        return NetworkError;

    if (jsonObject.value("status").toString() == QLatin1String("1"))
        return NoError;

    if (jsonObject.value("message").toString() == QLatin1String("No transactions found"))
        return NoTransactionsFoundError;

    QString errorString = jsonObject.value("result").toString();
    if (errorString.contains(QLatin1String("Max rate limit reached")))
        return MaxRateError;

    if (errorString.contains(QLatin1String("upgrade to API Pro")))
        return ProRequiredError;

    if (errorString.contains(QLatin1String("No records found")))
        return NoRecorsFoundError;

    if (errorString.contains(QLatin1String("Invalid API Key")))
        return InvalidAPIKeyError;

    if (errorString.contains(QLatin1String("Invalid address format")))
        return InvalidAddressFormatError;

    if (errorString.contains(QLatin1String("Missing Or invalid Module")))
        return InvalidModuleNameError;

    if (errorString.contains(QLatin1String("Missing Or invalid Action")))
        return InvalidActionNameError;

    if (errorString.contains(QLatin1String("Missing or invalid parameter")))
        return InvalidParameterError;

    qDebug() << "Etherscan API Error: "<<errorString;
    return UnknownError;
}

} //namespace QtEtherscan


