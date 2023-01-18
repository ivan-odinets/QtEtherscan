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

#ifndef UNCLE_H
#define UNCLE_H

#include "./ether.h"
#include "./global.h"

namespace QtEtherscan {

class Uncle
{
public:
    Uncle() {}
    Uncle(const QJsonObject& jsonObject);
    Uncle(const QJsonValue& jsonValue) :
        Uncle(jsonValue.toObject()) {}

    bool      isValid() const          { return m_miner.isEmpty(); }

    QString   miner() const            { return m_miner; }
    int       unclePosition() const    { return m_unclePosition; }
    Ether     blockReward() const      { return m_blockReward; }

private:
    QString   m_miner;
    int       m_unclePosition;
    Ether     m_blockReward;
};

inline QDebug operator<< (QDebug dbg, const Uncle& uncle)
{
    dbg.nospace() << qUtf8Printable(QString("Uncle(miner=%1; unclePosition=%2; blockReward=%3 ETH)")
                                    .arg(uncle.miner())
                                    .arg(uncle.unclePosition())
                                    .arg(uncle.blockReward().eth()));

    return dbg.maybeSpace();
}

typedef JsonObjectsList<Uncle> UncleList;

inline QDebug operator<< (QDebug dbg, const UncleList& uncleList)
{
    dbg.nospace() << qUtf8Printable(QString("UncleList(count=%1)")
                                    .arg(uncleList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // UNCLE_H
