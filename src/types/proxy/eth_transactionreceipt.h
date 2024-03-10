/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_ETH_TRANSACTIONRECEIPT_H
#define QT_ETHERSCAN_ETH_TRANSACTIONRECEIPT_H

#include "./eth_response.h"
#include "./eth_log.h"
#include "../qethsc_constants.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class TransactionReceipt src/types/proxy/eth_transactionreceipt.h
 *  @brief Object of this type contains data about transaction receipt, which is returned as a field of
 *         TransactionRecieptResponse object.
 *  @details All string values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactionreceipt */

class TransactionReceipt
{
public:
    /*! @brief Default constructor. Constructs invalid TransactionReceipt object. */
    TransactionReceipt();
    TransactionReceipt(const QJsonObject& jsonObject);
    TransactionReceipt(const QJsonValue& jsonValue) :
        TransactionReceipt(jsonValue.toObject()) {}

    /*! @brief Returns true if this TransactionReceipt object is valid and contains reasonable information.
     *         TransactionReceipt object is considered to be valid if blockNumber() contains anything but not -1. */
    bool      isValid() const               { return m_number != InvalidBlockNumber; }

    /*! @brief Returns hash of the hash of the transaction in eth format. */
    QString transactionHash() const         { return m_transactionHash; }

    /*! @brief Returns integer of the transactions index position in the block. */
    qint32 transactionIndex() const         { return m_transactionIndex; }

    /*! @brief Returns string with the position of the transaction index in the block. */
    QString transactionIndexString() const  { return Helper::intToEthString(m_transactionIndex); }

    /*! @brief Returns string with the hash of the block where this transaction was in. */
    QString blockHash() const               { return m_blockHash; }

    /*! @brief Returns block number as an integer. */
    qint32  blockNumber() const             { return m_number; }

    /*! @brief Returns block number as a string in eth format. */
    QString blockNumberString() const       { return Helper::intToEthString(m_number); }

    /*! @brief Returns string with the address of the sender. */
    QString from() const                    { return m_from; }

    /*! @brief Returns string with the address of the receiver. null when its a contract creation transaction. */
    QString to() const                      { return m_to; }

    /*! @brief Returns integer with the total amount of gas used when this transaction was executed in the block. */
    quint64 cumulativeGasUsed() const       { return m_cumulativeGasUsed; }

    /*! @brief Returns string with the total amount of gas used when this transaction was executed in the block. */
    QString cumulativeGasUsedString() const { return Helper::intToEthString(m_cumulativeGasUsed); }

    /*! @brief Returns integer with the sum of the base fee and tip paid per unit of gas. */
    quint64 effectiveGasPrice() const       { return m_effectiveGasPrice; }

    /*! @brief Returns string with the sum of the base fee and tip paid per unit of gas. */
    QString effectiveGasPriceString() const { return Helper::intToEthString(m_effectiveGasPrice); }

    /*! @brief Returns integer with the amount of gas used by this specific transaction alone. */
    quint64 gasUsed() const                 { return m_gasUsed; }

    /*! @brief Returns string with the amount of gas used by this specific transaction alone. */
    QString gasUsedString() const           { return Helper::intToEthString(m_gasUsed); }

    /*! @brief Returns string with the contract address created, if the transaction was a contract creation. Otherwise
     *         - empty string. */
    QString contractAddress() const         { return m_contractAddress; }

    /*! @brief Retrns LogList object with the array of log objects, which this transaction generated. */
    LogList logs() const                    { return m_logs; }

    /*! @brief Returns string with the bloom filter for light clients to quickly retrieve related logs. */
    QString logsBloomString() const         { return m_logsBloom; }

    /*! @brief Returns integer with the transaction type, 0x0 for legacy transactions, 0x1 for access list types, 0x2
     *         for dynamic fees. */
    qint8 type() const                      { return m_type; }

    /*! @brief Returns string with the transaction type, 0x0 for legacy transactions, 0x1 for access list types, 0x2
     *         for dynamic fees. */
    QString typeString() const              { return Helper::intToEthString(m_type); }

private:
    QString m_transactionHash;
    qint32  m_transactionIndex;
    QString m_blockHash;
    qint32  m_number;
    QString m_from;
    QString m_to;
    quint64 m_cumulativeGasUsed;
    quint64 m_effectiveGasPrice;
    quint64 m_gasUsed;
    QString m_contractAddress;
    QString m_logsBloom;
    LogList m_logs;
    qint8   m_type;
};

inline QDebug operator<< (QDebug dbg, const TransactionReceipt& transactionReceipt)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::TransactionReceipt(transactionHash=%1)")
                                    .arg(transactionReceipt.transactionHash()));

    return dbg.maybeSpace();
}

/*! @class TransactionReceiptResponse src/types/proxy/eth_transactionreceipt.h
 *  @brief Object of this type is returned by API::eth_getTransactionReceipt method. Data about transaction receipt can
 *         be obtained using TransactionReceiptResponse::transactionReceipt method.
 *
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionreceipt */

class TransactionReceiptResponse : public ObjectResponse<TransactionReceipt>
{
public:
    TransactionReceiptResponse() :
        ObjectResponse<TransactionReceipt>() {}
    TransactionReceiptResponse(const QJsonObject& jsonObject) :
        ObjectResponse<TransactionReceipt>(jsonObject) {}
    TransactionReceiptResponse(const QJsonValue& jsonValue) :
        TransactionReceiptResponse(jsonValue.toObject()) {}

    /*! @brief Returns Proxy::TransactionReceipt object with data about specific transaction receipt. */
    TransactionReceipt transactionReceipt() const     { return result(); }
};

inline QDebug operator<< (QDebug dbg, const TransactionReceiptResponse& transactionReceiptResponse)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::TransactionReceiptResponse(jsonrpc=%1; id=%2; transactionReceipt.transactionHash()=%3)")
                                    .arg(transactionReceiptResponse.jsonRpc())
                                    .arg(transactionReceiptResponse.id())
                                    .arg(transactionReceiptResponse.transactionReceipt().transactionHash()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ETH_TRANSACTIONRECEIPT_H
