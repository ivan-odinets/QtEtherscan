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

#ifndef QT_ETHERSCAN_DAILYBLOCKSIZE_H
#define QT_ETHERSCAN_DAILYBLOCKSIZE_H

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyBlockSize src/types/qethsc_dailyblocksize.h
 *  @brief This object holds information about daily average block size. A list of such objects (DailyBlockSizeList)
 *         is returned by API::getDailyAverageBlockSize methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-block-size */

class DailyBlockSize
{
public:
    /*! @brief Default constructor. Constructs invalid DailyBlockSize object. */
    DailyBlockSize();
    DailyBlockSize(const QJsonObject& jsonObject);
    DailyBlockSize(const QJsonValue& jsonValue) :
        DailyBlockSize(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyBlockSize object is valid and contains reasonable information. DailyBlockSize
     *         object is considered to be valid if blockSize() contains enything but not -1. */
    bool      isValid() const          { return m_blockSize != InvalidBlockSize; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-block-size */
    QString   utcDate() const          { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate     timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

    /*! @brief Returns "blockSize_bytes" field from reply from etherscan.io. */
    qint32    blockSize() const        { return m_blockSize; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint32    m_blockSize;
};

inline QDebug operator<< (QDebug dbg, const DailyBlockSize& dailyBlockSize)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockSize(utcDate=%1; blockSize=%2)")
                                    .arg(dailyBlockSize.utcDate())
                                    .arg(dailyBlockSize.blockSize()));

    return dbg.maybeSpace();
}

/*! @typedef DailyBlockSizeList
 *  @brief This is a list of DailyBlockSize objects. It is returned by methods API::getDailyAverageBlockSize
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/blocks#get-daily-average-block-size */

typedef JsonObjectsList<DailyBlockSize> DailyBlockSizeList;

inline QDebug operator<< (QDebug dbg, const DailyBlockSizeList& dailyBlockSizeList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyBlockSizeList(count=%1)")
                   .arg(dailyBlockSizeList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYBLOCKSIZE_H
