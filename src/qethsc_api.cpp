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

#include "./qethsc_api.h"

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
    : QObject{parent},m_errorCode{NoError}
{
    setEtheriumNetwork(Mainnet);
}

API::API(const QString& apiKey,QObject* parent)
    : QObject{parent},
      m_apiKey{apiKey},m_errorCode{NoError}
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

QJsonObject API::call(const QUrlQuery& query)
{
    //if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    QJsonObject result = makeApiCall(query);
    m_errorCode = getErrorCode(result);
    return result;
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
        { QLatin1String("action"),          QLatin1String("getminedblocks") },
        { QLatin1String("address"),         address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset) },
        { QLatin1String("blocktype"),       (blockType == UnclesType) ? QLatin1String("uncles") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<BlockList>(makeApiCall(query));
}

BlockList API::getListOfBlocksValidatedByAddress(const QString& address, BlockType blockType, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("getminedblocks") },
        { QLatin1String("address"),         address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset) },
        { QLatin1String("blocktype"),       (blockType == UnclesType) ? QLatin1String("uncles") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<BlockList>(makeApiCall(query));
}

BeaconChainWithdrawalList API::getBeaconChainWithdrawals(const QString& address, qint32 startBlock, qint32 endBlock, int page, int offset, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("txsBeaconWithdrawal") },
        { QLatin1String("address"),         address },
        { QLatin1String("startblock"),      QString::number(startBlock) },
        { QLatin1String("endblock"),        QString::number(endBlock) },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)},
        { QLatin1String("sort"),            (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<BeaconChainWithdrawalList>(makeApiCall(query));
}

EtherBalance API::getHistoricalEtherBalance(const QString& address, qint32 blockNumber)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("balancehistory") },
        { QLatin1String("address"),         address },
        { QLatin1String("blockno"),         QString::number(blockNumber) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EtherBalance>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "contract" module
 *
 */

QJsonArray API::getContratABI(const QString& address)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("contract") },
        { QLatin1String("action"),          QLatin1String("getabi") },
        { QLatin1String("address"),         address }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    QJsonObject response = makeApiCall(query);
    m_errorCode = getErrorCode(response);
    if (m_errorCode != NoError)
        return QJsonArray();

    return QJsonDocument::fromJson(response.value("result").toString().toLocal8Bit()).array();
}

ContractSourceCode API::getContractSourceCode(const QString& address)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("contract") },
        { QLatin1String("action"),          QLatin1String("getsourcecode") },
        { QLatin1String("address"),         address }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ContractSourceCode>(makeApiCall(query));
}

