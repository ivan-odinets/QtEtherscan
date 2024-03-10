/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2023-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_ETHERPRICE_H
#define QT_ETHERSCAN_ETHERPRICE_H

#include <QJsonObject>
#include <QJsonValue>

#include "./qethsc_constants.h"

namespace QtEtherscan {

/*! @class EtherPrice src/types/qethsc_etherprice.h
 *  @brief Object of this type is returned by API::getEtherLastPrice method.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-last-price */

class EtherPrice
{
public:
    /*! @brief Default constructor. Constructs invalid EtherPrice object. */
    EtherPrice();
    EtherPrice(const QJsonObject& jsonObject);
    EtherPrice(const QJsonValue& jsonValue) :
        EtherPrice(jsonValue.toObject()) {}

    /*! @brief Returns true if this EtherPrice object is valid and contains reasonable information. EtherPrice object is
     *         considered to be valid if ethBtc() and ethUsd() are containing anything but not -1. */
    bool      isValid() const          { return ( (m_ethBtc != InvalidPrice) && (m_ethUsd != InvalidPrice) ); }

    /*! @brief Returns "ethbtc" field from reply from etherscan.io in form of double. */
    double    ethBtc() const           { return m_ethBtc; }

    /*! @brief Returns "ethbtc_timestamp" field from reply from etherscan.io in form of QDateTime object. */
    QDateTime ethBtcTimeStamp() const  { return QDateTime::fromSecsSinceEpoch(m_ethBtcTimeStamp); }

    /*! @brief Returns "ethusd" field from reply from etherscan.io in form of double. */
    double    ethUsd() const           { return m_ethUsd; }

    /*! @brief Returns "ethusd_timestamp" field from reply from etherscan.io in form of QDateTime object. */
    QDateTime ethUsdTimeStamp() const  { return QDateTime::fromSecsSinceEpoch(m_ethUsdTimeStamp); }

private:
    double    m_ethBtc;
    qint64    m_ethBtcTimeStamp;
    double    m_ethUsd;
    qint64    m_ethUsdTimeStamp;
};

inline QDebug operator<< (QDebug dbg, const EtherPrice& etherPrice)
{
    dbg.nospace() << qUtf8Printable(QString("EtherPrice(ethBtc=%1; ethUsd=%2)")
                                    .arg(etherPrice.ethBtc())
                                    .arg(etherPrice.ethUsd()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_ETHERPRICE_H
