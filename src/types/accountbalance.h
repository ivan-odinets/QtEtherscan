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

#ifndef ACCOUNTBALANCE_H
#define ACCOUNTBALANCE_H

#include <QDebug>
#include <QJsonObject>

#include "./ether.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class AccountBalance src/types/accountbalance.h
 *  @brief This object holds information about account and its balance. A list of such objects (AccountBalanceList) is
 *         returned by method API::getEtherBalance (if called for multiple addresses within one API call).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-multiple-addresses-in-a-single-call */

class AccountBalance
{
public:
    AccountBalance() {}
    AccountBalance(const QJsonObject& jsonObject);
    AccountBalance(const QJsonValue& jsonValue) :
        AccountBalance(jsonValue.toObject()) {}

    /*! @brief Returns true if this AccountBalance object is valid and contains reasonable information. AccountBalance
     *         object is considered to be valid if account() contains non-empty QString. */
    bool      isValid() const     { return m_account.isEmpty(); }

    QString   account() const     { return m_account; }
    Ether     balance() const     { return m_balance; }

private:
    QString   m_account;
    Ether     m_balance;
};

inline QDebug operator<< (QDebug dbg, const AccountBalance& accountBalance)
{
    dbg.nospace() << qUtf8Printable(QString("AccountBalance(account=%1; balance.eth()=%2 ETH)")
                                    .arg(accountBalance.account())
                                    .arg(accountBalance.balance().eth()));

    return dbg.maybeSpace();
}

/*! @typedef AccountBalanceList
 *  @brief This is a list of AccountBalance objects. It is returned by method API::getEtherBalance (if called for multiple
 *         addresses within one API call). Nothing more than a QList with some extra constructors (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-multiple-addresses-in-a-single-call */

typedef JsonObjectsList<AccountBalance> AccountBalanceList;

inline QDebug operator<< (QDebug dbg, const AccountBalanceList& accountBalanceList)
{
    dbg.nospace() << qUtf8Printable(QString("AccountBalanceList(count=%1)")
                   .arg(accountBalanceList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ACCOUNTBALANCE_H
