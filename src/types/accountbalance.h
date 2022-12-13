/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2021-2022 IvanOdinets
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

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>

#include "./etherbalance.h"

class AccountBalance
{
public:
    AccountBalance() {}
    AccountBalance(const QJsonObject& jsonObject);
    AccountBalance(const QJsonValue& jsonValue) :
        AccountBalance(jsonValue.toObject()) {}

    bool           isValid() const     { return m_account.isEmpty(); }

    QString        account() const     { return m_account; }
    EtherBalance   balance() const     { return m_balance; }

private:
    QString        m_account;
    EtherBalance   m_balance;
};

inline QDebug operator<< (QDebug dbg, const AccountBalance& accountBalance)
{
    dbg.nospace() << qUtf8Printable(QString("AccountBalance(account=%1; balance.eth()=%2 ETH)")
                                    .arg(accountBalance.account())
                                    .arg(accountBalance.balance().eth()));

    return dbg.maybeSpace();
}

class AccountBalanceList : public QList<AccountBalance>
{
public:
    AccountBalanceList() {}
    AccountBalanceList(const QJsonArray& jsonArray);
    AccountBalanceList(const QJsonValue& jsonValue) :
        AccountBalanceList(jsonValue.toArray()) {}
};

#endif // ACCOUNTBALANCE_H
