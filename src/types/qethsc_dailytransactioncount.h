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

#ifndef QT_ETHERSCAN_DAILYTRANSACTIONCOUNT_H
#define QT_ETHERSCAN_DAILYTRANSACTIONCOUNT_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyTransactionCount src/types/qethsc_dailytransactioncount.h
 *  @brief This object holds information about daily transaction count. A list of such objects (DailyTransactionCountList)
 *         is returned by API::getDailyTransactionCount methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-transaction-count */

class DailyTransactionCount
{
public:
    /*! @brief Default constructor. Constructs invalid DailyTransactionCount object. */
    DailyTransactionCount();
    DailyTransactionCount(const QJsonObject& jsonObject);
    DailyTransactionCount(const QJsonValue& jsonValue) :
        DailyTransactionCount(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyTransactionCount object is valid and contains reasonable information.
     *         DailyTransactionCount object is considered to be valid if timeStampInteger() contains enything but not -1. */
    bool isValid() const                    { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-transaction-count  */
    QString utcDate() const                 { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const                { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const         { return m_timeStamp; }

    /*! @brief Returns "transactionCount" field from reply from etherscan.io in form of integer. */
    qint64 transactionCount() const         { return m_transactionCount; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint64    m_transactionCount;
};

inline QDebug operator<< (QDebug dbg, const DailyTransactionCount& dailyTransactionCount)
{
    dbg.nospace() << qUtf8Printable(QString("DailyTransactionCount(utcDate=%1; transactionCount=%2)")
                                    .arg(dailyTransactionCount.utcDate())
                                    .arg(dailyTransactionCount.transactionCount()));

    return dbg.maybeSpace();
}

/*! @typedef DailyTransactionCountList
 *  @brief This is a list of DailyTransactionCount objects. It is returned by API::getDailyTransactionCount methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-transaction-count */

typedef QtEtherscan::JsonObjectsList<DailyTransactionCount> DailyTransactionCountList;

inline QDebug operator<< (QDebug dbg, const DailyTransactionCountList& dailyTransactionCount)
{
    dbg.nospace() << qUtf8Printable(QString("DailyTransactionCountList(count=%1)")
                   .arg(dailyTransactionCount.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYTRANSACTIONCOUNT_H
