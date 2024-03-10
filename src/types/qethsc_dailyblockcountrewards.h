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

#ifndef QT_ETHERSCAN_DAILYBLOCKCOUNTREWARDS_H
#define QT_ETHERSCAN_DAILYBLOCKCOUNTREWARDS_H

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

#include "./qethsc_ether.h"
#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyBlockCountRewards src/types/qethsc_dailyblockcountrewards.h
 *  @brief This object holds information about daily average block count and rewards. A list of such objects (DailyBlockCountRewardsList) is
 *         returned by API::getDailyBlockCountRewards method.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-count-and-rewards */

class DailyBlockCountRewards
{
public:
    /*! @brief Default constructor. Constructs invalid DailyBlockCountRewards object. */
    DailyBlockCountRewards();
    DailyBlockCountRewards(const QJsonObject& jsonObject);
    DailyBlockCountRewards(const QJsonValue& jsonValue) :
        DailyBlockCountRewards(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyBlockCountRewards object is valid and contains reasonable information. DailyBlockCountRewards
     *         object is considered to be valid if blockCount() contains enything but not -1. */
    bool      isValid() const          { return m_blockCount != InvalidBlockCount; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-count-and-rewards */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "blockRewards_Eth" field from reply from etherscan.io in form of Ether object. */
    Ether     blockRewards() const     { return m_blockRewards; }

    /*! @brief Returns "blockCount" field from reply from etherscan.io */
    qint32    blockCount() const       { return m_blockCount; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint32    m_blockCount;
    Ether     m_blockRewards;
};

inline QDebug operator<< (QDebug dbg, const DailyBlockCountRewards& dailyBlockCountRewards)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockCountRewards(utcDate=%1; blockRewards.eth()=%2 ETH; blockCount=%3)")
                                    .arg(dailyBlockCountRewards.utcDate())
                                    .arg(dailyBlockCountRewards.blockRewards().eth())
                                    .arg(dailyBlockCountRewards.blockCount()));

    return dbg.maybeSpace();
}

/*! @typedef DailyBlockCountRewardsList
 *  @brief This is a list of DailyBlockCountRewardsList objects. It is returned by methods API::getDailyBlockCountRewards
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-block-count-and-rewards */

typedef JsonObjectsList<DailyBlockCountRewards> DailyBlockCountRewardsList;

inline QDebug operator<< (QDebug dbg, const DailyBlockCountRewardsList& dailyBlockCountRewardsList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockCountRewardsList(count=%1)")
                   .arg(dailyBlockCountRewardsList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QETHSC_DAILYBLOCKCOUNTREWARDS_H
