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

#ifndef ETH_RESPONSE_H
#define ETH_RESPONSE_H

#include <QJsonObject>
#include <QJsonValue>
#include <QString>

namespace QtEtherscan {

namespace Proxy {

/*! @class Response src/types/proxy/eth_response.h
 *  @brief This is basic class for objects returned by methods from "proxy" etherscan module.
 *  @details For detailed example check proxy example in examples directory (@ref examples/proxy/main.cpp).
 *  @example examples/proxy/main.cpp
 *
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_blocknumber
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getunclebyblocknumberandindex
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblocktransactioncountbynumber
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionbyhash
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactioncount
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_sendrawtransaction
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gettransactionreceipt
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_call
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getcode
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getstorageat
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_gasprice
 *  @see https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_estimategas */

class Response
{
public:
    enum {
        NoError      = 0,
        UnknownError = 1
    };

    Response();
    Response(const QJsonObject& jsonObject);
    Response(const QJsonValue& jsonValue) :
        Response(jsonValue.toObject()) {}

    /*! @brief Returns "jsonrpc" field from reply from etherscan.io. */
    QString   jsonRpc() const          { return m_jsonRpc; }

    /*! @brief Returns "id" field from reply from etherscan.io. */
    int       id() const               { return m_id; }

    /*! @brief Returns true if no error has occured on eth/proxy level */
    bool      noError() const          { return m_errorCode == NoError; }

    /*! @brief Returns integer code of error, which occured on eth/proxy level */
    int       errorCode() const        { return m_errorCode; }

    /*! @brief Returns error message, describing error occured on eth/proxy level. */
    QString   errorMessage() const     { return m_errorMessage; }

private:
    QString   m_jsonRpc;
    int       m_id;

    int       m_errorCode;
    QString   m_errorMessage;
};

/*! @class StringResponse src/types/proxy/eth_response.h
 *  @brief This class is basic class for simple string results of api methods from etherscan "proxy" module. */

class StringResponse : public Response
{
public:
    StringResponse();
    StringResponse(const QJsonObject& jsonObject);
    StringResponse(const QJsonValue& jsonValue) :
        StringResponse(jsonValue.toObject()) {}

    /*! @brief Returns QString with data, which was returned by method from "proxy" etherscan module. */
    QString   result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator  QString() const          { return m_result; }

private:
    QString   m_result;
};

/*! @class IntResponse src/types/proxy/eth_response.h
 *  @brief This class is basic class for simple integer results of api methods from etherscan "proxy" module. */

class IntResponse : public Response
{
public:
    IntResponse(int defaultValue = 0);
    IntResponse(const QJsonObject& jsonObject, int defaultValue = 0);

    /*! @brief Returns qint32 with data, which was returned by method from "proxy" etherscan module. */
    int       result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator  int() const              { return m_result; }

private:
    int m_result;
};

/*! @class ObjectResponse src/types/proxy/eth_response.h
 *  @brief This class is basic class for complex results of api methods from etherscan "proxy" module. */

template<class C>
class ObjectResponse : public Response
{
public:
    ObjectResponse() :
        Response() {}

    ObjectResponse(const QJsonObject& jsonObject) :
        Response(jsonObject)
    {
        if (jsonObject.contains("result"))
            m_result = C(jsonObject.value("result").toObject());
    }

    ObjectResponse(const QJsonValue& jsonValue) :
        ObjectResponse(jsonValue.toObject()) {}

    /*! @brief Returns object of type C, which was returned by method from "proxy" etherscan module.
    *  @details Object of this type is a representation of JSON field result from etherscan.io reply. */
    C         result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator C() const                 { return m_result; }

private:
    C m_result;
};

} //namespace Proxy

} //namespace QtEtherscan

#endif // ETH_RESPONSE_H
