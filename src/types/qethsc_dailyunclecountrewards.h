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

#ifndef QT_ETHERSCAN_DAILYUNCLECOUNTREWARDS_H
#define QT_ETHERSCAN_DAILYUNCLECOUNTREWARDS_H

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

#include "./qethsc_ether.h"
#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyUncleCountRewards src/types/qethsc_dailyunclecountrewards.h
 *  @brief This object holds information about daily average uncle block rewards. A list of such objects (DailyUncleCountRewardsList) is
 *         returned by API::getDailyUncleCountRewards methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-uncle-block-count-and-rewards */

class DailyUncleCountRewards
{
public:
    /*! @brief Default constructor. Constructs invalid DailyUncleCountRewards object. */
    DailyUncleCountRewards();
    DailyUncleCountRewards(const QJsonObject& jsonObject);
    DailyUncleCountRewards(const QJsonValue& jsonValue) :
        DailyUncleCountRewards(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyUncleCountRewards object is valid and contains reasonable information. DailyUncleCountRewards
     *         object is considered to be valid if uncleBlockCount() contains enything but not -1. */
    bool      isValid() const               { return m_uncleBlockCount != InvalidBlockCount; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-uncle-block-count-and-rewards */
    QString   utcDate() const               { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer */
    qint64    timeStampInteger() const      { return m_timeStamp; }

    /*! @brief Returns "blockRewards_Eth" field from reply from etherscan.io in form of Ether object. */
    Ether     uncleBlockRewards() const     { return m_uncleBlockRewards; }

    /*! @brief Returns "blockCount" field from reply from etherscan.io */
    qint32    uncleBlockCount() const       { return m_uncleBlockCount; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint32    m_uncleBlockCount;
    Ether     m_uncleBlockRewards;
};

inline QDebug operator<< (QDebug dbg, const DailyUncleCountRewards& dailyUncleCountRewards)
{
    dbg.nospace() << qUtf8Printable(QString("DailyUncleCountRewards(utcDate=%1; uncleBlockRewards.eth()=%2 ETH; uncleBlockCount=%3)")
                                    .arg(dailyUncleCountRewards.utcDate())
                                    .arg(dailyUncleCountRewards.uncleBlockRewards().eth())
                                    .arg(dailyUncleCountRewards.uncleBlockCount()));

    return dbg.maybeSpace();
}

/*! @typedef DailyUncleCountRewardsList
 *  @brief This is a list of DailyUncleCountRewards objects. It is returned by API::getDailyUncleCountRewards methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-uncle-block-count-and-rewards */

typedef JsonObjectsList<DailyUncleCountRewards> DailyUncleCountRewardsList;

inline QDebug operator<< (QDebug dbg, const DailyUncleCountRewardsList& dailyBlockCountRewardsList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyUncleCountRewardsList(count=%1)")
                   .arg(dailyBlockCountRewardsList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYUNCLECOUNTREWARDS_H
