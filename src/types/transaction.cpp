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

#include "transaction.h"

namespace QtEtherscan {

Transaction::Transaction() :
    m_blockNumber(InvalidBlockNumber)
{}

Transaction::Transaction(const QJsonObject& jsonObject) :
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong()),
    m_timeStamp(QDateTime::fromSecsSinceEpoch(jsonObject.value("timeStamp").toString().toLongLong())),
    m_hash(jsonObject.value("hash").toString()),
    m_nonce(jsonObject.value("nonce").toString().toDouble()),
    m_blockHash(jsonObject.value("blockHash").toString()),
    m_transactionIndex(jsonObject.value("transactionIndex").toString().toDouble()),
    m_from(jsonObject.value("from").toString()),
    m_to(jsonObject.value("to").toString()),
    m_value(jsonObject.value("value").toString()),
    m_gas(jsonObject.value("gas").toString().toDouble()),
    m_gasPrice(jsonObject.value("gasPrice").toString().toDouble()),
    m_isErrorString(jsonObject.value("isError").toString()),
    m_txreceiptStatusString(jsonObject.value("txreceipt_status").toString()),
    m_input(jsonObject.value("input").toString()),
    m_contractAddress(jsonObject.value("contractAddress").toString()),
    m_cumulativeGasUsed(jsonObject.value("cumulativeGasUsed").toString().toDouble()),
    m_gasUsed(jsonObject.value("gasUsed").toString().toDouble()),
    m_confirmations(jsonObject.value("confirmations").toString().toDouble()),
    m_methodIdString(jsonObject.value("methodId").toString()),
    m_functionName(jsonObject.value("functionName").toString())
{}

} //namespace QtEtherscan
