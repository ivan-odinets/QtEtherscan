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

#ifndef QT_ETHERSCAN_DAILYGASLIMIT_H
#define QT_ETHERSCAN_DAILYGASLIMIT_H

#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"
#include "./qethsc_constants.h"

namespace QtEtherscan {

/*! @class DailyGasLimit src/types/qethsc_dailygaslimit.h
 *  @brief This object holds information about daily average gas limit. A list of such objects (DailyGasLimitList) is
 *         returned by API::getDailyAverageGasLimit methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-limit */

class DailyGasLimit
{
public:
    /*! @brief Default constructor. Constructs invalid DailyGasLimit object. */
    DailyGasLimit();
    DailyGasLimit(const QJsonObject& jsonObject);
    DailyGasLimit(const QJsonValue& jsonValue) :
        DailyGasLimit(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyGasLimit object is valid and contains reasonable information. DailyGasLimit
     *         object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool      isValid() const          { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-limit  */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "gasLimit" field from reply from etherscan.io. */
    qint64    gasLimit() const         { return m_gasLimit; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint64    m_gasLimit;
};

/*! @typedef DailyGasLimitList
 *  @brief This is a list of DailyGasLimit objects. It is returned by API::getDailyAverageGasLimit methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-daily-average-gas-limit */

typedef QtEtherscan::JsonObjectsList<DailyGasLimit> DailyGasLimitList;

inline QDebug operator<< (QDebug dbg, const DailyGasLimitList& dailyGasLimitList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyGasLimitList(count=%1)")
                   .arg(dailyGasLimitList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYGASLIMIT_H
