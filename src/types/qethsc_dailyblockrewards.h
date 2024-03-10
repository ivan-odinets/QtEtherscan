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

#ifndef QT_ETHERSCAN_DAILYBLOCKREWARDS_H
#define QT_ETHERSCAN_DAILYBLOCKREWARDS_H

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

#include "./qethsc_constants.h"
#include "./qethsc_ether.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyBlockRewards src/types/qethsc_dailyblockrewards.h
 *  @brief This object holds information about daily average block rewards. A list of such objects (DailyBlockRewardsList) is
 *         returned by API::getDailyBlockRewards methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-rewards */

class DailyBlockRewards
{
public:
    /*! @brief Default constructor. Constructs invalid DailyBlockRewards object. */
    DailyBlockRewards();
    DailyBlockRewards(const QJsonObject& jsonObject);
    DailyBlockRewards(const QJsonValue& jsonValue) :
        DailyBlockRewards(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyBlockRewards object is valid and contains reasonable information. DailyBlockRewards
     *         object is considered to be valid if timeStampInteger() contains enything but not -1. */
    bool      isValid() const          { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-rewards */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "blockRewards_Eth" field from reply from etherscan.io in form of Ether object. */
    Ether     blockRewards() const     { return m_blockRewards; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    Ether     m_blockRewards;
};

inline QDebug operator<< (QDebug dbg, const DailyBlockRewards& dailyBlockRewards)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockRewards(utcDate=%1; blockRewards.eth()=%2 ETH)")
                                    .arg(dailyBlockRewards.utcDate())
                                    .arg(dailyBlockRewards.blockRewards().eth()));

    return dbg.maybeSpace();
}

/*! @typedef DailyBlockRewardsList
 *  @brief This is a list of DailyBlockRewards objects. It is returned by API::getDailyBlockRewards methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-rewards */

typedef JsonObjectsList<DailyBlockRewards> DailyBlockRewardsList;

inline QDebug operator<< (QDebug dbg, const DailyBlockRewardsList& dailyBlockRewardsList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockRewardsList(count=%1)")
                   .arg(dailyBlockRewardsList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYBLOCKREWARDS_H
