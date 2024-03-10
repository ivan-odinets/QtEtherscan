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

#ifndef QT_ETHERSCAN_NODESCOUNT_H
#define QT_ETHERSCAN_NODESCOUNT_H

#include <QJsonObject>
#include <QJsonValue>

#include "./qethsc_constants.h"

namespace QtEtherscan {

/*! @class NodesCount src/types/qethsc_nodescount.h
 *  @brief Object of this class is returned by API::getTotalNodesCount.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-total-nodes-count */

class NodesCount
{
public:
    /*! @brief Default constructor. Constructs invalid NodesCount object. */
    NodesCount();
    NodesCount(const QJsonObject& jsonObject);
    NodesCount(const QJsonValue& jsonValue) :
        NodesCount(jsonValue.toObject()) {}

    /*! @brief Returns true if this NodesCount object is valid and contains reasonable information. NodesCount object
     *         is considered to be valid if totalNodeCount() contains anything but not 0. */
    bool      isValid() const          { return m_totalNodeCount != InvalidNodeCount; }

    /*! @brief Returns "UTCDate" field from etherscan. io reply in form of QDate. */
    QDate     utcDate() const          { return m_utcDate; }

    /*! @brief Returns "TotalNodeCount" field from etherscan.io reply. */
    quint32   totalNodeCount() const   { return m_totalNodeCount; }

private:
    quint32   m_totalNodeCount;
    QDate     m_utcDate;
};

inline QDebug operator<< (QDebug dbg, const NodesCount& nodesCount)
{
    dbg.nospace() << qUtf8Printable(QString("NodesCount(utcDate=%1; totalNodeCount=%2)")
                                    .arg(nodesCount.utcDate().toString())
                                    .arg(nodesCount.totalNodeCount()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_NODESCOUNT_H
