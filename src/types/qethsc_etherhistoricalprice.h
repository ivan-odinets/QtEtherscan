/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_ETHERHISTORICALPRICE_H
#define QT_ETHERSCAN_ETHERHISTORICALPRICE_H

#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"
#include "./qethsc_constants.h"

namespace QtEtherscan {

/*! @class EtherHistoricalPrice src/types/qethsc_etherhistoricalpric.h
 *  @brief This object holds information about ETH historical price. A list of such objects is returned by
 *         API::getEtherHistoricalPrice methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-price */

class EtherHistoricalPrice
{
public:
    /*! @brief Default constructor. Constructs invalid EtherHistoricalPrice object. */
    EtherHistoricalPrice();
    EtherHistoricalPrice(const QJsonObject& jsonObject);
    EtherHistoricalPrice(const QJsonValue& jsonValue) :
        EtherHistoricalPrice(jsonValue.toObject()) {}

    /*! @brief Returns true if this EtherHistoricalPrice object is valid and contains reasonable information.
     *         EtherHistoricalPrice object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool      isValid() const          { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-price */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "value" field from reply from etherscan.io. */
    double    value() const            { return m_historicalPrice; }

private:
    QString m_utcDate;
    qint64  m_timeStamp;
    double  m_historicalPrice;
};

inline QDebug operator<< (QDebug dbg, const EtherHistoricalPrice& etherHistoricalPrice)
{
    dbg.nospace() << qUtf8Printable(QString("EtherHistoricalPrice(utcDate=%1; value=%2)")
                                    .arg(etherHistoricalPrice.utcDate())
                                    .arg(etherHistoricalPrice.value()));

    return dbg.maybeSpace();
}

/*! @typedef EtherHistoricalPriceList
 *  @brief This is a list of EtherHistoricalPrice objects. It is returned by API::getEtherHistoricalPrice methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-price */

typedef QtEtherscan::JsonObjectsList<EtherHistoricalPrice> EtherHistoricalPriceList;

inline QDebug operator<< (QDebug dbg, const EtherHistoricalPriceList& etherHistoricalPriceList)
{
    dbg.nospace() << qUtf8Printable(QString("EtherHistoricalPriceList(count=%1)")
                   .arg(etherHistoricalPriceList.count()));

    return dbg.maybeSpace();
}


} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ETHERHISTORICALPRICE_H
