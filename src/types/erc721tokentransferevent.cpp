/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets
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

#include "./erc721tokentransferevent.h"

namespace QtEtherscan {

ERC721TokenTransferEvent::ERC721TokenTransferEvent() :
    m_blockNumber(InvalidBlockNumber),
    m_timeStamp(0),
    m_nonce(0),
    m_tokenDecimal(0),
    m_transactionIndex(0),
    m_gas(0),
    m_gasPrice(0),
    m_gasUsed(0),
    m_cumulativeGasUsed(0),
    m_confirmations(0)
{}

ERC721TokenTransferEvent::ERC721TokenTransferEvent(const QJsonObject& jsonObject) :
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong()),
    m_timeStamp(jsonObject.value("timeStamp").toString().toLongLong()),
    m_hash(jsonObject.value("hash").toString()),
    m_nonce(jsonObject.value("nonce").toString().toULongLong()),
    m_blockHash(jsonObject.value("blockHash").toString()),
    m_from(jsonObject.value("from").toString()),
    m_contractAddress(jsonObject.value("contractAddress").toString()),
    m_to(jsonObject.value("to").toString()),
    m_tokenIdString(jsonObject.value("tokenID").toString()),
    m_tokenName(jsonObject.value("tokenName").toString()),
    m_tokenSymbol(jsonObject.value("tokenSymbol").toString()),
    m_tokenDecimal(jsonObject.value("tokenDecimal").toString().toUInt()),
    m_transactionIndex(jsonObject.value("transactionIndex").toString().toUInt()),
    m_gas(jsonObject.value("gas").toString().toULongLong()),
    m_gasPrice(jsonObject.value("gasPrice").toString().toULongLong()),
    m_gasUsed(jsonObject.value("gasUsed").toString().toULongLong()),
    m_cumulativeGasUsed(jsonObject.value("cumulativeGasUsed").toString().toULongLong()),
    m_input(jsonObject.value("input").toString()),
    m_confirmations(jsonObject.value("confirmations").toString().toULongLong())
{}

} //namespace QtEtherscan
