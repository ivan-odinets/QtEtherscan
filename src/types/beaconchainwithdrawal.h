/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets
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

#ifndef BEACONCHAINWITHDRAWAL_H
#define BEACONCHAINWITHDRAWAL_H

#include <QDebug>
#include <QJsonObject>

#include "./ether.h"
#include "./constants.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class BeaconChainWithdrawal src/types/beaconchainwithdrawal.h
 *  @brief A list of such objects is returned by API::getBeaconChainWithdrawals method
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-beacon-chain-withdrawals-by-address-and-block-range */

class BeaconChainWithdrawal
{
public:
    BeaconChainWithdrawal();
    BeaconChainWithdrawal(const QJsonObject& jsonObject);
    BeaconChainWithdrawal(const QJsonValue& jsonValue) :
        BeaconChainWithdrawal(jsonValue.toObject()) {}

    /*! @brief Returns true if this BeaconChainWithdrawal object is valid and contains reasonable information.
     *         BeaconChainWithdrawal object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    qint32    withdrawalIndex() const  { return m_withdrawalIndex; }
    qint32    validatorIndex() const   { return m_validatorIndex; }
    QString   address() const          { return m_address; }
    Ether     amount() const           { return m_amount; }
    qint32    blockNumber() const      { return m_blockNumber; }
    QDateTime timeStamp() const        { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }

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
    dbg.nospace() << qUtf8Printable(QString("BeaconChainWithdrawal(blockNumber=%1; timeStamp=%2)")
                                    .arg(beaconChainWithdrawal.blockNumber())
                                    .arg(beaconChainWithdrawal.timeStamp().toString()));

    return dbg.maybeSpace();
}

/*! @typedef BeaconChainWithdrawalList src/types/beaconchainwithdrawal.h
 *  @brief This is a list of BeaconChainWithdrawal objects. It is returned by API::getBeaconChainWithdrawals method.
 *         Nothing more than a QList with some extra constructors (JsonObjectList).
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

#endif // BEACONCHAINWITHDRAWAL_H
