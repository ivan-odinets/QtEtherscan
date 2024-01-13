/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets
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

#ifndef LOG_H
#define LOG_H

#include <QJsonObject>
#include <QJsonValue>
#include <QString>

#include "./eth_helper.h"
#include "../constants.h"
#include "../jsonobjectslist.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class Log src/types/proxy/eth_log.h
 *  @brief Object of this type contains data about log object.
 *  @details All string values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_getfilterchanges
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactionreceipt */

class Log
{
public:
    Log();
    Log(const QJsonObject& jsonObject);
    Log(const QJsonValue& jsonValue) :
        Log(jsonValue.toObject()) {}

    /*! @brief Returns true if this Poxy::Log object is valid and contains reasonable information. Proxy::Log object is considered
     *         to be valid if blockNumber() contains anything but not -1. */
    bool isValid() const                    { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns true when the log was removed, due to a chain reorganization. false if its a valid log. */
    bool removed() const                    { return m_removed; }

    /*! @brief Returns integer of the log index position in the block. */
    qint32 logIndex() const                 { return m_logIndex; }

    /*! @brief Returns string with the log index position in the block. */
    QString logIndexString() const          { return Helper::intToEthString(m_logIndex); }

    /*! @brief Returns integer of the transactions index position log was created from. */
    qint32 transactionIndex() const         { return m_transactionIndex; }

    /*! @brief Returns string with the transactions index position log was created from. */
    QString transactionIndexString() const  { return Helper::intToEthString(m_transactionIndex); }

    /*! @brief Returns string with the hash of the transactions this log was created from.*/
    QString transactionHash() const         { return m_transactionHash; }

    /*! @brief Returns string with the hash of the block where this log was in. */
    QString blockHash() const               { return m_blockHash; }

    /*! @brief Returns integer with the block number where this log was in. */
    qint32 blockNumber() const              { return m_blockNumber; }

    /*! @brief Returns string with the block number where this log was in. */
    QString blockNumberString() const       { return Helper::intToEthString(m_blockNumber); }

    /*! @brief Returns address from which this log originated. */
    QString address() const                 { return m_address; }

    /*! @brief Returns string with the data field of the log object. Data field contains zero or more 32 Bytes non-indexed
     *         arguments of the log. */
    QString data() const                    { return m_data; }

    /*! @brief Returns QStringList containing topics field of the log object. */
    QStringList topics() const              { return m_topics; }

private:
    bool           m_removed;
    qint32         m_logIndex;
    qint32         m_transactionIndex;
    QString        m_transactionHash;
    QString        m_blockHash;
    qint32         m_blockNumber;
    QString        m_address;
    QString        m_data;
    QStringList    m_topics;
};

inline QDebug operator<< (QDebug dbg, const Log& log)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::Log(blockNumber=%1; transactionHash=%2;)")
                                    .arg(log.blockNumber())
                                    .arg(log.transactionHash()));

    return dbg.maybeSpace();
}

/*! @typedef LogList src/types/proxy/eth_log.h
 *  @brief This is a list of Proxy::Log objects. Nothing more than a QList with some extra constructors (JsonObjectList). */

typedef JsonObjectsList<Log> LogList;

inline QDebug operator<< (QDebug dbg, const LogList& logList)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::LogList(count=%1)")
                                    .arg(logList.count()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // LOG_H
