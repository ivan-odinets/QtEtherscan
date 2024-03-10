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

#ifndef QT_ETHERSCAN_ETH_BLOCK_H
#define QT_ETHERSCAN_ETH_BLOCK_H

#include "./eth_transaction.h"
#include "./eth_helper.h"
#include "../qethsc_constants.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class Block src/types/proxy/eth_block.h
 *  @brief Object of this type contains data about etherium block, which is returned as a field of BlockResponse object.
 *  @details All string values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_getblockbyhash
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_getblockbynumber
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getunclebyblocknumberandindex */

class Block
{
public:
    /*! @brief Default constructor. Constructs invalid Proxy::Block object. */
    Block();
    Block(const QJsonObject& jsonObject);
    Block(const QJsonValue& jsonValue) :
        Block(jsonValue.toObject()) {}

    /*! @brief Returns true if this Poxy::Block object is valid and contains reasonable information. Proxy::Block object is considered
     *         to be valid if number() contains anything but not -1. */
    bool isValid() const                    { return m_number != InvalidBlockNumber; }

    /*! @brief Returns integer with the block number. */
    qint32  number() const                  { return m_number; }

    /*! @brief Returns string with the block number. */
    QString numberString() const            { return Helper::intToEthString(m_number); }

    /*! @brief Returns string with the hash of the block. */
    QString hash() const                    { return m_hash; }

    /*! @brief Returns string with the hash of the parent block. */
    QString parentHash() const              { return m_parentHash; }

    /*! @brief Returns integer with the "nonce" field. */
    quint64 nonce() const                   { return m_nonce; }

    /*! @brief Returns string with the "nonce" field. */
    QString nonceString() const             { return Helper::intToEthString(m_nonce); }

    /*! @brief Returns string with the SHA3 of the uncles data in the block. */
    QString sha3Uncles() const              { return m_sha3Uncles; }

    /*! @brief Returns string with the bloom filter for the logs of the block. */
    QString logsBloom() const               { return m_logsBloom; }

    /*! @brief Returns string with the root of the transaction trie of the block. */
    QString transactionsRoot() const        { return m_transactionsRoot; }

    /*! @brief Returns string with the root of the final state trie of the block. */
    QString stateRoot() const               { return m_stateRoot; }

    /*! @brief Returns string with the root of the receipts trie of the block. */
    QString receiptsRoot() const            { return m_receiptsRoot; }

    /*! @brief Returns string with the address of the beneficiary to whom the mining rewards were given. */
    QString miner() const                   { return m_miner; }

    /*! @brief Returns string with the difficulty for this block. */
    QString difficultyString() const        { return m_difficulty; }

    /*! @brief Returns string with the total difficulty of the chain until this block. */
    QString totalDifficultyString() const   { return m_totalDifficulty; }

    /*! @brief Returns string with the "extraData" field. */
    QString extraData() const               { return m_extraData; }

    /*! @brief Returns integer with size of the block in bytes. */
    qint32 size() const                     { return m_size; }

    /*! @brief Returns string with the size of this block in bytes. */
    QString sizeString() const              { return Helper::intToEthString(m_size); }

    /*! @brief Returns integer with maximum amount of gas allowed in this block. */
    quint64 gasLimit() const                { return m_gasLimit; }

    /*! @brief Returns string with the maximum gas allowed in this block. */
    QString gasLimitString() const          { return Helper::intToEthString(m_gasLimit); }

    /*! @brief Returns integer with the total used gas by all transactions in this block. */
    quint64 gasUsed() const                 { return m_gasUsed; }

    /*! @brief Returns string with the total used gas by all transactions in this block. */
    QString gasUsedString() const           { return Helper::intToEthString(m_gasUsed); }

    /*! @brief Returns integer with the timestamp for when the block was collated. */
    qint64 timestampInteger() const         { return m_timestamp; }

    /*! @brief Returns QDateTime with the timestamp for when the block was collated. */
    QDateTime timestamp() const             { return QDateTime::fromSecsSinceEpoch(m_timestamp); }

    /*! @brief Returns string with the timestamp for when the block was collated. */
    QString timestampString() const         { return Helper::intToEthString(m_timestamp); }

    /*! @brief This method returns list of transaction hashes of transactions present in block. */
    QStringList transactionHashList() const { return m_transactionHashList; }

    /*! @brief Returns list of Proxy::Transaction objects, which representates transactions contained in this block.
     *  @details If this Proxy::Block object was returned by API::eth_getBlockByNumber method with passing false parameter -
     *           this method will return empty list.*/
    TransactionList transactions() const    { return m_transactionList; }

    /*! @brief Returns QStringList with array of uncle hashes. */
    QStringList uncles() const              { return m_uncles; }

private:
    qint32              m_number;
    QString             m_hash;
    QString             m_parentHash;
    quint64             m_nonce;
    QString             m_sha3Uncles;
    QString             m_logsBloom;
    QString             m_transactionsRoot;
    QString             m_stateRoot;
    QString             m_receiptsRoot;
    QString             m_miner;
    QString             m_difficulty;
    QString             m_totalDifficulty;
    QString             m_extraData;
    qint32              m_size;
    quint64             m_gasLimit;
    quint64             m_gasUsed;
    qint64              m_timestamp;

    QStringList         m_transactionHashList;
    TransactionList     m_transactionList;
    QStringList         m_uncles;
};

inline QDebug operator<< (QDebug dbg, const Block& blockNumber)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::Block(numberString=%1; hashString=%2)")
                                    .arg(blockNumber.numberString())
                                    .arg(blockNumber.hash()));

    return dbg.maybeSpace();
}

/*! @typedef BlockResponse src/types/proxy/eth_block.h
 *  @brief Object of this type is returned by API::eth_getBlockByNumber and API::eth_getUncleByBlockNumberAndIndex
 *         methods. Data about block can be obtained using BlockResponse::block method.
 *
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getunclebyblocknumberandindex */

class BlockResponse : public ObjectResponse<Block>
{
public:
    BlockResponse() :
        ObjectResponse<Block>() {}
    BlockResponse(const QJsonObject& jsonObject) :
        ObjectResponse<Block>(jsonObject) {}
    BlockResponse(const QJsonValue& jsonValue) :
        ObjectResponse<Block>(jsonValue) {}

    /*! @brief Returns Proxy::Block object with data about specific block. */
    Block     block() const  { return result(); }
};

inline QDebug operator<< (QDebug dbg, const BlockResponse& blockResponse)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::BlockResponse(jsonrpc=%1; id=%2; block.numberString()=%3)")
                                    .arg(blockResponse.jsonRpc())
                                    .arg(blockResponse.id())
                                    .arg(blockResponse.block().numberString()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // ETH_BLOCK_H
