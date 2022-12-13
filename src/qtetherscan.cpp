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

#include "qtetherscan.h"

#include <QUrlQuery>
#include <QJsonDocument>

/*
 **********************************************************************************************************************
 *
 * Configuration and setup
 *
 */

QtEtherscan::QtEtherscan(QObject *parent)
    : QObject(parent)
{
    setEtheriumNetwork(Mainnet);
}

QtEtherscan::QtEtherscan(const QString& apiKey,QObject* parent)
    : QObject(parent),m_apiKey(apiKey)
{
    setEtheriumNetwork(Mainnet);
}

void QtEtherscan::setEtheriumNetwork(Network etheriumNetwork)
{
    switch (etheriumNetwork) {
    case Mainnet:
        m_net.setApiHost("https://api.etherscan.io/api");
        return;
    case Goerli:
        m_net.setApiHost("https://api-goerli.etherscan.io/api");
        return;
    case Kovan:
        m_net.setApiHost("https://api-kovan.etherscan.io/api");
        return;
    case RInkeby:
        m_net.setApiHost("https://api-rinkeby.etherscan.io/api");
        return;
    case Ropsten:
        m_net.setApiHost("https://api-ropsten.etherscan.io/api");
        return;
    case Sepolia:
        m_net.setApiHost("https://api-sepolia.etherscan.io/api");
        return;
    }
    //Obvoisly some enum
    Q_ASSERT(false);
}

/*
 **********************************************************************************************************************
 *
 * Implemented API methods
 *
 */

EtherBalance QtEtherscan::getEtherBalance(const QString& address, Tag tag)
{
    QUrlQuery query({
        {"module","account"},
        {"action","balance"},
        {"address",address}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem("apikey",m_apiKey);

    switch (tag) {
    case Latest:
        query.addQueryItem("tag","latest");
        break;
    case Pending:
        query.addQueryItem("tag","pending");
        break;
    case Earliest:
        query.addQueryItem("tag","earliest");
        break;
    }

    return responseObject<EtherBalance>(makeApiCall(query));
}

AccountBalanceList QtEtherscan::getEtherBalance(const QStringList& addresses, Tag tag)
{
    QUrlQuery query({
        {"module","account"},
        {"action","balancemulti"},
        {"address",addresses.join(",")}
    });

    if (!m_apiKey.isEmpty()) query.addQueryItem("apikey",m_apiKey);

    switch (tag) {
    case Latest:
        query.addQueryItem("tag","latest");
        break;
    case Pending:
        query.addQueryItem("tag","pending");
        break;
    case Earliest:
        query.addQueryItem("tag","earliest");
        break;
    }

    return responseObject<AccountBalanceList>(makeApiCall(query));
}

/*
 **********************************************************************************************************************
 *
 * Internal methods
 *
 */

QJsonObject QtEtherscan::makeApiCall(const QUrlQuery& urlQuery)
{
    return QJsonDocument::fromJson(m_net.request(urlQuery)).object();
}

template<class C>
C QtEtherscan::responseObject(const QJsonObject& response)
{
    m_errorCode = getErrorCode(response);
    return m_errorCode == NoError ? C(response.value("result")) : C();
}

QtEtherscan::Error QtEtherscan::getErrorCode(const QJsonObject& jsonObject)
{
    if (jsonObject.isEmpty())
        return NetworkError;

    if (jsonObject.value("status").toString() == QLatin1String("1"))
        return NoError;

    QString errorString = jsonObject.value("result").toString();
    if (errorString.contains("Max rate limit reached"))
        return MaxRateError;

    if (errorString.contains("Invalid API Key"))
        return InvalidAPIKeyError;

    if (errorString.contains("Invalid address format"))
        return InvalidAddressFormatError;

    if (errorString.contains("Missing Or invalid Module"))
        return InvalidModuleNameError;

    if (errorString.contains("Missing Or invalid Action"))
        return InvalidActionNameError;

    qDebug() << "Etherscan API Error: "<<errorString;
    return UnknownError;
}
