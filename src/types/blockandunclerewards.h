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

#ifndef BLOCKANDUNCLEREWARDS_H
#define BLOCKANDUNCLEREWARDS_H

#include "./ether.h"
#include "./uncle.h"

namespace QtEtherscan {

class BlockAndUncleRewards
{
public:
    BlockAndUncleRewards();
    BlockAndUncleRewards(const QJsonObject& jsonObject);
    BlockAndUncleRewards(const QJsonValue& jsonValue) :
        BlockAndUncleRewards(jsonValue.toObject()) {}

    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return m_timestamp;  }
    QString   blockMiner() const            { return m_blockMiner; }
    Ether     blockReward() const           { return m_blockReward; }
    UncleList uncles() const                { return m_uncles; }
    Ether     uncleInclusionReward() const  { return m_uncleInclusionReward; }

private:
    qint32    m_blockNumber;
    QDateTime m_timestamp;
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
                                    .arg(blockAndUncleRewards.uncleInclusionReward().wei()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // BLOCKANDUNCLEREWARDS_H
