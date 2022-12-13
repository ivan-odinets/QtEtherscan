/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2021-2022 IvanOdinets
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

#ifndef QTETHERSCAN_H
#define QTETHERSCAN_H

#include <QObject>

#include "./networking.h"

#include "./types/accountbalance.h"
#include "./types/etherbalance.h"

/*!
 * @class QtEtherscan src/qtetherscan.h
 * @brief QtEtherscan class provides interface to communiocate with Etherscan servers
 */

class QtEtherscan : public QObject
{
    Q_OBJECT
public:
    /*! @brief This enum describes etherium networks supported by etherscan */
    enum Network {
        Mainnet,   /*!< @brief Mainnet. Requests will go to URL https://api.etherscan.io/api */
        Goerli,    /*!< @brief Goerli. Requests will go to URL https://api-goerli.etherscan.io/api */
        Kovan,     /*!< @brief Kovan. Requests will go to URL https://api-kovan.etherscan.io/api */
        RInkeby,   /*!< @brief RInkeby. Requests will go to URL https://api-rinkeby.etherscan.io/api */
        Ropsten,   /*!< @brief Ropsten. Requests will go to URL https://api-ropsten.etherscan.io/api */
        Sepolia    /*!< @brief Sepolia. Requests will go to URL https://api-sepolia.etherscan.io/api */
    };

    /*! @brief This enum holds information about what exactly error happened */
    enum Error {
        NoError,                       /*!< @brief If the request was successfuul */
        NetworkError,                  /*!< @brief If during requestb some networking error happened */

        MaxRateError,                  /*!< @brief Corresponds to "result":"Max rate limit reached, please use API
                                        *          Key for higher rate limit */
        InvalidAPIKeyError,            /*!< @brief Corresponds to "result":"Invalid API Key"*/
        InvalidAddressFormatError,     /*!< @brief Corresponds to "result":"Error! Invalid address format" */

        InvalidModuleNameError,        /*!< @brief Corresponds to "result":"Error! Missing Or invalid Module name" */
        InvalidActionNameError,        /*!< @brief Corresponds to "result":"Error! Missing Or invalid Action name" */

        UnknownError                   /*!< @brief Corresponds to any other error which have happened */
    };

    explicit QtEtherscan(QObject *parent = nullptr);
    explicit QtEtherscan(const QString& apiKey, QObject *parent = nullptr);
    ~QtEtherscan() {}

    /*! @brief This method can be used to set Etherscan API token
     *  @details After setting new api key - all requests made to Etherscan servers will be done using this key. For
     *           creating those keys check [etherscan docs](https://docs.etherscan.io/getting-started/viewing-api-usage-statistics#creating-an-api-key)
     *  @param QString newApiKey*/
    void           setApiKey(const QString& newApiKey)     { m_apiKey = newApiKey; }

    /*! @brief This method can be used to configure proxy, through which communication with etherscan servers will be done
     *  @param QNetworkProxy newProxy - new proxy configuration */
    void           setProxy(const QNetworkProxy& newProxy) { m_net.setProxy(newProxy); }

    /*! @brief This method can be used to get information about currently configured proxy.
     *  @return QNetworkProxy object, representing current proxy configuration */
    QNetworkProxy  proxy() const                           { return m_net.proxy(); }

    /*! @brief This method allows to setup a timeout for requests to Etherscan servers.
     *  @param quint32 timeout (in mseconds) after which request will be aborted. Pass 0 to disable timeout */
    void setRequestTimeout(quint32 msec)                   { m_net.setRequestTimeout(msec); }

    /*! @brief This method returns information about timeout */
    quint32 requestTimeout() const                         { return m_net.requestTimeout(); }

    /*! @brief This method can be used to setup with what Etherium network this instantce of QtEtherscan object will interact.
     *         By default QtEtherscan object will use Mainnet as a "target" network
     *  @param etheriumNetwork represented by one of the values from enum QtEtherscan::Network */
    void setEtheriumNetwork(Network etheriumNetwork);

    /*! @brief This method allows to check with what Etherium network this instantce of QtEtherscan object will interact
     *  @returns QtEtherscan::Network value */
    Network etheriumNetwork() const                        { return m_activeEtheriumNetwork; }

    /*! @brief This method can be used to get information about errors related to Etherscan API
     *  @return Error::NoError on success and any other value - if failed. */
    Error       errorCode() const                          { return m_errorCode; }

    /*! @brief This enum is representign an argument needed for some methods (like QtEtherscan::getEtherBalance) */
    enum Tag {
        Earliest,
        Pending,
        Latest
    };

    /*! @brief Returns the Ether balance of a given address.
     *  @returns EtherBalance object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-a-single-address */
    EtherBalance getEtherBalance(const QString& address, Tag tag = Latest);

    /*! @brief Returns the balance of the accounts from a list of addresses.
     *  @returns AccountBalanceList object
     *  @see https://docs.etherscan.io/api-endpoints/accounts#get-ether-balance-for-multiple-addresses-in-a-single-call */
    AccountBalanceList getEtherBalance(const QStringList& addresses, Tag tag = Latest);

private:
    QJsonObject makeApiCall(const QUrlQuery& urlQuery);

    template<class C>
    C responseObject(const QJsonObject& response);
    Error getErrorCode(const QJsonObject& response);

    Networking     m_net;
    QString        m_apiKey;
    Network        m_activeEtheriumNetwork;

    Error          m_errorCode;
    QString        m_errorMessage;
};

#endif // QTETHERSCAN_H
