/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2023 Ivan Odinets
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

#include "./ether.h"
#include "./global.h"

namespace QtEtherscan {

class AccountBalance
{
public:
    AccountBalance() {}
    AccountBalance(const QJsonObject& jsonObject);
    AccountBalance(const QJsonValue& jsonValue) :
        AccountBalance(jsonValue.toObject()) {}

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

typedef JsonObjectsList<AccountBalance> AccountBalanceList;

inline QDebug operator<< (QDebug dbg, const AccountBalanceList& accountBalanceList)
{
    qUtf8Printable(QString("AccountBalanceList(count=%1)")
                   .arg(accountBalanceList.count()));

        return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ACCOUNTBALANCE_H
