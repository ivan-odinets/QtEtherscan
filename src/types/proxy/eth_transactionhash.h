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

#ifndef QT_ETHERSCAN_ETH_TRANSACTIONHASH_H
#define QT_ETHERSCAN_ETH_TRANSACTIONHASH_H

#include "./eth_response.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class TransactionHashResponse src/types/proxy/eth_transactionhash.h
 *  @brief Object of this type is returned by API::eth_sendRawTransaction method.
 *  @details All string values, returned by methods of this class are formatted in
 *           eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_sendrawtransaction
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_sendrawtransaction */

class TransactionHashResponse : public StringResponse
{
public:
    TransactionHashResponse() :
        StringResponse() {}
    TransactionHashResponse(const QJsonObject& jsonObject) :
        StringResponse(jsonObject) {}
    TransactionHashResponse(const QJsonValue& jsonValue) :
        TransactionHashResponse(jsonValue.toObject()) {}

    QString transactionHash() const    { return StringResponse::result(); }
};

inline QDebug operator<< (QDebug dbg, const TransactionHashResponse& transactionHashResponse)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::TransactionHashResponse(jsonrpc=%1; id=%2; transactionHash=%3)")
                                    .arg(transactionHashResponse.jsonRpc())
                                    .arg(transactionHashResponse.id())
                                    .arg(transactionHashResponse.transactionHash()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ETH_TRANSACTIONHASH_H
