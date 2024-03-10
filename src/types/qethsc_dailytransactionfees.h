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

#ifndef QT_ETHERSCAN_DAILYTRANSACTIONFEES_H
#define QT_ETHERSCAN_DAILYTRANSACTIONFEES_H

#include <QJsonObject>

#include "qethsc_constants.h"
#include "qethsc_ether.h"
#include "qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class DailyTransactionFees src/types/qethsc_dailytransactionfees.h
 *  @brief This object holds information about daily fees payed to miners. A list of such objects (DailyTransactionFeesList)
 *         is returned by API::getDailyNetworkTransactionFee methods.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-transaction-fee */

class DailyTransactionFees
{
public:
    /*! @brief Default constructor. Constructs invalid DailyTransactionFees object. */
    DailyTransactionFees();
    DailyTransactionFees(const QJsonObject& jsonObject);
    DailyTransactionFees(const QJsonValue& jsonValue) :
        DailyTransactionFees(jsonValue.toObject()) {}

    /*! @brief Returns true if this DailyTransactionFees object is valid and contains reasonable information.
     *         DailyTransactionFees object is considered to be valid if timeStampInteger() contains anything but not -1. */
    bool isValid() const               { return m_timeStamp != InvalidTimestamp; }

    /*! @brief Returns "UTCDate" field from reply from etherscan.io.
     *  @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-transaction-fee */
    QString utcDate() const            { return m_utcDate; }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of QDate object. */
    QDate  timeStamp() const           { return QDateTime::fromSecsSinceEpoch(m_timeStamp).date(); }

    /*! @brief Returns "unixTimeStamp" field from reply from etherscan.io in form of integer. */
    qint64 timeStampInteger() const    { return m_timeStamp; }

    /*! @brief Returns "transactionFee_Eth" field from reply from etherscan.io in form of Ether object. */
    Ether transactionFeeEth() const    { return Ether::fromEtherNumber(m_transactionFeeEth); }

    /*! @brief Returns "transactionFee_Eth" field from reply from etherscan.io in form of double. */
    double transactionFeeDouble() const { return m_transactionFeeEth; }

private:
    QString   m_utcDate;
    qint64    m_timeStamp;
    double    m_transactionFeeEth;
};

inline QDebug operator<< (QDebug dbg, const DailyTransactionFees& dailyTransactionFees)
{
    dbg.nospace() << qUtf8Printable(QString("DailyTransactionFees(utcDate=%1; transactionFeeDouble=%2 ETH)")
                                    .arg(dailyTransactionFees.utcDate())
                                    .arg(dailyTransactionFees.transactionFeeDouble()));

    return dbg.maybeSpace();
}

/*! @typedef DailyTransactionFeesList
 *  @brief This is a list of DailyTransactionFees objects. It is returned by API::getDailyNetworkTransactionFee methods.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-daily-network-transaction-fee */

typedef QtEtherscan::JsonObjectsList<DailyTransactionFees> DailyTransactionFeesList;

inline QDebug operator<< (QDebug dbg, const DailyTransactionFeesList& dailyTransactionFeesList)
{
    dbg.nospace() << qUtf8Printable(QString("DailyTransactionFeesList(count=%1)")
                   .arg(dailyTransactionFeesList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_DAILYTRANSACTIONFEES_H
