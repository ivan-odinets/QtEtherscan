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

#ifndef QT_ETHERSCAN_DAILYTOTALGAS_H
#define QT_ETHERSCAN_DAILYTOTALGAS_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyTotalGas src/types/qethsc_dailytotalgas.h
 *  @brief This object holds information about daily total gas used. A list of such objects (DailyTotalGasList) is
 *         returned by API::getDailyTotalGasAmount methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-ethereum-daily-total-gas-used */

class DailyTotalGas
{
public:
    /*! @brief Default constructor. Constructs invalid DailyTotalGas object. */
    DailyTotalGas();
    DailyTotalGas(const QJsonObject& jsonObject);
    DailyTotalGas(const QJsonValue& jsonValue) :
        DailyTotalGas(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyTotalGas object is valid and contains reasonable information.
     *         DailyTotalGas object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-ethereum-daily-total-gas-used  */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "gasUsed" field from reply from etherscan.io. */
    qint64 gasUsed() const             { return m_gasUsed; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    qint64    m_gasUsed;
};

/*! @typedef DailyTotalGasList
 *  @brief This is a list of DailyTotalGas objects. It is returned by API::getDailyTotalGasAmount methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-ethereum-daily-total-gas-used */

typedef QtEtherscan::JsonObjectsList<DailyTotalGas> DailyTotalGasList;

inline QDebug operator<< (QDebug dbg, const DailyTotalGasList& dailyTotalGasList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyTotalGasList(count=%1)")
                   .arg(dailyTotalGasList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QETHSC_DAILYTOTALGAS_H
