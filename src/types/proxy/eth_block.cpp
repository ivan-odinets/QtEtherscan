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

#include "eth_block.h"

#include <QJsonArray>

namespace QtEtherscan {

namespace Proxy {

Block::Block() :
    m_number(InvalidBlockNumber),
    m_nonce(0),
    m_size(InvalidBlockSize),
    m_gasLimit(0),
    m_gasUsed(0),
    m_timestamp(0)
{}

Block::Block(const QJsonObject& jsonObject) :
    m_number(jsonObject.value("number").toString(InvalidBlockNumberString).toInt(nullptr,0)),
    m_hash(jsonObject.value("hash").toString()),
    m_parentHash(jsonObject.value("parentHash").toString()),
    m_nonce(jsonObject.value("nonce").toString().toULongLong(nullptr,0)),
    m_sha3Uncles(jsonObject.value("sha3Uncles").toString()),
    m_logsBloom(jsonObject.value("logsBloom").toString()),
    m_transactionsRoot(jsonObject.value("transactionsRoot").toString()),
    m_stateRoot(jsonObject.value("stateRoot").toString()),
    m_receiptsRoot(jsonObject.value("receiptsRoot").toString()),
    m_miner(jsonObject.value("miner").toString()),
    m_difficulty(jsonObject.value("difficulty").toString()),
    m_totalDifficulty(jsonObject.value("totalDifficulty").toString()),
    m_extraData(jsonObject.value("extraData").toString()),
    m_size(jsonObject.value("size").toString(InvalidBlockSizeString).toInt(nullptr,0)),
    m_gasLimit(jsonObject.value("gasLimit").toString().toULongLong(nullptr,0)),
    m_gasUsed(jsonObject.value("gasUsed").toString().toULongLong(nullptr,0)),
    m_timestamp(jsonObject.value("timestamp").toString().toLongLong(nullptr,0))
{
    // Transactions
    QJsonArray transactionsArray = jsonObject.value("transactions").toArray();
    for (auto i = transactionsArray.constBegin(); i != transactionsArray.constEnd(); i++) {
        if (i->isString()) {
            m_transactionHashList.append(i->toString());
        } else if (i->isObject()) {
            Transaction tr(i->toObject());
            m_transactionHashList.append(tr.hash());
            m_transactionList.append(std::move(tr));
        }
    }

    QJsonArray unclesArray = jsonObject.value("uncles").toArray();
    foreach (const QJsonValue& uncleValue, unclesArray)
        m_uncles.append(uncleValue.toString());
}

} // namespace Proxy

} // namespace QtEtherscan
