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

#ifndef BLOCKANDUNCLEREWARDS_H
#define BLOCKANDUNCLEREWARDS_H

#include <QDebug>
#include <QJsonObject>

#include "./ether.h"
#include "./constants.h"
#include "./jsonobjectslist.h"
#include "./uncle.h"

namespace QtEtherscan {

/*! @class BlockAndUncleRewards src/types/blockandunclerewards.h
 *  @brief Object of this type is returned by method API::getBlockAndUncleRewards
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-block-and-uncle-rewards-by-blockno */

class BlockAndUncleRewards
{
public:
    BlockAndUncleRewards();
    BlockAndUncleRewards(const QJsonObject& jsonObject);
    BlockAndUncleRewards(const QJsonValue& jsonValue) :
        BlockAndUncleRewards(jsonValue.toObject()) {}

    /*! @brief Returns true if this BlockAndUncleRewards object is valid and contains reasonable information.
     *         BlockAndUncleRewards object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timestamp);  }
    QString   blockMiner() const            { return m_blockMiner; }
    Ether     blockReward() const           { return m_blockReward; }
    UncleList uncles() const                { return m_uncles; }
    Ether     uncleInclusionReward() const  { return m_uncleInclusionReward; }

private:
    qint32    m_blockNumber;
    qint64    m_timestamp;
    QString   m_blockMiner;
    Ether     m_blockReward;
    UncleList m_uncles;
    Ether     m_uncleInclusionReward;
};

inline QDebug operator<< (QDebug dbg, const BlockAndUncleRewards& blockAndUncleRewards)
{
    dbg.nospace() << qUtf8Printable(QString("BlockAndUncleRewards(blockNumber=%1; timeStamp=%2; blockMiner=%3; blockReward=%4; uncles.count()=%5; uncleInclusionReward=%6)")
                                    .arg(blockAndUncleRewards.blockNumber())
                                    .arg(blockAndUncleRewards.timeStamp().toString())
                                    .arg(blockAndUncleRewards.blockMiner())
                                    .arg(blockAndUncleRewards.blockReward().wei())
                                    .arg(blockAndUncleRewards.uncles().count())
                                    .arg(blockAndUncleRewards.uncleInclusionReward().weiString()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // BLOCKANDUNCLEREWARDS_H
