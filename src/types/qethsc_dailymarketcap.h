/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_DAILYMARKETCAP_H
#define QT_ETHERSCAN_DAILYMARKETCAP_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_ether.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyMarketCap src/types/qethsc_dailymarketcap.h
 *  @brief This object holds information about daily average market capitalization. A list of such objects (DailyMarketCap) is
 *         returned by API::getHistoricalEtherMarketCapitalization methods .
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-daily-market-cap */

class DailyMarketCap
{
public:
    /*! @brief Default constructor. Constructs invalid DailyMarketCap object. */
    DailyMarketCap();
    DailyMarketCap(const QJsonObject& jsonObject);
    DailyMarketCap(const QJsonValue& jsonValue) :
        DailyMarketCap(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyGasPrice object is valid and contains reasonable information. DailyGasPrice
     *         object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-daily-market-cap  */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "supply" field from reply from etherscan.io in form of Ether object. */
    Ether supply() const               { return m_supply; }

    /*! @brief Returns "marketCap" field from reply from etherscan.io in form of double. **NOTE** The marketCap is
     *         represented in million US Dollars (USD). */
    double marketCap() const           { return m_marketCap; }

    /*! @brief Returns "price" field from reply from etherscan.io in form of double. */
    double price() const               { return m_price; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    Ether     m_supply;
    double    m_marketCap;
    double    m_price;
};

/*! @typedef DailyMarketCapList
 *  @brief This is a list of DailyMarketCap objects. It is returned by API::getHistoricalEtherMarcatCapitalization methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-ether-historical-daily-market-cap */

typedef QtEtherscan::JsonObjectsList<DailyMarketCap> DailyMarketCapList;

inline QDebug operator<< (QDebug dbg, const DailyMarketCapList& dailyMarketcapList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyMarketCapList(count=%1)")
                   .arg(dailyMarketcapList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYMARKETCAP_H
