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

#ifndef ETH_BLOCKNUMBER_H
#define ETH_BLOCKNUMBER_H

#include "./eth_response.h"
#include "./eth_helper.h"
#include "../constants.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class BlockNumberResponse src/types/proxy/eth_blocknumber.h
 *  @brief Object of this type is returned by API::eth_blockNumber method.
 *  @details Block number can be obtained using BlockNumberResponse::blockNumber and BlockNumberResponse::blockNumberString
 *           methods. For other available methods check Proxy::Response and Proxy::Response<qint32> classes. All string
 *           values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_blocknumber
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_blocknumber */

class BlockNumberResponse : public Response<qint32>
{
public:
    BlockNumberResponse() :
        Response<qint32>(InvalidBlockNumber) {}
    BlockNumberResponse(const QJsonObject& jsonObject,qint32 defaultValue = InvalidBlockNumber) :
        Response<qint32>(jsonObject,defaultValue) {}
    BlockNumberResponse(const QJsonValue& jsonValue) :
        BlockNumberResponse(jsonValue.toObject(),InvalidBlockNumber) {}

    /*! @brief Returns true if this Poxy::BlockNumberResponse object is valid and contains reasonable information.
     *         Proxy::BlockNumberResponse object is considered to be valid if blockNumber() contains anything but not -1. */
    bool isValid() const              { return blockNumber() != InvalidBlockNumber; }

    /*! @brief This method returns integer containing block number. */
    qint32 blockNumber() const        { return result(); }

    /*! @brief This method returns QString containing block number in eth format.
     *  @see https://ethereum.org/en/developers/docs/apis/json-rpc/#hex-encoding */
    QString blockNumberString() const { return Helper::intToEthString(result()); }
};

inline QDebug operator<< (QDebug dbg, const BlockNumberResponse& blockNumber)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::BlockNumberResponse(jsonrpc=%1; id=%2; blockNumberString=%3)")
                                    .arg(blockNumber.jsonRpc())
                                    .arg(blockNumber.id())
                                    .arg(blockNumber.blockNumberString()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // ETH_BLOCKNUMBER_H
