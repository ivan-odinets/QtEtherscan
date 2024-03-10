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

#ifndef QT_ETHERSCAN_DAILYGASPRICE_H
#define QT_ETHERSCAN_DAILYGASPRICE_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyGasPrice src/types/qethsc_dailygasprice.h
 *  @brief This object holds information about daily average gas price. A list of such objects (DailyGasPriceList) is
 *         returned by API::getDailyAverageGasPrice methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-price */

class DailyGasPrice
{
public:
    /*! @brief Default constructor. Constructs invalid DailyGasPrice object. */
    DailyGasPrice();
    DailyGasPrice(const QJsonObject& jsonObject);
    DailyGasPrice(const QJsonValue& jsonValue) :
        DailyGasPrice(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyGasPrice object is valid and contains reasonable information. DailyGasPrice
     *         object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-price  */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "maxGasPrice_Wei" field from reply from etherscan.io */
    qint64 maxGasPrice() const         { return m_maxGasPriceWei; }

    /*! @brief Returns "minGasPrice_Wei" field from reply from etherscan.io */
    qint64 minGasPrice() const         { return m_minGasPriceWei; }

    /*! @brief Returns "avgGasPrice_Wei" field from reply from etherscan.io */
    qint64 avgGasPrice() const         { return m_avgGasPriceWei; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint64    m_maxGasPriceWei;
    qint64    m_minGasPriceWei;
    qint64    m_avgGasPriceWei;
};

/*! @typedef DailyGasPriceList
 *  @brief This is a list of DailyGasPricetList objects. It is returned by API::getDailyAverageGasPrice methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-price */

typedef QtEtherscan::JsonObjectsList<DailyGasPrice> DailyGasPriceList;

inline QDebug operator<< (QDebug dbg, const DailyGasPriceList& dailyGasPrice)
{
    dbg.nospace() << qUtf8Printable(QString("DailyGasPriceList(count=%1)")
                   .arg(dailyGasPrice.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYGASPRICE_H