ContractCreatorList API::getContractCreatorList(const QStringList& addresses)
{
    QUrlQuery query({
        { QLatin1String("module"),               QLatin1String("contract")               },
        { QLatin1String("action"),               QLatin1String("getcontractcreation")    },
        { QLatin1String("contractaddresses"),    addresses.join(',')                     }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ContractCreatorList>(makeApiCall(query));
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

DailyBlockSizeList API::getDailyAverageBlockSize(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("dailyavgblocksize") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyBlockSizeList>(makeApiCall(query));
}

DailyBlockSizeList API::getDailyAverageBlockSize(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyAverageBlockSize(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyBlockCountRewardsList API::getDailyBlockCountRewards(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("dailyblkcount") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyBlockCountRewardsList>(makeApiCall(query));
}

DailyBlockCountRewardsList API::getDailyBlockCountRewards(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyBlockCountRewards(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyBlockRewardsList API::getDailyBlockRewards(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("dailyblockrewards") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyBlockRewardsList>(makeApiCall(query));
}

DailyBlockRewardsList API::getDailyBlockRewards(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyBlockRewards(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyBlockTimeList API::getDailyAverageTimeForBlock(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("dailyavgblocktime") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyBlockTimeList>(makeApiCall(query));
}

DailyBlockTimeList API::getDailyAverageTimeForBlock(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyAverageTimeForBlock(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyUncleCountRewardsList API::getDailyUncleCountRewards(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("block") },
        { QLatin1String("action"),     QLatin1String("dailyuncleblkcount") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyUncleCountRewardsList>(makeApiCall(query));
}

DailyUncleCountRewardsList API::getDailyUncleCountRewards(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyUncleCountRewards(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
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

EventLogList API::getEventLogsByTopics(const QMap<QString,QString>& topics, qint32 fromBlock, qint32 toBlock, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("logs") },
        { QLatin1String("action"),     QLatin1String("getLogs") },
        { QLatin1String("fromBlock"),  QString::number(fromBlock) },
        { QLatin1String("toBlock"),    QString::number(toBlock) },
        { QLatin1String("page"),       QString::number(page) },
        { QLatin1String("offset"),     QString::number(offset) },
    });

    for (auto i = topics.constBegin(); i != topics.constEnd(); i++)
        query.addQueryItem(i.key(),i.value());

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EventLogList>(makeApiCall(query));
}

EventLogList API::getEventLogsByAddressTopics(const QMap<QString,QString>& topics, const QString& address, qint32 fromBlock, qint32 toBlock, int page, int offset)
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

    for (auto i = topics.constBegin(); i != topics.constEnd(); i++)
        query.addQueryItem(i.key(),i.value());

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EventLogList>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods from "proxy" module
 *
 */

Proxy::BlockNumberResponse API::eth_blockNumber()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_blockNumber") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::BlockNumberResponse>(makeApiCall(query));
}

Proxy::BlockResponse API::eth_getBlockByNumber(const QString blockNumberString, bool boolean)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getBlockByNumber") },
        { QLatin1String("tag"),        blockNumberString },
        { QLatin1String("boolean"),    (boolean) ? QLatin1String("true") : QLatin1String("false") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::BlockResponse>(makeApiCall(query));
}

Proxy::BlockResponse API::eth_getBlockByNumber(qint32 blockNumber, bool boolean)
{
    return eth_getBlockByNumber(Proxy::Helper::intToEthString(blockNumber),boolean);
}

Proxy::BlockResponse API::eth_getUncleByBlockNumberAndIndex(const QString& blockNumberString,const QString& indexString)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getUncleByBlockNumberAndIndex") },
        { QLatin1String("tag"),        blockNumberString },
        { QLatin1String("index"),      indexString }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::BlockResponse>(makeApiCall(query));
}

Proxy::BlockResponse API::eth_getUncleByBlockNumberAndIndex(qint32 blockNumber,int index)
{
    return eth_getUncleByBlockNumberAndIndex(Proxy::Helper::intToEthString(blockNumber),
                                             Proxy::Helper::intToEthString(index));
}

Proxy::TransactionCountResponse API::eth_getBlockTransactionCountByNumber(const QString& blockNumberString)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getBlockTransactionCountByNumber") },
        { QLatin1String("tag"),        blockNumberString }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionCountResponse>(makeApiCall(query));
}

Proxy::TransactionCountResponse API::eth_getBlockTransactionCountByNumber(qint32 blockNumber)
{
    return eth_getBlockTransactionCountByNumber(Proxy::Helper::intToEthString(blockNumber));
}

Proxy::TransactionResponse API::eth_getTransactionByHash(const QString& txHash)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getTransactionByHash") },
        { QLatin1String("txhash"),     txHash }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionResponse>(makeApiCall(query));
}

Proxy::TransactionResponse API::eth_getTransactionByBlockNumberAndIndex(const QString& blockNumber, const QString& index)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getTransactionByBlockNumberAndIndex") },
        { QLatin1String("tag"),        blockNumber },
        { QLatin1String("index"),      index }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionResponse>(makeApiCall(query));
}

Proxy::TransactionResponse API::eth_getTransactionByBlockNumberAndIndex(qint32 blockNumber, qint32 index)
{
    return eth_getTransactionByBlockNumberAndIndex(Proxy::Helper::intToEthString(blockNumber),
                                                   Proxy::Helper::intToEthString(index));
}

Proxy::TransactionCountResponse API::eth_getTransactionCount(const QString& address, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getTransactionCount") },
        { QLatin1String("address"),    address },
        { QLatin1String("tag"),        tagToString(tag) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionCountResponse>(makeApiCall(query));
}

Proxy::TransactionHashResponse API::eth_sendRawTransaction(const QString& hex)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_sendRawTransaction") },
        { QLatin1String("hex"),        hex }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionHashResponse>(makeApiCall(query));
}

Proxy::TransactionReceiptResponse API::eth_getTransactionReceipt(const QString& txHash)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getTransactionReceipt") },
        { QLatin1String("txhash"),     txHash }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::TransactionReceiptResponse>(makeApiCall(query));
}

Proxy::StringResponse API::eth_call(const QString& to, const QString& data, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_call") },
        { QLatin1String("to"),         to },
        { QLatin1String("data"),       data },
        { QLatin1String("tag"),        tagToString(tag) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::StringResponse>(makeApiCall(query));
}

Proxy::StringResponse API::eth_getCode(const QString& address, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getCode") },
        { QLatin1String("address"),    address },
        { QLatin1String("tag"),        tagToString(tag) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::StringResponse>(makeApiCall(query));
}

Proxy::StringResponse API::eth_getStorageAt(const QString& address, const QString& positionString, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_getCode") },
        { QLatin1String("address"),    address },
        { QLatin1String("position"),   positionString },
        { QLatin1String("tag"),        tagToString(tag) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::StringResponse>(makeApiCall(query));
}

Proxy::GasPriceResponse API::eth_gasPrice()
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_gasPrice") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::GasPriceResponse>(makeApiCall(query));
}

Proxy::StringResponse API::eth_estimateGas(const QString& data, const QString& to,const QString& value,const QString& gasPrice, const QString& gas)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("proxy") },
        { QLatin1String("action"),     QLatin1String("eth_estimateGas") },
        { QLatin1String("data"),       data },
        { QLatin1String("to"),         to },
        { QLatin1String("value"),      value },
        { QLatin1String("gasPrice"),   gasPrice},
        { QLatin1String("gas"),        gas }

    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return proxyResponse<Proxy::StringResponse>(makeApiCall(query));
}

Proxy::StringResponse API::eth_estimateGas(const QString& data, const QString& to,const QString& value,quint64 gasPrice, quint64 gas)
{
    return eth_estimateGas(data,to,value,Proxy::Helper::intToEthString(gasPrice),
                                         Proxy::Helper::intToEthString(gas));
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

QString API::getERC20TokenAccountBalance(const QString& contractAddress, const QString& address, Tag tag)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("tokenbalance") },
        { QLatin1String("contractaddress"), contractAddress},
        { QLatin1String("tag"),             tagToString(tag) },
        { QLatin1String("address"),         address}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseString(makeApiCall(query));
}

QString API::getHistoricalERC20TokenSupply(const QString& contractAddress, qint32 blockNumber)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("stats") },
        { QLatin1String("action"),          QLatin1String("tokensupplyhistory") },
        { QLatin1String("contractaddress"), contractAddress},
        { QLatin1String("blockno"),         QString::number(blockNumber) }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseString(makeApiCall(query));
}

QString API::getHistoricalERC20TokenBalance(const QString& contractAddress, const QString& address, qint32 blockNumber)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("tokenbalancehistory") },
        { QLatin1String("contractaddress"), contractAddress},
        { QLatin1String("blockno"),         QString::number(blockNumber) },
        { QLatin1String("address"),         address}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseString(makeApiCall(query));
}

