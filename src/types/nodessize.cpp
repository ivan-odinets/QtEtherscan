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

#include "./nodessize.h"

namespace QtEtherscan {

ChainSize::ChainSize() :
    m_blockNumber(InvalidBlockNumber),
    m_chainSize(0)
{}

ChainSize::ChainSize(const QJsonObject& jsonObject) :
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong()),
    m_timeStamp(QDate::fromString(jsonObject.value("chainTimeStamp").toString(),Qt::ISODate)),
    m_chainSize(jsonObject.value("chainSize").toString().toULongLong())
{
    m_clientType = (QString::compare(jsonObject.value("clientType").toString(),QLatin1String("Geth"),Qt::CaseInsensitive) == 0)
            ? Geth : Parity;

    m_syncMode = (QString::compare(jsonObject.value("syncMode").toString(),QLatin1String("Default"),Qt::CaseInsensitive) == 0)
            ? Default : Archive;
};

} //namespace QtEtherscan
