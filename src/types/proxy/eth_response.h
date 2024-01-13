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

#include "./eth_helper.h"

namespace QtEtherscan {

namespace Proxy {

/*! @class Response src/types/proxy/eth_response.h
 *  @tparam C Specific type of response, which was returned by etherscan. Can be one of QString, QtEtherscan::Proxy::Block, QtEtherscan::Proxy::Transaction
 *  @brief This is template class for objects returned by methods from "proxy" etherscan module.
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

template<class C>
class Response
{
public:
    enum {
        NoError      = 0,
        UnknownError = 1
    };

    Response() :
        m_id(0),m_errorCode(UnknownError) {}

    Response(const QJsonObject& jsonObject) :
        m_jsonRpc(jsonObject.value("jsonrpc").toString()),
        m_id(jsonObject.value("id").toInt()),
        m_errorCode(NoError)
    {
        if (jsonObject.contains("result")) {
            m_errorCode = NoError;
            m_result = getResult(jsonObject);
        } else if (jsonObject.contains("error")) {
            QJsonObject errorObject = jsonObject.value("error").toObject();

            m_errorCode = errorObject.value("code").toInt();
            m_errorMessage = errorObject.value("message").toString();
        }
    }

    Response(const QJsonValue& jsonValue) :
        Response(jsonValue.toObject()) {}

    QString   jsonRpc() const          { return m_jsonRpc; }
    int       id() const               { return m_id; }

    /*! @brief Returns true if no error has occured on eth/proxy level */
    bool      noError() const          { return m_errorCode == NoError; }

    /*! @brief Returns integer code of error, which occured on eth/proxy level */
    int       errorCode() const        { return m_errorCode; }

    /*! @brief Returns errot message, describing error occured on eth/proxy level. */
    QString   errorMessage() const     { return m_errorMessage; }

    /*! @brief Returns object of type C, which was returned by method from "proxy" etherscan module.
     *  @details Object of this type is a representation of JSON field result from etherscan.io reply. */
    C         result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator C() const                 { return m_result; }

private:
    QString   m_jsonRpc;
    int       m_id;

    C         getResult(const QJsonObject& jsonObject) { return C(jsonObject.value("result").toObject()); }
    C         m_result;

    int       m_errorCode;
    QString   m_errorMessage;
};


/*! @class Response<qint32> src/types/proxy/eth_response.h
 *  @brief Specialization of a Response template class using qint32 as template parameter. */

template<>
class Response<qint32>
{
public:
    enum {
        NoError      = 0,
        UnknownError = 1
    };

    Response() :
        m_id(0),m_errorCode(UnknownError) {}

    Response(qint32 value) :
        m_id(value),m_errorCode(UnknownError) {}

    Response(const QJsonObject& jsonObject,qint32 defaultValue = 0) :
        m_jsonRpc(jsonObject.value("jsonrpc").toString()),
        m_id(jsonObject.value("id").toInt()),
        m_result(defaultValue),
        m_errorCode(NoError)
    {
        if (jsonObject.contains("result")) {
            m_errorCode = NoError;
            m_result = Helper::ethStringToInt32(jsonObject.value("result").toString());
        } else if (jsonObject.contains("error")) {
            QJsonObject errorObject = jsonObject.value("error").toObject();

            m_errorCode = errorObject.value("code").toInt();
            m_errorMessage = errorObject.value("message").toString();
        }
    }

    Response(const QJsonValue& jsonValue) :
        Response(jsonValue.toObject()) {}

    QString   jsonRpc() const          { return m_jsonRpc; }
    int       id() const               { return m_id; }

    /*! @copydoc Response::noError */
    bool      noError() const          { return m_errorCode == NoError; }

    /*! @copydoc Response::errorCode */
    int       errorCode() const        { return m_errorCode; }

    /*! @copydoc Response::errorMessage */
    QString   errorMessage() const     { return m_errorMessage; }

    /*! @brief Returns qint32 with data, which was returned by method from "proxy" etherscan module. */
    qint32    result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator  int() const              { return m_result; }

private:

    QString   m_jsonRpc;
    int       m_id;
    int       m_result;

    int       m_errorCode;
    QString   m_errorMessage;
};

/*! @class Response<QString> src/types/proxy/eth_response.h
 *  @brief Specialization of a Response template class using QString as template parameter. */

template<>
class Response<QString>
{
public:
    enum {
        NoError      = 0,
        UnknownError = 1
    };

    Response() :
        m_id(0),m_errorCode(UnknownError) {}

    Response(const QJsonObject& jsonObject) :
        m_jsonRpc(jsonObject.value("jsonrpc").toString()),
        m_id(jsonObject.value("id").toInt()),
        m_errorCode(NoError)
    {        
        if (jsonObject.contains("result")) {
            m_errorCode = NoError;
            m_result = jsonObject.value("result").toString();
        } else if (jsonObject.contains("error")) {
            QJsonObject errorObject = jsonObject.value("error").toObject();

            m_errorCode = errorObject.value("code").toInt();
            m_errorMessage = errorObject.value("message").toString();
        }
    }

    Response(const QJsonValue& jsonValue) :
        Response(jsonValue.toObject()) {}

    QString   jsonRpc() const          { return m_jsonRpc; }
    int       id() const               { return m_id; }

    /*! @copydoc Response::noError */
    bool      noError() const          { return m_errorCode == NoError; }

    /*! @copydoc Response::errorCode */
    int       errorCode() const        { return m_errorCode; }

    /*! @copydoc Response::errorMessage */
    QString   errorMessage() const     { return m_errorMessage; }

    /*! @brief Returns QString with data, which was returned by method from "proxy" etherscan module. */
    QString   result() const           { return m_result; }

    /*! @brief Cast operator, which is provided for convenience. */
    operator  QString() const          { return m_result; }

private:
    QString   m_jsonRpc;
    int       m_id;
    QString   m_result;

    int       m_errorCode;
    QString   m_errorMessage;
};

typedef Response<QString> StringResponse;

} //namespace Proxy

} //namespace QtEtherscan

//#include "eth_response.cpp"

#endif // ETH_RESPONSE_H
