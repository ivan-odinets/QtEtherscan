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

#include "./internaltransaction.h"

namespace QtEtherscan {

InternalTransaction::InternalTransaction() :
    m_blockNumber(InvalidBlockNumber),
    m_timeStamp(0),
    m_gas(0),
    m_gasUsed(0)
{}

InternalTransaction::InternalTransaction(const QJsonObject& jsonObject) :
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong()),
    m_timeStamp(jsonObject.value("timeStamp").toString().toLongLong()),
    m_hash(jsonObject.value("hash").toString()),
    m_from(jsonObject.value("from").toString()),
    m_to(jsonObject.value("to").toString()),
    m_value(jsonObject.value("value").toString()),
    m_contractAddress(jsonObject.value("contractAddress").toString()),
    m_input(jsonObject.value("input").toString()),
    m_typeString(jsonObject.value("type").toString()),
    m_gas(jsonObject.value("gas").toString().toULongLong()),
    m_gasUsed(jsonObject.value("gasUsed").toString().toULongLong()),
    m_traceIdString(jsonObject.value("traceId").toString()),
    m_isErrorString(jsonObject.value("isError").toString()),
    m_errCodeString(jsonObject.value("errCode").toString())
{}

} //namespace QtEtherscan
