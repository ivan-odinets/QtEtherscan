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

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDebug>
#include <QJsonObject>

#include "./ether.h"
#include "./constants.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class Transaction src/types/transaction.h
 *  @brief A list of such objects is returned by API::getListOfNomalTransactions method.
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-normal-transactions-by-address */

class Transaction
{
public:
    Transaction();
    Transaction(const QJsonObject& jsonObject);
    Transaction(const QJsonValue& jsonValue) :
        Transaction(jsonValue.toObject()) {}

    /*! @brief Returns true if this Transaction object is valid and contains reasonable information. Transaction object
     *         is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }
    QString   hash() const                  { return m_hash; }
    quint64   nonce() const                 { return m_nonce; }
    quint64   transactionIndex() const      { return m_transactionIndex; }
    QString   from() const                  { return m_from; }
    QString   to() const                    { return m_to; };
    Ether     value() const                 { return m_value; }
    quint64   gas() const                   { return m_gas; }
    quint64   gasPrice() const              { return m_gasPrice; }
    QString   blockHash() const             { return m_blockHash; }
    QString   isErrorString() const         { return m_isErrorString; }
    QString   txreceiptStatusString() const { return m_txreceiptStatusString; }
    QString   input() const                 { return m_input; }
    QString   contractAddress() const       { return m_contractAddress; }
    quint64   cumulativeGasUsed() const     { return m_cumulativeGasUsed; }
    quint64   gasUsed() const               { return m_gasUsed; }
    QString   methodIdString() const        { return m_methodIdString; }
    quint32   confirmations()               { return m_confirmations; }
    QString   functionName() const          { return m_functionName; }

private:
    qint32    m_blockNumber;
    qint64    m_timeStamp;
    QString   m_hash;
    quint64   m_nonce;
    QString   m_blockHash;
    quint32   m_transactionIndex;
    QString   m_from;
    QString   m_to;
    Ether     m_value;
    quint64   m_gas;
    quint64   m_gasPrice;
    QString   m_isErrorString;
    QString   m_txreceiptStatusString;
    QString   m_input;
    QString   m_contractAddress;
    quint64   m_cumulativeGasUsed;
    quint64   m_gasUsed;
    quint64   m_confirmations;
    QString   m_methodIdString;
    QString   m_functionName;
};

inline QDebug operator<< (QDebug dbg, const Transaction& transaction)
{
    dbg.nospace() << qUtf8Printable(QString("Transaction(from=%1; to=%2; hash=%3)")
                                    .arg(transaction.from())
                                    .arg(transaction.to())
                                    .arg(transaction.hash()));

    return dbg.maybeSpace();
}

/*! @typedef TransactionList src/types/transaction.h
 *  @brief This is a list of Transaction objects. It is returned by API::getListOfNomalTransactions method. Nothing more
 *         than a QList with some extra constructors (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-normal-transactions-by-address */

typedef JsonObjectsList<Transaction> TransactionList;

inline QDebug operator<< (QDebug dbg, const TransactionList& transactionList)
{
    dbg.nospace() << qUtf8Printable(QString("TransactionList(count=%1)")
                                    .arg(transactionList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // TRANSACTION_H
