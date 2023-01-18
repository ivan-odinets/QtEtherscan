/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023 Ivan Odinets
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

#include "./blockandunclerewards.h"

namespace QtEtherscan {

BlockAndUncleRewards::BlockAndUncleRewards() :
    m_blockNumber(InvalidBlockNumber)
{}

BlockAndUncleRewards::BlockAndUncleRewards(const QJsonObject& jsonObject) :
    m_blockNumber(jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toLong()),
    m_timestamp(QDateTime::fromSecsSinceEpoch(jsonObject.value("timeStamp").toString().toLongLong())),
    m_blockMiner(jsonObject.value("blockMiner").toString()),
    m_blockReward(jsonObject.value("blockReward").toString()),
    m_uncles(jsonObject.value("uncles").toArray()),
    m_uncleInclusionReward(jsonObject.value("uncleInclusionReward").toString())
{}

} //namespace QtEtherscan
