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

#ifndef QT_ETHERSCAN_BLOCK_H
#define QT_ETHERSCAN_BLOCK_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_ether.h"
#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class Block src/types/qethsc_block.h
 *  @brief A list of such objects is returned by API::getListOfBlocksMinedByAddress (deprecated, will be removed) and
 *         API::getListOfBlocksValidatedByAddress methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-list-of-blocks-validated-by-address */

class Block
{
public:
    /*! @brief Default constructor. Constructs invalid Block object. */
    Block();
    Block(const QJsonObject& jsonObject);
    Block(const QJsonValue& jsonValue) :
        Block(jsonValue.toObject()) {}

    /*! @brief Returns true if this Block object is valid and contains reasonable information. Block object is considered
     *         to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns "blockNumber" field from etherscan.io response. */
    qint32    blockNumber() const      { return m_blockNumber; }

    /*! @brief Returns "timeStamp" field from etherscan.io response in form of QDateTime object. */
    QDateTime timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }

    /*! @brief Returns "timeStamp" field from etherscan.io response in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "blockReward" field from etherscan.io response in form of Ether object. */
    Ether     blockReward() const      { return m_blockReward; }

private:
    qint32    m_blockNumber;
    qint64    m_timeStamp;
    Ether     m_blockReward;
};

inline QDebug operator<< (QDebug dbg, const Block& block)
{
    dbg.nospace() << qUtf8Printable(QString("Block(blockNumber=%1; timeStamp=%2)")
                                    .arg(block.blockNumber())
                                    .arg(block.timeStamp().toString()));

    return dbg.maybeSpace();
}

/*! @typedef BlockList
 *  @brief This is a list of Block objects. It is returned by API::getListOfBlocksMinedByAddress (deprecated, will be
 *         removed) and API::getListOfBlocksValidatedByAddress methods. Nothing more than a QList with some extra constructors
 *         (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-list-of-blocks-validated-by-address */

typedef JsonObjectsList<Block> BlockList;

inline QDebug operator<<(QDebug dbg, const BlockList& blockList)
{
    dbg.nospace() << qUtf8Printable(QString("BlockList(count=%1)")
                                    .arg(blockList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_BLOCK_H
