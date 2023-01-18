/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023 Ivan Odinets
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

#ifndef INTERNALTRANSACTION_H
#define INTERNALTRANSACTION_H

#include "./ether.h"
#include "./global.h"

namespace QtEtherscan {

class InternalTransaction
{
public:
    InternalTransaction();
    InternalTransaction(const QJsonObject& jsonObject);
    InternalTransaction(const QJsonValue& jsonValue) :
        InternalTransaction(jsonValue.toObject()) {}

    bool      isValid() const          { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const      { return m_blockNumber; }
    QDateTime timeStamp() const        { return m_timeStamp; }
    QString   hash() const             { return m_hash; }
    QString   from() const             { return m_from; }
    QString   to() const               { return m_to; }
    Ether     value() const            { return m_value; }
    QString   contractAddress() const  { return m_contractAddress; }
    QString   input() const            { return m_input; }
    QString   typeString() const       { return m_typeString; }
    quint64   gas() const              { return m_gas; }
    quint64   gasUsed() const          { return m_gasUsed; }
    QString   traceIdString() const    { return m_traceIdString; }
    QString   isErrorString() const    { return m_isErrorString; }
    QString   errCodeString() const    { return m_errCodeString; }

private:
    qint32    m_blockNumber;
    QDateTime m_timeStamp;
    QString   m_hash;
    QString   m_from;
    QString   m_to;
    Ether     m_value;
    QString   m_contractAddress;
    QString   m_input;
    QString   m_typeString;
    quint64   m_gas;
    quint64   m_gasUsed;
    QString   m_traceIdString;
    QString   m_isErrorString;
    QString   m_errCodeString;
};

inline QDebug operator<< (QDebug dbg, const InternalTransaction& transaction)
{
    dbg.nospace() << qUtf8Printable(QString("InternalTransaction(from=%1; to=%2; hash=%3)")
                                    .arg(transaction.from())
                                    .arg(transaction.to())
                                    .arg(transaction.hash()));

    return dbg.maybeSpace();
}

typedef JsonObjectsList<InternalTransaction> InternalTransactionList;

inline QDebug operator<< (QDebug dbg, const InternalTransactionList& transactionList)
{
    dbg.nospace() << qUtf8Printable(QString("InternalTransactionList(count=%1)")
                                    .arg(transactionList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // INTERNALTRANSACTION_H
