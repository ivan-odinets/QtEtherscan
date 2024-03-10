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

#ifndef QT_ETHERSCAN_NODESSIZE_H
#define QT_ETHERSCAN_NODESSIZE_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_constants.h"
#include "./qethsc_enums.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ChainSize src/types/qethsc_nodessize.h
 *  @brief A list of such objects is returned by API::getEtheriumNodesSize method.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ethereum-nodes-size */

class ChainSize
{
public:
    /*! @brief Default constructor. Constructs invalid ChainSize object. */
    ChainSize();
    ChainSize(const QJsonObject& jsonObject);
    ChainSize(const QJsonValue& jsonValue) :
        ChainSize(jsonValue.toObject()) {}

    /*! @brief Returns true if this ChainSize object is valid and contains reasonable information. ChainSize object is
     *         considered to be valid if blockNumber() contains anything but not -1. */
    bool           isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns "blockNumber" field from etherscan.io response. */
    qint32         blockNumber() const      { return m_blockNumber; }

    /*! @brief Returns "chainTimeStamp" field from etherscan.io response in form of QDate object. */
    QDate          chainTimeStamp() const   { return m_timeStamp; }

    /*! @brief Returns "chainSize" field from etherscan.io response. */
    quint64        chainSize() const        { return m_chainSize; }

    /*! @brief Returns "clientType" field from etherscan.io response in form of ClientType enum. */
    ClientType     clientType() const       { return m_clientType; }

    /*! @brief Returns "syncMode" field from etherscan.io response in form of Syncmode enum. */
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
                                    .arg(chainSize.chainTimeStamp().toString(Qt::ISODate))
                                    .arg(chainSize.chainSize()));

    return dbg.maybeSpace();
}

/*! @typedef NodesSize
 *  @brief This is a list of ChainSize objects. It is returned by API::getEtheriumNodesSize method. Nothing more than a
 *         QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ethereum-nodes-size */

typedef JsonObjectsList<ChainSize> NodesSize;

inline QDebug operator<< (QDebug dbg, const NodesSize& nodesSize)
{
    dbg.nospace() << qUtf8Printable(QString("NodesSize(count=%1)")
                                    .arg(nodesSize.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_NODESSIZE_H
