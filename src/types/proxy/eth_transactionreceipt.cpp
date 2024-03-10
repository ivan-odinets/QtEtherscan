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

#include "./eth_transactionreceipt.h"

namespace QtEtherscan {

namespace Proxy {

TransactionReceipt::TransactionReceipt() :
    m_transactionIndex(0),
    m_number(InvalidBlockNumber),
    m_cumulativeGasUsed(0),
    m_effectiveGasPrice(0),
    m_gasUsed(0),
    m_type(0)
{}

TransactionReceipt::TransactionReceipt(const QJsonObject& jsonObject) :
    m_transactionHash(jsonObject.value("transactionHash").toString()),
    m_transactionIndex(jsonObject.value("transactionIndex").toString().toInt(nullptr,0)),
    m_blockHash(jsonObject.value("blockHash").toString()),
    m_number(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toInt(nullptr,0)),
    m_from(jsonObject.value("from").toString()),
    m_to(jsonObject.value("to").toString()),
    m_cumulativeGasUsed(jsonObject.value("cumulativeGasUsed").toString().toULongLong(nullptr,0)),
    m_effectiveGasPrice(jsonObject.value("effectiveGasPrice").toString().toULongLong(nullptr,0)),
    m_gasUsed(jsonObject.value("gasUsed").toString().toULongLong(nullptr,0)),
    m_contractAddress(jsonObject.value("contractAddress").toString()),
    m_logsBloom(jsonObject.value("logsBloom").toString()),
    m_logs(jsonObject.value("logs")),
    m_type(jsonObject.value("type").toString().toInt(nullptr,0))
{}

} // namespace Proxy

} // namespace QtEtherscan
