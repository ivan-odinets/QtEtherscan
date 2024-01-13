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

#ifndef ETH_TRANSACTION_H
#define ETH_TRANSACTION_H

#include "./eth_response.h"
#include "../constants.h"
#include "../jsonobjectslist.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class Transaction src/types/proxy/eth_transaction.h
 *  @brief Object of this type contains data about etherium transaction, which can be returned either as a field of
 *         TransactionResponse object. Or can be present in one of the fields of Proxy::Block object (check
 *         Proxy::Block::transactions method.
 *  @details All string values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactionbyhash
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactionbyblockhashandindex
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactionbyblocknumberandindex
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionbyhash
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionbyblocknumberandindex */

class Transaction
{
public:
    Transaction();
    Transaction(const QJsonObject& jsonObject);
    Transaction(const QJsonValue& jsonValue);

    /*! @brief Returns true if this Poxy::Transaction object is valid and contains reasonable information. Proxy::Transaction
     *         object is considered to be valid if blockNumber() contains anything but not -1. */
    bool isValid() const                    { return m_blockNumber != InvalidBlockNumber; }

    /*! @brief Returns string with the hash of the block where this transaction was in. */
    QString blockHash() const               { return m_blockHash; }

    /*! @brief Returns integer with block number where this transaction was in. */
    qint32 blockNumber() const              { return m_blockNumber; }

    /*! @brief Returns string with block nummber. */
    QString blockNumberString() const       { return Helper::intToEthString(m_blockNumber); }

    /*! @brief Returns string with the address of the sender. */
    QString from() const                    { return m_from; }

    /*! @brief Returns integer with gas provided by the sender. */
    quint64 gas() const                     { return m_gas; }

    /*! @brief Returns string with gas provided by the sender. */
    QString gasString() const               { return Helper::intToEthString(m_gas); }

    /*! @brief Returns string with gas price provided by the sender in Wei. */
    QString gasPriceString() const          { return m_gasPrice; }

    /*! @brief Returns string with the hash of the transaction. */
    QString hash() const                    { return m_hash; }

    /*! @brief Returns string with the data send along with the transaction. */
    QString input() const                   { return m_input; }

    /*! @brief Returns string with the number of transactions made by the sender prior to this one. */
    QString nonceString() const             { return m_nonce; }

    /*! @brief Returns string with the address of the receiver. null when its a contract creation transaction. */
    QString to() const                      { return m_to; }

    /*! @brief Returns string with the index of the transaction position in the block. */
    QString transactionIndexString() const  { return m_transactionIndex; }

    /*! @brief Returns string with the value transferred in Wei. */
    QString valueString() const             { return m_value; }

    /*! @brief Returns string with the ECDSA recovery id. */
    QString vString() const                 { return m_v; }

    /*! @brief Returns string with the ECDSA signature r. */
    QString rString() const                 { return m_r; }

    /*! @brief Returns string with the ECDSA signature s. */
    QString sString() const                 { return m_s; }

private:
    QString m_blockHash;
    qint32  m_blockNumber;
    QString m_from;
    quint64 m_gas;
    QString m_gasPrice;
    QString m_hash;
    QString m_input;
    QString m_nonce;
    QString m_to;
    QString m_transactionIndex;
    QString m_value;
    QString m_v;
    QString m_r;
    QString m_s;
};

inline QDebug operator<< (QDebug dbg, const Transaction& transaction)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::Transaction(from=%1; to=%2; hash=%3)")
                                    .arg(transaction.from())
                                    .arg(transaction.to())
                                    .arg(transaction.hash()));

    return dbg.maybeSpace();
}

/*! @typedef TransactionList src/types/proxy/eth_transaction.h
 *  @brief This is a list of Proxy::Transaction objects. Nothing more than a QList with some extra constructors
 *         (JsonObjectList). */

typedef JsonObjectsList<Proxy::Transaction> TransactionList;

inline QDebug operator<< (QDebug dbg, const TransactionList& transactionList)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::TransactionList(count=%1)")
                                    .arg(transactionList.count()));

    return dbg.maybeSpace();
}

/*! @typedef TransactionResponse src/types/proxy/eth_transaction.h
 *  @brief Object of this type is returned by API::eth_getTransactionByHash and API::eth_getTransactionByBlockNumberAndIndex
 *         methods. Data about transaction can be obtained using TransactionResponse::transaction method.
 *
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber */

class TransactionResponse : public Response<Transaction>
{
public:
    TransactionResponse() :
        Response() {}
    TransactionResponse(const QJsonObject& jsonObject) :
        Response(jsonObject) {}
    TransactionResponse(const QJsonValue& jsonValue) :
        Response(jsonValue) {}

    /*! @brief Returns Proxy::Transaction object with data about specific transaction. */
    Transaction transaction() const    { return result(); }
};

inline QDebug operator<< (QDebug dbg, const TransactionResponse& transactionResponse)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::Transaction(from=%1; to=%2; transaction.hash()=%3)")
                                    .arg(transactionResponse.jsonRpc())
                                    .arg(transactionResponse.id())
                                    .arg(transactionResponse.transaction().hash()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // ETH_TRANSACTION_H
