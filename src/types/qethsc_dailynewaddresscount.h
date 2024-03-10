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

#ifndef QT_ETHERSCAN_DAILYNEWADDRESSCOUNT_H
#define QT_ETHERSCAN_DAILYNEWADDRESSCOUNT_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyNewAddressCount src/types/qethsc_dailynewaddresscount.h
 *  @brief This object holds information about daily new address count. A list of such objects (DailyAddressCountList) is
 *         returned by API::getDailyNewAddressCount methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-new-address-count */

class DailyNewAddressCount
{
public:
    /*! @brief Default constructor. Constructs invalid DailyNewAddressCount object. */
    DailyNewAddressCount();
    DailyNewAddressCount(const QJsonObject& jsonObject);
    DailyNewAddressCount(const QJsonValue& jsonValue) :
        DailyNewAddressCount(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyNewAddressCount object is valid and contains reasonable information.
     *         DailyNetworkHashrate object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-new-address-count */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "newAddressCount" field from reply from etherscan.io in form of integer" */
    qint32 count() const               { return m_count; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint32    m_count;
};

inline QDebug operator<< (QDebug dbg, const DailyNewAddressCount& dailyNewAddressCount)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNewAddressCount(utcDate=%1; count=%2)")
                                    .arg(dailyNewAddressCount.utcDate())
                                    .arg(dailyNewAddressCount.count()));

    return dbg.maybeSpace();
}

/*! @typedef DailyNewAddressCountList
 *  @brief This is a list of DailyNewAddressCount objects. It is returned by API::getDailyNewAddressCount methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-new-address-count */

typedef QtEtherscan::JsonObjectsList<DailyNewAddressCount> DailyNewAddressCountList;

inline QDebug operator<< (QDebug dbg, const DailyNewAddressCountList& dailyNewAddressCountList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyNewAddressCountList(count=%1)")
                   .arg(dailyNewAddressCountList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QETHSC_DAILYNEWADDRESSCOUNT_H
