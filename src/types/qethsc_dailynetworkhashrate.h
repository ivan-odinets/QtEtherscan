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

#ifndef QT_ETHERSCAN_DAILYNETWORKHASHRATE_H
#define QT_ETHERSCAN_DAILYNETWORKHASHRATE_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyNetworkHashrate src/types/qethsc_dailynetworkhashrate.h
 *  @brief This object holds information about daily hash rate. A list of such objects (DailyNetworkHashrateList)
 *         is returned by API::getDailyNetworkHashrate methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-hash-rate */

class DailyNetworkHashrate
{
public:
    /*! @brief Default constructor. Constructs invalid DailyNetworkHashrate object. */
    DailyNetworkHashrate();
    DailyNetworkHashrate(const QJsonObject& jsonObject);
    DailyNetworkHashrate(const QJsonValue& jsonValue) :
        DailyNetworkHashrate(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyNetworkHashrate object is valid and contains reasonable information.
     *         DailyNetworkHashrate object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const                    { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-hash-rate  */
    QString utcDate() const                 { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const                { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const         { return m_timeStamp; }

    /*! @brief Returns "networkHashRate" field from reply from etherscan.io in form of double. */
    double networkHashRate() const          { return m_networkHashRate; }

    /*! @brief Returns "networkHashRate" field from reply from etherscan.io */
    QString networkHashRateString() const   { return QString::number(m_networkHashRate); }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    double    m_networkHashRate;
};

inline QDebug operator<< (QDebug dbg, const DailyNetworkHashrate& dailyNetworkHashrate)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkHashrate(utcDate=%1; networkHashRate=%2)")
                                    .arg(dailyNetworkHashrate.utcDate())
                                    .arg(dailyNetworkHashrate.networkHashRate()));

    return dbg.maybeSpace();
}

/*! @typedef DailyNetworkHashrateList
 *  @brief This is a list of DailyNetworkHashrate objects. It is returned by API::getDailyNetworkHashrate methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-hash-rate */

typedef QtEtherscan::JsonObjectsList<DailyNetworkHashrate> DailyNetworkHashrateList;

inline QDebug operator<< (QDebug dbg, const DailyNetworkHashrateList& dailyNetworkHashrateList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkHashrateList(count=%1)")
                   .arg(dailyNetworkHashrateList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYNETWORKHASHRATE_H