ERC20TokenHolderList API::getERC20TokenHolders(const QString& contractAddress, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("token") },
        { QLatin1String("action"),          QLatin1String("tokenholderlist") },
        { QLatin1String("contractaddress"), contractAddress },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC20TokenHolderList>(makeApiCall(query));
}

TokenInfo API::getTokenInfo(const QString& contractAddress)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("token") },
        { QLatin1String("action"),          QLatin1String("tokeninfo") },
        { QLatin1String("contractaddress"), contractAddress }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<TokenInfo>(makeApiCall(query));
}

ERC20TokenHoldingList API::getERC20TokenHolding(const QString& address, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("addresstokenbalance") },
        { QLatin1String("address"), address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC20TokenHoldingList>(makeApiCall(query));
}

ERC721TokenHoldingList API::getERC721TokenHolding(const QString& address, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("addresstokennftbalance") },
        { QLatin1String("address"), address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC721TokenHoldingList>(makeApiCall(query));
}

ERC721TokenInventoryList API::getERC721TokenInventory(const QString& address,const QString& contractAddress, int page, int offset)
{
    QUrlQuery query({
        { QLatin1String("module"),          QLatin1String("account") },
        { QLatin1String("action"),          QLatin1String("addresstokennftinventory") },
        { QLatin1String("contractaddress"), contractAddress },
        { QLatin1String("address"), address },
        { QLatin1String("page"),            QString::number(page) },
        { QLatin1String("offset"),          QString::number(offset)}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<ERC721TokenInventoryList>(makeApiCall(query));
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

DailyGasLimitList API::getDailyAverageGasLimit(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailyavggaslimit") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyGasLimitList>(makeApiCall(query));
}

DailyGasLimitList API::getDailyAverageGasLimit(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyAverageGasLimit(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyTotalGasList API::getDailyTotalGasAmount(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailygasused") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyTotalGasList>(makeApiCall(query));
}

DailyTotalGasList API::getDailyTotalGasAmount(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyTotalGasAmount(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyGasPriceList API::getDailyAverageGasPrice(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailyavggasprice") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyGasPriceList>(makeApiCall(query));
}

DailyGasPriceList API::getDailyAverageGasPrice(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyAverageGasPrice(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
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

DailyTransactionFeesList API::getDailyNetworkTransactionFee(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailytxnfee") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyTransactionFeesList>(makeApiCall(query));
}

DailyTransactionFeesList API::getDailyNetworkTransactionFee(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyNetworkTransactionFee(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyNewAddressCountList API::getDailyNewAddressCount(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailynewaddress") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyNewAddressCountList>(makeApiCall(query));
}

DailyNewAddressCountList API::getDailyNewAddressCount(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyNewAddressCount(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyNetworkUtilizationList API::getDailyNetworkUtilization(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailynetutilization") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyNetworkUtilizationList>(makeApiCall(query));
}

DailyNetworkUtilizationList API::getDailyNetworkUtilization(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyNetworkUtilization(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyNetworkHashrateList API::getDailyNetworkHashrate(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailyavghashrate") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyNetworkHashrateList>(makeApiCall(query));
}

DailyNetworkHashrateList API::getDailyNetworkHashrate(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyNetworkHashrate(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyTransactionCountList API::getDailyTransactionCount(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailytx") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyTransactionCountList>(makeApiCall(query));
}

DailyTransactionCountList API::getDailyTransactionCount(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyTransactionCount(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyNetworkDifficultyList API::getDailyNetworkDifficulty(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("dailyavgnetdifficulty") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyNetworkDifficultyList>(makeApiCall(query));
}

DailyNetworkDifficultyList API::getDailyNetworkDifficulty(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getDailyNetworkDifficulty(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

DailyMarketCapList API::getHistoricalEtherMarketCapitalization(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("ethdailymarketcap") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<DailyMarketCapList>(makeApiCall(query));
}

DailyMarketCapList API::getHistoricalEtherMarketCapitalization(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getHistoricalEtherMarketCapitalization(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

EtherHistoricalPriceList API::getEtherHistoricalPrice(const QString& startDate, const QString& endDate, Sort sort)
{
    QUrlQuery query({
        { QLatin1String("module"),     QLatin1String("stats") },
        { QLatin1String("action"),     QLatin1String("ethdailyprice") },
        { QLatin1String("startdate"),  startDate },
        { QLatin1String("enddate"),    endDate },
        { QLatin1String("sort"),       (sort == Asc) ? QLatin1String("asc") : QLatin1String("desc") }
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem(QLatin1String("apikey"),m_apiKey);

    return responseObject<EtherHistoricalPriceList>(makeApiCall(query));
}

EtherHistoricalPriceList API::getEtherHistoricalPrice(const QDate& startDate, const QDate& endDate, Sort sort)
{
    return getEtherHistoricalPrice(startDate.toString(Qt::ISODate),endDate.toString(Qt::ISODate),sort);
}

/*
 **********************************************************************************************************************
 *
 * Internal methods
 *
 */

QJsonObject API::makeApiCall(const QUrlQuery& urlQuery)
{
    qDebug() << m_net.request(urlQuery);
    return QJsonDocument::fromJson(m_net.request(urlQuery)).object();
}

template<class C>
C API::responseObject(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return (m_errorCode == NoError) ? C(response.value("result")) : C();
}

template<class C>
C API::proxyResponse(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return (m_errorCode == NoError) ? C(response) : C();
}

QString API::responseString(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? response.value("result").toString() : QString();
}

qint64 API::responseInt(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? response.value("result").toString().toLongLong() : 0;
}

API::Error API::getErrorCode(const QJsonObject& jsonObject)
{
    if (jsonObject.isEmpty())
        return NetworkError;

    // If we have reply for etherscan API method - we have status field in reply QJsonObject
    if (jsonObject.value("status").toString() == QLatin1String("1"))
        return NoError;

    // If we have reply for etherscan geth/parity method - we have "jsonrpc" field in reply QJsonObject
    if (jsonObject.contains("jsonrpc"))
        return NoError;

    if (jsonObject.value("message").toString() == QLatin1String("No transactions found"))
        return NoTransactionsFoundError;

    QString errorString = jsonObject.value("result").toString();
    m_errorMessage = errorString;
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

//    qDebug() << "Etherscan API Error: "<<errorString;
    return UnknownError;
}

QString API::tagToString(Tag tag)
{
    switch (tag) {
    case Latest:
        return QLatin1String("latest");
    case Pending:
        return QLatin1String("pending");
    case Earliest:
        return QLatin1String("earliest");
    }
    Q_ASSERT(false);
    return QString();
}

} //namespace QtEtherscan


