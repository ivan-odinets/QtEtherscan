/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_BLOCKANDUNCLEREWARDS_H
#define QT_ETHERSCAN_BLOCKANDUNCLEREWARDS_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_ether.h"
#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"
#include "./qethsc_uncle.h"

namespace QtEtherscan {

/*! @class BlockAndUncleRewards src/types/qethsc_blockandunclerewards.h
 *  @brief Object of this type is returned by API::getBlockAndUncleRewards method.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-block-and-uncle-rewards-by-blockno */

class BlockAndUncleRewards
{
public:
    /*! @brief Default constructor. Constructs invalid BlockAndUncleRewards object. */
    BlockAndUncleRewards();
    BlockAndUncleRewards(const QJsonObject& jsonObject);
    BlockAndUncleRewards(const QJsonValue& jsonValue) :
        BlockAndUncleRewards(jsonValue.toObject()) {}

    /*! @brief Returns true if this BlockAndUncleRewards object is valid and contains reasonable information.
     *         BlockAndUncleRewards object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns "blockNumber" field from etherscan.io response. */
    qint32    blockNumber() const           { return m_blockNumber; }

    /*! @brief Returns "timeStamp" field from etherscan.io response in form of QDateTime object. */
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }

    /*! @brief Returns "timeStamp" field from etherscan.io response in form of integer. */
    qint64    timeStampInteger() const      { return m_timeStamp; }

    /*! @brief Returns "blockMiner" field from etherscan.io response. */
    QString   blockMiner() const            { return m_blockMiner; }

    /*! @brief Returns "blockReward" field from etherscan.io response in form of Ether object. */
    Ether     blockReward() const           { return m_blockReward; }

    /*! @brief Returns "uncles" field from etherscan.io response in form of UncleList object. */
    UncleList uncles() const                { return m_uncles; }

    /*! @brief Returns "uncleInclusionReward" field from etherscan.io response in form of Ether object. */
    Ether     uncleInclusionReward() const  { return m_uncleInclusionReward; }

private:
    qint32    m_blockNumber;
    qint64    m_timeStamp;
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
                                    .arg(blockAndUncleRewards.blockReward().weiString())
                                    .arg(blockAndUncleRewards.uncles().count())
                                    .arg(blockAndUncleRewards.uncleInclusionReward().weiString()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_BLOCKANDUNCLEREWARDS_H
