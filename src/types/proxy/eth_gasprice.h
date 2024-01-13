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

#ifndef ETH_GASPRICE_H
#define ETH_GASPRICE_H

#include "./eth_response.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class GasPriceResponse src/types/proxy/eth_gasprice.h
 *  @brief Object of this type is returned by API::eth_gasPrice method.
 *  @details All string values, returned by methods of this class are formatted in eth format.
 *
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#conventions
 * @see https://ethereum.org/en/developers/docs/apis/json-rpc/#eth_gasprice
 * @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gasprice */

class GasPriceResponse : public Response<QString>
{
public:
    GasPriceResponse() :
        Response<QString>() {}
    GasPriceResponse(const QJsonObject& jsonObject) :
        Response<QString>(jsonObject) {}
    GasPriceResponse(const QJsonValue& jsonValue) :
        GasPriceResponse(jsonValue.toObject()) {}

    /*! @brief Returns string containing current gas price in wei. */
    QString gasPriceString() const     { return result(); }
};

inline QDebug operator<< (QDebug dbg, const GasPriceResponse& gasPriceResponse)
{
    dbg.nospace() << qUtf8Printable(QString("Proxy::Block(gasPriceString=%1)")
                                    .arg(gasPriceResponse.gasPriceString()));

    return dbg.maybeSpace();
}

} // namespace Proxy

} // namespace QtEtherscan

#endif // ETH_GASPRICE_H
