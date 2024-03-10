/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_ERC721TOKENTRANSFEREVENT_H
#define QT_ETHERSCAN_ERC721TOKENTRANSFEREVENT_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_constants.h"
#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC721TokenTransferEvent src/types/qethsc_erc721tokentransferevent.h
 *  @brief A list of such objects is returned by API::getListOfERC721TokenTransfers method.
 *
 * @see  https://docs.etherscan.io/api-endpoints/accounts#get-a-list-of-erc721-token-transfer-events-by-address */

class ERC721TokenTransferEvent
{
public:
    /*! @brief Default constructor. Constructs invalid ERC721TokenTransferEvent. */
    ERC721TokenTransferEvent();
    ERC721TokenTransferEvent(const QJsonObject& jsonObject);
    ERC721TokenTransferEvent(const QJsonValue& jsonValue) :
        ERC721TokenTransferEvent(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC721TokenTransferEvent object is valid and contains reasonable information.
     *         ERC721TokenTransferEvent object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns "blockNumber" field from etherscan.io reply. */
    qint32    blockNumber() const           { return m_blockNumber; }

    /*! @brief Returns "timeStamp" field from etherscan.io reply. */
    QDateTime timeStamp() const             { return QDateTime::fromSecsSinceEpoch(m_timeStamp); }

    /*! @brief Returns "hash" field from etherscan.io reply. */
    QString   hash() const                  { return m_hash; }

    /*! @brief Returns "nonce" field from etherscan.io reply. */
    quint64   nonce() const                 { return m_nonce; };

    /*! @brief Returns "blockHash" field from etherscan.io reply. */
    QString   blockHash() const             { return m_blockHash; }

    /*! @brief Returns "from" field from etherscan.io reply. */
    QString   from() const                  { return m_from; }

    /*! @brief Returns "contractAddress" field from etherscan.io reply. */
    QString   contractAddress() const       { return m_contractAddress; }

    /*! @brief Returns "to" field from etherscan.io reply. */
    QString   to() const                    { return m_to; }

    /*! @brief Returns "tokenID" field from etherscan.io reply. */
    QString   tokenIdString() const         { return m_tokenIdString; }

    /*! @brief Returns "tokenName" field from etherscan.io reply. */
    QString   tokenName() const             { return m_tokenName; }

    /*! @brief Returns "tokenSymbol" field from etherscan.io reply. */
    QString   tokenSymbol() const           { return m_tokenSymbol; }

    /*! @brief Returns "tokenDecimal" field from etherscan.io reply. */
    quint32   tokenDecimal() const          { return m_tokenDecimal; }

    /*! @brief Returns "transactionIndex" field from etherscan.io reply. */
    quint32   transactionIndex() const      { return m_transactionIndex; }

    /*! @brief Returns "gas" field from etherscan.io reply. */
    quint64   gas() const                   { return m_gas; }

    /*! @brief Returns "gasPrice" field from etherscan.io reply. */
    quint64   gasPrice() const              { return m_gasPrice; }

    /*! @brief Returns "gasUsed" field from etherscan.io reply. */
    quint64   gasUsed() const               { return m_gasUsed; }

    /*! @brief Returns "cumulativeGasUsed" field from etherscan.io reply. */
    quint64   cumulativeGasUsed() const     { return m_cumulativeGasUsed; }

    /*! @brief Returns "input" field from etherscan.io reply. */
    QString   input() const                 { return m_input; }

    /*! @brief Returns "confirmations" field from etherscan.io reply. */
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

/*! @typedef ERC721TokenTransferEventList
 *  @brief This is a list of ERC721TokenTransferEventList objects. It is returned by API::getListOfERC721TokenTransfers
 *         method. Nothing more than a QList with some extra constructors (JsonObjectsList).
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

#endif // QT_ETHERSCAN_ERC721TOKENTRANSFEREVENT_H
