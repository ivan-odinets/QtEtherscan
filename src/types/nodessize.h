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

#ifndef NODESSIZE_H
#define NODESSIZE_H

#include "./global.h"

namespace QtEtherscan {

class ChainSize
{
public:
    ChainSize();
    ChainSize(const QJsonObject& jsonObject);
    ChainSize(const QJsonValue& jsonValue) :
        ChainSize(jsonValue.toObject()) {}

    bool           isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    qint32         blockNumber() const      { return m_blockNumber; }
    QDate          chainTimeStamp() const   { return m_timeStamp; };
    quint64        chainSize() const        { return m_chainSize; }
    ClientType     clientType() const       { return m_clientType; }
    Syncmode       syncMode() const         { return m_syncMode; }

private:
    qint32         m_blockNumber;
    QDate          m_timeStamp;
    quint64        m_chainSize;
    ClientType     m_clientType;
    Syncmode       m_syncMode;
};

inline QDebug operator<< (QDebug dbg, const ChainSize& chainSize)
{
    dbg.nospace() << qUtf8Printable(QString("ChainSize(blockNumber=%1; chainTimeStamp=%2; chainSize=%3)")
                                    .arg(chainSize.blockNumber())
                                    .arg(chainSize.chainTimeStamp().toString())
                                    .arg(chainSize.chainSize()));

    return dbg.maybeSpace();
}

typedef JsonObjectsList<ChainSize> NodesSize;

inline QDebug operator<< (QDebug dbg, const NodesSize& nodesSize)
{
    dbg.nospace() << qUtf8Printable(QString("NodesSize(count=%1)")
                                    .arg(nodesSize.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // NODESSIZE_H
