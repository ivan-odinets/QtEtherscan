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

#ifndef EVENTLOGS_H
#define EVENTLOGS_H

#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "./global.h"

namespace QtEtherscan {

class EventLog
{
public:
    EventLog();
    EventLog(const QJsonObject& jsonObject);
    EventLog(const QJsonValue& jsonValue) :
        EventLog(jsonValue.toObject()) {}

    bool           isValid() const                    { return m_blockNumber != InvalidBlockNumber; }

    QString        address() const                    { return m_address; }
    QStringList    topics() const                     { return m_topics; }
    QString        dataString() const                 { return m_dataString; }
    qint32         blockNumber() const                { return m_blockNumber; }
    QDateTime      timeStamp() const                  { return m_timeStamp; }
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
    QDateTime      m_timeStamp;
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

typedef JsonObjectsList<EventLog> EventLogList;

inline QDebug operator<< (QDebug dbg, const EventLogList& eventLogList)
{
    dbg.nospace() << qUtf8Printable(QString("EventLogList(count=%1)")
                                    .arg(eventLogList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // EVENTLOGS_H
