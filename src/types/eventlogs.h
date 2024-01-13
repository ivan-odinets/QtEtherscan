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

#ifndef EVENTLOGS_H
#define EVENTLOGS_H

#include <QDebug>
#include <QJsonObject>

#include "./constants.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class EventLog src/types/eventlogs.h
 *  @brief A list of such objects is returned by API::getEventLogs, API::getEventLogsByTopics and API::getEventLogsByAddressTopics
 *         methods. Nothing more than a QList with some extra constructors (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-topics
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address-filtered-by-topics */

class EventLog
{
public:
    EventLog();
    EventLog(const QJsonObject& jsonObject);
    EventLog(const QJsonValue& jsonValue) :
        EventLog(jsonValue.toObject()) {}

    /*! @brief Returns true if this EventLog object is valid and contains reasonable information. EventLog object is considered
     *         to be valid if blockNumber() contains anything but not -1. */
    bool           isValid() const                    { return m_blockNumber != InvalidBlockNumber; }

    QString        address() const                    { return m_address; }
    QStringList    topics() const                     { return m_topics; }
    QString        dataString() const                 { return m_dataString; }
    qint32         blockNumber() const                { return m_blockNumber; }
    QString        blockHash() const                  { return m_blockHash; }
    QDateTime      timeStamp() const                  { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }
    quint64        gasPrice() const                   { return m_gasPrice; }
    quint64        gasUsed() const                    { return m_gasUsed; }
    QString        logIndexString() const             { return m_logIndexString; }
    QString        transactionHash() const            { return m_transactionHash; }
    QString        transactionIndexString() const     { return m_transactionIndexString; }

private:
    QString        m_address;
    QStringList    m_topics;
    QString        m_dataString;
    qint32         m_blockNumber;
    QString        m_blockHash;
    qint64         m_timeStamp;
    quint64        m_gasPrice;
    quint64        m_gasUsed;
    QString        m_logIndexString;
    QString        m_transactionHash;
    QString        m_transactionIndexString;
};

inline QDebug operator<< (QDebug dbg, const EventLog& eventLog)
{
    dbg.nospace() << qUtf8Printable(QString("EventLog(address=%1; blockNumber=%2; timeStamp=%3)")
                                    .arg(eventLog.address())
                                    .arg(eventLog.blockNumber())
                                    .arg(eventLog.timeStamp().toString()));

    return dbg.maybeSpace();
}

/*! @typedef EventLogList src/types/eventlogs.h
 *  @brief This is a list of EventLog objects. It is returned by API::getEventLogs, API::getEventLogsByTopics and
 *         API::getEventLogsByAddressTopics methods. Nothing more than a QList with some extra constructors
 *         (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-topics
 * @see https://docs.etherscan.io/api-endpoints/logs#get-event-logs-by-address-filtered-by-topics */

typedef JsonObjectsList<EventLog> EventLogList;

inline QDebug operator<< (QDebug dbg, const EventLogList& eventLogList)
{
    dbg.nospace() << qUtf8Printable(QString("EventLogList(count=%1)")
                                    .arg(eventLogList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // EVENTLOGS_H
