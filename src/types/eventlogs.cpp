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

#include "./eventlogs.h"

namespace QtEtherscan {

EventLog::EventLog() :
    m_blockNumber(InvalidBlockNumber)
{}

EventLog::EventLog(const QJsonObject& jsonObject) :
    m_address(jsonObject.value("address").toString()),
    m_dataString(jsonObject.value("data").toString()),
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong(nullptr,0)),
    m_timeStamp(QDateTime::fromSecsSinceEpoch(jsonObject.value("timeStamp").toString().toLongLong(nullptr,0))),
    m_gasPrice(jsonObject.value("gasPrice").toString().toLong(nullptr,0)),
    m_gasUsed(jsonObject.value("gasUsed").toString().toLong(nullptr,0)),
    m_logIndexString(jsonObject.value("logIndex").toString()),
    m_transactionHash(jsonObject.value("transactionHash").toString()),
    m_transactionIndexString(jsonObject.value("transactionIndex").toString())
{
    foreach (const QJsonValue& value, jsonObject.value("topics").toArray())
        m_topics.append(value.toString());
}

} //namespace QtEtherscan
