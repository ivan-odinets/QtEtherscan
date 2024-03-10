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

#ifndef QT_ETHERSCAN_DAILYBLOCKTIME_H
#define QT_ETHERSCAN_DAILYBLOCKTIME_H

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyBlockTime src/types/qethsc_dailyblocktime.h
 *  @brief This object holds information about daily average time for a block to be included in the blockchain. A list
 *         of such objects (DailyBlockTimeList) is returned by API::getDailyAverageTimeForBlock methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-time-for-a-block-to-be-included-in-the-ethereum-blockchain */

class DailyBlockTime
{
public:
    /*! @brief Default constructor. Constructs invalid DailyBlockTime object. */
    DailyBlockTime();
    DailyBlockTime(const QJsonObject& jsonObject);
    DailyBlockTime(const QJsonValue& jsonValue) :
        DailyBlockTime(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyBlockTime object is valid and contains reasonable information. DailyBlockTime
     *         object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool      isValid() const          { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-time-for-a-block-to-be-included-in-the-ethereum-blockchain */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "blockTime_sec" field from reply from etherscan.io. */
    double    blockTime() const        { return m_blockTime; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    double    m_blockTime;
};

inline QDebug operator<< (QDebug dbg, const DailyBlockTime& dailyBlokcTime)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockTime(utcDate=%1; blockTime=%2)")
                                    .arg(dailyBlokcTime.utcDate())
                                    .arg(dailyBlokcTime.blockTime()));

    return dbg.maybeSpace();
}

/*! @typedef DailyBlockTimeList
 *  @brief This is a list of DailyBlockTime objects. It is returned by API::getDailyAverageTimeForBlock methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-time-for-a-block-to-be-included-in-the-ethereum-blockchain */

typedef JsonObjectsList<DailyBlockTime> DailyBlockTimeList;

inline QDebug operator<< (QDebug dbg, const DailyBlockTimeList& dailyBlockTimeList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockTimeList(count=%1)")
                   .arg(dailyBlockTimeList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYBLOCKTIME_H
