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

#ifndef QT_ETHERSCAN_ETH_TRANSACTIONCOUNT_H
#define QT_ETHERSCAN_ETH_TRANSACTIONCOUNT_H

#include "./eth_response.h"
#include "./eth_helper.h"
#include "../qethsc_constants.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class TransactionCountResponse src/types/proxy/eth_transactioncount.h
 *  @brief Object of this type is returned by API::eth_getBlockTransactionCountByNumber and eth_getTransactionCount
 *         methods.
 *  @details Transaction count can be obtained using TransactionCountResponse::transactionCount and
 *           TransactionCountResponse::transactionCountString methods. For other available methods check Proxy::Response
 *           and Proxy::Response<qint32> classes. All string values, returned by methods of this class are formatted in
 *           eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_getblocktransactioncountbynumber
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gettransactioncount
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactioncount
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblocktransactioncountbynumber */

class TransactionCountResponse : public IntResponse
{
public:
    /*! @brief Default constructor. Constructs invalid TransactionCountResponse object. */
    TransactionCountResponse() :
        IntResponse(InvalidTransactionCount) {}
    TransactionCountResponse(const QJsonObject& jsonObject, qint32 defaultValue = InvalidTransactionCount) :
        IntResponse(jsonObject,defaultValue) {}
    TransactionCountResponse(const QJsonValue& jsonValue) :
        TransactionCountResponse(jsonValue.toObject(),InvalidTransactionCount) {}

    /*! @brief Returns true if this Poxy::TransactionCountResponse object is valid and contains reasonable information.
     *         Proxy::TransactionCountResponse object is considered to be valid if transactionCount() contains anything
     *         but not -1. */
    bool      isValid() const                    { return transactionCount() != InvalidTransactionCount; }

    /*! @brief This method returns integer containing transaction count. */
    qint32    transactionCount() const           { return result(); }

    /*! @brief This method returns QString containing transaction count in eth format.
     *  @see https://ethereum.org/en/developers/docs/apis/json-rpc/#hex-encoding */
    QString   transactionCountString() const     { return Helper::intToEthString(result()); }
};

inline QDebug operator<< (QDebug dbg, const TransactionCountResponse& transactionCount)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::TransactionCount(jsonrpc=%1; id=%2; transactionCountString=%3)")
                                    .arg(transactionCount.jsonRpc())
                                    .arg(transactionCount.id())
                                    .arg(transactionCount.transactionCountString()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ETH_TRANSACTIONCOUNT_H
