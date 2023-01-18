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

#ifndef BLOCK_H
#define BLOCK_H

#include "./ether.h"
#include "./global.h"

namespace QtEtherscan {

class Block
{
public:
    Block();
    Block(const QJsonObject& jsonObject);
    Block(const QJsonValue& jsonValue) :
        Block(jsonValue.toObject()) {}

    bool      isValid() const     { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const { return m_blockNumber; }
    QDateTime timeStamp() const   { return m_timeStamp; }
    Ether     blockReward() const { return m_blockReward; }

private:
    qint32    m_blockNumber;
    QDateTime m_timeStamp;
    Ether     m_blockReward;
};

inline QDebug operator<< (QDebug dbg, const Block& block)
{
    dbg.nospace() << qUtf8Printable(QString("Block(blockNumber=%1; timeStamp=%2)")
                                    .arg(block.blockNumber())
                                    .arg(block.timeStamp().toString()));

    return dbg.maybeSpace();
}

typedef JsonObjectsList<Block> BlockList;

inline QDebug operator<<(QDebug dbg, const BlockList& blockList)
{
    dbg.nospace() << qUtf8Printable(QString("BlockList(blockList.count()=%1)")
                                    .arg(blockList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // BLOCK_H
