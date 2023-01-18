/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2023 Ivan Odinets
 *
 * This file is part of QtEtherscan
 *
 * QtTelegramBot is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QtTelegramBot  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QtTelegramBot; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef ETHERPRICE_H
#define ETHERPRICE_H

#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

class EtherPrice
{
public:
    static double constexpr InvalidPrice = -1;

    EtherPrice();
    EtherPrice(const QJsonObject& jsonObject);
    EtherPrice(const QJsonValue& jsonValue) :
        EtherPrice(jsonValue.toObject()) {}

    bool      isValid() const          { return ( (m_ethBtc != InvalidPrice) && (m_ethUsd != InvalidPrice) ); }

    double    ethBtc() const           { return m_ethBtc; }
    QDateTime ethBtcTimeStamp() const  { return m_ethBtcTimeStamp; }
    double    ethUsd() const           { return m_ethUsd; }
    QDateTime ethUsdTimeStamp() const  { return m_ethUsdTimeStamp; }

private:
    double    m_ethBtc;
    QDateTime m_ethBtcTimeStamp;
    double    m_ethUsd;
    QDateTime m_ethUsdTimeStamp;
};

inline QDebug operator<< (QDebug dbg, const EtherPrice& etherPrice)
{
    dbg.nospace() << qUtf8Printable(QString("EtherPrice(ethBtc=%1; ethUsd=%2)")
                                    .arg(etherPrice.ethBtc())
                                    .arg(etherPrice.ethUsd()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ETHERPRICE_H
