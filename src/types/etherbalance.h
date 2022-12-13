/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2021-2022 IvanOdinets
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

#ifndef ETHERBALANCE_H
#define ETHERBALANCE_H

#include <QJsonValue>

class EtherBalance
{
public:
    EtherBalance() {}
    EtherBalance(const QString& weiString) :
        m_weiString(weiString) {}
    EtherBalance(const QJsonValue& jsonValue) :
        EtherBalance(jsonValue.toString()) {}

    /*! @brief This method returns this EtheriumBalance in Wei */
    double wei() const   { return m_weiString.toDouble(); }

    /*! @brief This method returns this EtheriumBalance in Eth */
    double eth() const   { return m_weiString.toDouble() / 1000000000000000000.0; }

    /*! @brief This method returns this EtheriumBalance in Szabo */
    double szabo() const { return m_weiString.toDouble() / 1000000000000.0; }

private:
    QString m_weiString;
};

inline QDebug operator<< (QDebug dbg, const EtherBalance& etherBalance)
{
    dbg.nospace() << qUtf8Printable(QString("EtherBalance(eth=%1 ETH)")
                                    .arg(etherBalance.eth()));

    return dbg.maybeSpace();
}

#endif // ETHERBALANCE_H
