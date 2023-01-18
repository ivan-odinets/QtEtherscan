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

#ifndef NODESCOUNT_H
#define NODESCOUNT_H

#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

class NodesCount
{
public:
    static quint32 constexpr InvalidCount = 0;

    NodesCount();
    NodesCount(const QJsonObject& jsonObject);
    NodesCount(const QJsonValue& jsonValue) :
        NodesCount(jsonValue.toObject()) {}

    bool      isValid() const          { return m_totalNodeCount != InvalidCount; }

    QDate     utcDate() const          { return m_utcDate; }
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

#endif // NODESCOUNT_H
