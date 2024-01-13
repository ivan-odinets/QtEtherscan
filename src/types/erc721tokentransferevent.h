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

#ifndef ERC721TOKENTRANSFEREVENT_H
#define ERC721TOKENTRANSFEREVENT_H

#include <QDebug>
#include <QJsonObject>

#include "./constants.h"
#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC721TokenTransferEvent src/types/erc721tokentransferevent.h
 *  @brief A list of such objects is returned by API::getListOfERC721TokenTransfers method.
 *
 * @see  https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc721-token-transfer-events-by-address */

class ERC721TokenTransferEvent
{
public:
    ERC721TokenTransferEvent();
    ERC721TokenTransferEvent(const QJsonObject& jsonObject);
    ERC721TokenTransferEvent(const QJsonValue& jsonValue) :
        ERC721TokenTransferEvent(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC721TokenTransferEvent object is valid and contains reasonable information.
     *         ERC721TokenTransferEvent object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    qint32    blockNumber() const           { return m_blockNumber; }
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }
    QString   hash() const                  { return m_hash; }
    quint64   nonce() const                 { return m_nonce; };
    QString   blockHash() const             { return m_blockHash; }
    QString   from() const                  { return m_from; }
    QString   contractAddress() const       { return m_contractAddress; }
    QString   to() const                    { return m_to; }
    QString   tokenIdString() const         { return m_tokenIdString; }
    QString   tokenName() const             { return m_tokenName; }
    QString   tokenSymbol() const           { return m_tokenSymbol; }
    quint32   tokenDecimal() const          { return m_tokenDecimal; }
    quint32   transactionIndex() const      { return m_transactionIndex; }
    quint64   gas() const                   { return m_gas; }
    quint64   gasPrice() const              { return m_gasPrice; }
    quint64   gasUsed() const               { return m_gasUsed; }
    quint64   cumulativeGasUsed() const     { return m_cumulativeGasUsed; }
    QString   input() const                 { return m_input; }
    quint64   confirmations() const         { return m_confirmations; }

private:
    qint32         m_blockNumber;
    qint64         m_timeStamp;
    QString        m_hash;
    quint64        m_nonce;
    QString        m_blockHash;
    QString        m_from;
    QString        m_contractAddress;
    QString        m_to;
    QString        m_tokenIdString;
    QString        m_tokenName;
    QString        m_tokenSymbol;
    quint32        m_tokenDecimal;
    quint32        m_transactionIndex;
    quint64        m_gas;
    quint64        m_gasPrice;
    quint64        m_gasUsed;
    quint64        m_cumulativeGasUsed;
    QString        m_input;
    quint64        m_confirmations;
};

inline QDebug operator<< (QDebug dbg, const ERC721TokenTransferEvent& tokenTransferEvent)
{
    dbg.nospace() << qUtf8Printable(QString("ERC721TokenTransferEvent(from=%1; to=%2; blockNumber=%3; tokenName=%4)")
                                    .arg(tokenTransferEvent.from())
                                    .arg(tokenTransferEvent.to())
                                    .arg(tokenTransferEvent.blockNumber())
                                    .arg(tokenTransferEvent.tokenName()));

    return dbg.maybeSpace();
}

/*! @typedef ERC721TokenTransferEventList src/types/erc721tokentransferevent.h
 *  @brief This is a list of ERC721TokenTransferEventList objects. It is returned by API::getListOfERC721TokenTransfers
 *         method. Nothing more than a QList with some extra constructors (JsonObjectList).
 *
 * @see https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc721-token-transfer-events-by-address */

typedef JsonObjectsList<ERC721TokenTransferEvent> ERC721TokenTransferEventList;

inline QDebug operator<<(QDebug dbg, const ERC721TokenTransferEventList& erc721TokenTransferEventList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC721TokenTransferEventList(count=%1)")
                                    .arg(erc721TokenTransferEventList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ERC721TOKENTRANSFEREVENT_H
