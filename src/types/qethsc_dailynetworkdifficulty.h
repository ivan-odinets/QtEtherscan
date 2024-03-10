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

#ifndef QT_ETHERSCAN_DAILYNETWORKDIFFICULTY_H
#define QT_ETHERSCAN_DAILYNETWORKDIFFICULTY_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyNetworkDifficulty src/types/qethsc_dailynetworkdifficulty.h
 *  @brief This object holds information about daily network difficulty. A list of such objects (DailyNetworkDifficultyList)
 *         is returned by API::getDailyNetworkDifficulty methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-difficulty */

class DailyNetworkDifficulty
{
public:
    /*! @brief Default contructor. Constructs invalid DailyNetworkDifficulty object. */
    DailyNetworkDifficulty();
    DailyNetworkDifficulty(const QJsonObject& jsonObject);
    DailyNetworkDifficulty(const QJsonValue& jsonValue) :
        DailyNetworkDifficulty(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyNetworkDifficulty object is valid and contains reasonable information.
     *         DailyNetworkDifficulty object is considered to be valid if timeStampInteger() contains enything but not -1. */
    bool isValid() const                    { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-difficulty  */
    QString utcDate() const                 { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const                { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const         { return m_timeStamp; }

    /*! @brief Returns "networkDifficulty" field from reply from etherscan.io in form of double. */
    double networkDifficulty() const        { return m_networkDifficulty; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    double    m_networkDifficulty;
};

inline QDebug operator<< (QDebug dbg, const DailyNetworkDifficulty& dailyNetworkDifficulty)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkDifficulty(utcDate=%1; networkDifficulty=%2)")
                                    .arg(dailyNetworkDifficulty.utcDate())
                                    .arg(dailyNetworkDifficulty.networkDifficulty()));

    return dbg.maybeSpace();
}

/*! @typedef DailyNetworkDifficultyList
 *  @brief This is a list of DailyNetworkDifficulty objects. It is returned by API::getDailyNetworkDifficulty methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-average-network-difficulty  */

typedef QtEtherscan::JsonObjectsList<DailyNetworkDifficulty> DailyNetworkDifficultyList;

inline QDebug operator<< (QDebug dbg, const DailyNetworkDifficultyList& dailyNetworkDifficultyList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNetworkDifficultyList(count=%1)")
                   .arg(dailyNetworkDifficultyList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYNETWORKDIFFICULTY_H
