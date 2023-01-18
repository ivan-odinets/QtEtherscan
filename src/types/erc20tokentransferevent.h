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

#ifndef ERC20TOKENTRANSFEREVENT_H
#define ERC20TOKENTRANSFEREVENT_H

#include "./global.h"

namespace QtEtherscan {

class ERC20TokenTransferEvent
{
public:
    ERC20TokenTransferEvent();
    ERC20TokenTransferEvent(const QJsonObject& jsonObject);
    ERC20TokenTransferEvent(const QJsonValue& jsonValue) :
        ERC20TokenTransferEvent(jsonValue.toObject()) {}

    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return m_timeStamp; }
    QString   hash() const                  { return m_hash; }
    quint64   nonce() const                 { return m_nonce; };
    QString   blockHash() const             { return m_blockHash; }
    QString   from() const                  { return m_from; }
    QString   contractAddress() const       { return m_contractAddress; }
    QString   to() const                    { return m_to; }
    quint64   value() const                 { return m_value; }
    QString   tokenName() const             { return m_tokenName; }
    QString   tokenSymbol() const           { return m_tokenSymbol; }
    quint16   tokenDecimal() const          { return m_tokenDecimal; }
    quint32   transactionIndex() const      { return m_transactionIndex; }
    quint64   gas() const                   { return m_gas; }
    quint64   gasPrice() const              { return m_gasPrice; }
    quint64   gasUsed() const               { return m_gasUsed; }
    quint64   cumulativeGasUsed() const     { return m_cumulativeGasUsed; }
    QString   input() const                 { return m_input; }
    quint64   confirmations() const         { return m_confirmations; }

private:
    qint32    m_blockNumber;
    QDateTime m_timeStamp;
    QString   m_hash;
    quint64   m_nonce;
    QString   m_blockHash;
    QString   m_from;
    QString   m_contractAddress;
    QString   m_to;
    quint64   m_value;
    QString   m_tokenName;
    QString   m_tokenSymbol;
    quint16   m_tokenDecimal;
    quint32   m_transactionIndex;
    quint64   m_gas;
    quint64   m_gasPrice;
    quint64   m_gasUsed;
    quint64   m_cumulativeGasUsed;
    QString   m_input;
    quint64   m_confirmations;
};

inline QDebug operator<< (QDebug dbg, const ERC20TokenTransferEvent& tokenTransferEvent)
{
    dbg.nospace() << qUtf8Printable(QString("ERC20TokenTransferEvent(from=%1; to=%2; blockNumber=%3; tokenName=%4)")
                                    .arg(tokenTransferEvent.from())
                                    .arg(tokenTransferEvent.to())
                                    .arg(tokenTransferEvent.blockNumber())
                                    .arg(tokenTransferEvent.tokenName()));

    return dbg.maybeSpace();
}

typedef JsonObjectsList<ERC20TokenTransferEvent> ERC20TokenTransferEventList;

inline QDebug operator<<(QDebug dbg, const ERC20TokenTransferEventList& erc20TokenTransferEventList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC20TokenTransferEventList(count=%1)")
                                    .arg(erc20TokenTransferEventList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ERC20TOKENTRANSFEREVENT_H
