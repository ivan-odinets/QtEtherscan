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

#include "./nodescount.h"

namespace QtEtherscan {

NodesCount::NodesCount() :
    m_totalNodeCount(InvalidCount)
{}

NodesCount::NodesCount(const QJsonObject& jsonObject) :
    m_totalNodeCount(jsonObject.value("TotalNodeCount").toString(QLatin1String("0")).toULong()),
    m_utcDate(QDate::fromString(jsonObject.value("UTCDate").toString(),Qt::ISODate))
{}

} // namespace QtEtherscan
