/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_BEACONCHAINWITHDRAWAL_H
#define QT_ETHERSCAN_BEACONCHAINWITHDRAWAL_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_ether.h"
#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class BeaconChainWithdrawal src/types/qethsc_beaconchainwithdrawal.h
 *  @brief A list of such objects is returned by API::getBeaconChainWithdrawals method.
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-beacon-chain-withdrawals-by-address-and-block-range */

class BeaconChainWithdrawal
{
public:
    /*! @brief Default constructor. Constructs invalid BeaconChainWithdrawal object. */
    BeaconChainWithdrawal();
    BeaconChainWithdrawal(const QJsonObject& jsonObject);
    BeaconChainWithdrawal(const QJsonValue& jsonValue) :
        BeaconChainWithdrawal(jsonValue.toObject()) {}

    /*! @brief Returns true if this BeaconChainWithdrawal object is valid and contains reasonable information.
     *         BeaconChainWithdrawal object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns "withdrawalIndex" field from etherscan.io response. */
    qint32    withdrawalIndex() const  { return m_withdrawalIndex; }

    /*! @brief Returns "validatorIndex" field from etherscan.io response. */
    qint32    validatorIndex() const   { return m_validatorIndex; }

    /*! @brief Returns "address" field from etherscan.io response. */
    QString   address() const          { return m_address; }

    /*! @brief Returns "amount" field from etherscan.io response in form of Ether object. */
    Ether     amount() const           { return m_amount; }

    /*! @brief Returns "blockNumber" field from etherscan.io response. */
    qint32    blockNumber() const      { return m_blockNumber; }

    /*! @brief Returns "timestamp" field from etherscan.io response in form of QDateTime object. */
    QDateTime timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }

    /*! @brief Returns "timestamp" field from etherscan.io response in form of integer. */
    qint64    timeStampInteger() const { return m_timeStamp; }

private:
    qint32    m_withdrawalIndex;
    qint32    m_validatorIndex;
    QString   m_address;
    Ether     m_amount;
    qint32    m_blockNumber;
    qint64    m_timeStamp;
    Ether     m_blockReward;
};

inline QDebug operator<< (QDebug dbg, const BeaconChainWithdrawal& beaconChainWithdrawal)
{
    dbg.nospace() << qUtf8Printable(QString("BeaconChainWithdrawal(blockNumber=%1; timeStamp=%2; amount=%3 ETH)")
                                    .arg(beaconChainWithdrawal.blockNumber())
                                    .arg(beaconChainWithdrawal.timeStamp().toString())
                                    .arg(beaconChainWithdrawal.amount().eth()));

    return dbg.maybeSpace();
}

/*! @typedef BeaconChainWithdrawalList
 *  @brief This is a list of BeaconChainWithdrawal objects. It is returned by API::getBeaconChainWithdrawals method.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-beacon-chain-withdrawals-by-address-and-block-range */

typedef JsonObjectsList<BeaconChainWithdrawal> BeaconChainWithdrawalList;

inline QDebug operator<<(QDebug dbg, const BeaconChainWithdrawalList& beaconChainWithdrawalList)
{
    dbg.nospace() << qUtf8Printable(QString("BeaconChainWithdrawalList(count=%1)")
                                    .arg(beaconChainWithdrawalList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_BEACONCHAINWITHDRAWAL_H
