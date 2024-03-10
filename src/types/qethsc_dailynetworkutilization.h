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

#ifndef QT_ETHERSCAN_DAILYNETWORKUTILIZATION_H
#define QT_ETHERSCAN_DAILYNETWORKUTILIZATION_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyNetworkUtilization src/types/qethsc_dailynetworkutilization.h
 *  @brief This object holds information about daily networkutilization. A list of such objects (DailyNetworkUtilizationList)
 *         is returned by API::getDailyNetworkUtilization methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-utilization */

class DailyNetworkUtilization
{
public:
    /*! @brief Default constructor. Constructs invalid DailyNetworkUtilization object. */
    DailyNetworkUtilization();
    DailyNetworkUtilization(const QJsonObject& jsonObject);
    DailyNetworkUtilization(const QJsonValue& jsonValue) :
        DailyNetworkUtilization(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyNetworkUtilization object is valid and contains reasonable information.
     *         DailyNetworkUtilization object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-utilization */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "networkUtilization" field from reply from etherscan.io in form of double. */
    double value() const               { return m_networkUtilization; }

    /*! @brief Returns "networkUtilization" field from reply from etherscan.io. */
    QString valueString() const        { return QString::number(m_networkUtilization); }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    double    m_networkUtilization;
};

inline QDebug operator<< (QDebug dbg, const DailyNetworkUtilization& dailyNetworkUtilization)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkUtilization(utcDate=%1; value=%2)")
                                    .arg(dailyNetworkUtilization.utcDate())
                                    .arg(dailyNetworkUtilization.value()));

    return dbg.maybeSpace();
}

/*! @typedef DailyNetworkUtilizationList
 *  @brief This is a list of DailyNetworkUtilization objects. It is returned by API::getDailyNetworkUtilization methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-utilization */

typedef QtEtherscan::JsonObjectsList<DailyNetworkUtilization> DailyNetworkUtilizationList;

inline QDebug operator<< (QDebug dbg, const DailyNetworkUtilizationList& dailyNetworkUtilizationList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkUtilizationList(count=%1)")
                   .arg(dailyNetworkUtilizationList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYNETWORKUTILIZATION_H
