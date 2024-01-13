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

#ifndef ETHER_H
#define ETHER_H

#include <QJsonValue>
#include <QJsonObject>

namespace QtEtherscan {

/*! @class Ether src/types/ether.h
 *  @brief Object of this class represents specific amount of ETH. */

class Ether
{
public:
    Ether() {}
    Ether(const QString& weiString) :
        m_weiString(weiString) {}
    Ether(const QJsonValue& jsonValue) :
        Ether(jsonValue.toString()) {}

    bool      isValid() const     { return !m_weiString.isEmpty(); }

    /*! @brief This method returns this EtheriumBalance in Wei */
    double    wei() const         { return m_weiString.toDouble(); }

    /*! @brief This method can be used to get a string representation of EtheriumBalance in Wei */
    QString   weiString() const   { return m_weiString; }

    /*! @brief This method returns this EtheriumBalance in Eth */
    double    eth() const         { return m_weiString.toDouble() / 1000000000000000000.0; }

    /*! @brief This method returns this EtheriumBalance in Szabo */
    double    szabo() const       { return m_weiString.toDouble() / 1000000000000.0; }

private:
    QString   m_weiString;
};

inline QDebug operator<< (QDebug dbg, const Ether& ether)
{
    dbg.nospace() << qUtf8Printable(QString("Ether(eth=%1 ETH)")
                                    .arg(ether.eth()));

    return dbg.maybeSpace();
}

typedef Ether EtherBalance;

} //namespace QtEtherscan

#endif // ETHER_H
