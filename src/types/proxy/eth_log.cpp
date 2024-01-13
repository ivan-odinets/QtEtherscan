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

#include "eth_log.h"

namespace QtEtherscan {

namespace Proxy {

Log::Log() :
    m_removed(true),
    m_logIndex(0),
    m_transactionIndex(0),
    m_blockNumber(InvalidBlockNumber)
{}

Log::Log(const QJsonObject& jsonObject) :
    m_removed(jsonObject.value("removed").toBool()),
    m_logIndex(jsonObject.value("logIndex").toString().toInt(nullptr,0)),
    m_transactionIndex(jsonObject.value("transactionIndex").toString().toInt(nullptr,0)),
    m_transactionHash(jsonObject.value("transactionHash").toString()),
    m_blockHash(jsonObject.value("blockHash").toString()),
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toInt(nullptr,0)),
    m_address(jsonObject.value("address").toString()),
    m_data(jsonObject.value("data").toString())
{
    QJsonArray topicsJsonArray = jsonObject.value("topics").toArray();
    for (const QJsonValue& topicJsonValue : topicsJsonArray)
        m_topics.append(topicJsonValue.toString());
}

} // namespace Proxy

} // namespace QtEtherscan
