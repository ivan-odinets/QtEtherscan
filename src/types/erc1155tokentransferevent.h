/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets
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

#ifndef ERC1155TOKENTRANSFEREVENT_H
#define ERC1155TOKENTRANSFEREVENT_H

#include <QDebug>
#include <QJsonObject>

#include "./constants.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC1155TokenTransferEvent src/types/erc1155tokentransferevent.h
 *  @brief A list of such objects is returned by API::getListOfERC1155TokenTransfers method.
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc1155-token-transfer-events-by-address */

class ERC1155TokenTransferEvent
{
public:
    ERC1155TokenTransferEvent();
    ERC1155TokenTransferEvent(const QJsonObject& jsonObject);
    ERC1155TokenTransferEvent(const QJsonValue& jsonValue) :
        ERC1155TokenTransferEvent(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC1155TokenTransferEvent object is valid and contains reasonable information.
     *         ERC1155TokenTransferEvent object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }
    QString   hash() const                  { return m_hash; }
    quint64   nonce() const                 { return m_nonce; };
    QString   blockHash() const             { return m_blockHash; }
    quint32   transactionIndex() const      { return m_transactionIndex; }
    quint64   gas() const                   { return m_gas; }
    quint64   gasPrice() const              { return m_gasPrice; }
    quint64   gasUsed() const               { return m_gasUsed; }
    quint64   cumulativeGasUsed() const     { return m_cumulativeGasUsed; }
    QString   input() const                 { return m_input; }
    QString   contractAddress() const       { return m_contractAddress; }
    QString   from() const                  { return m_from; }
    QString   to() const                    { return m_to; }
    QString   tokenIdString() const         { return m_tokenIdString; }
    quint32   tokenValue() const            { return m_tokenValue; }
    QString   tokenName() const             { return m_tokenName; }
    QString   tokenSymbol() const           { return m_tokenSymbol; }
    quint64   confirmations() const         { return m_confirmations; }

private:
    qint32    m_blockNumber;
    qint64    m_timeStamp;
    QString   m_hash;
    quint64   m_nonce;
    QString   m_blockHash;
    quint32   m_transactionIndex;
    quint64   m_gas;
    quint64   m_gasPrice;
    quint64   m_gasUsed;
    quint64   m_cumulativeGasUsed;
    QString   m_input;
    QString   m_contractAddress;
    QString   m_from;
    QString   m_to;
    QString   m_tokenIdString;
    quint32   m_tokenValue;
    QString   m_tokenName;
    QString   m_tokenSymbol;
    quint64   m_confirmations;
};

inline QDebug operator<< (QDebug dbg, const ERC1155TokenTransferEvent& tokenTransferEvent)
{
    dbg.nospace() << qUtf8Printable(QString("ERC1155TokenTransferEvent(from=%1; to=%2; blockNumber=%3; tokenName=%4)")
                                    .arg(tokenTransferEvent.from())
                                    .arg(tokenTransferEvent.to())
                                    .arg(tokenTransferEvent.blockNumber())
                                    .arg(tokenTransferEvent.tokenName()));

    return dbg.maybeSpace();
}

/*! @typedef ERC1155TokenTransferEventList src/types/erc1155tokentransferevent.h
 *  @brief This is a list of ERC1155TokenTransferEvent objects. It is returned by API::getListOfERC1155TokenTransfers
 *         method. Nothing more than a QList with some extra constructors (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc1155-token-transfer-events-by-address */

typedef JsonObjectsList<ERC1155TokenTransferEvent> ERC1155TokenTransferEventList;

inline QDebug operator<<(QDebug dbg, const ERC1155TokenTransferEventList& erc1155TokenTransferEventList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC1155TokenTransferEventList(count=%1)")
                                    .arg(erc1155TokenTransferEventList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ERC1155TOKENTRANSFEREVENT_H
