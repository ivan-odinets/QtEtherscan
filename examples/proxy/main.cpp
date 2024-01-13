/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2023 Ivan Odinets
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

/*! @file examples/proxy/main.cpp
 *  @brief In this file it is shown how to user methods from "proxy" etherscan.io module. */

#include <QCoreApplication>
#include <QDebug>

#include "QtEtherscan.h"

#define TOKEN "YOUR TOKEN HERE"

#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtEtherscan::API etherscan;

    // Setting API token
    // etherscan.setApiKey(TOKEN);

    // Setting etherium network
    etherscan.setEtheriumNetwork(QtEtherscan::API::Mainnet);

    // Simple usage. Example from docs.etherscan.io
    // https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_getblockbynumber
    QtEtherscan::Proxy::Block block = etherscan.eth_getBlockByNumber("0x10d4f");
    qDebug() << block;

    // Small delay to avoid recieving MaxRateError
    QThread::currentThread()->sleep(5);

    // We can also pass block number as normal integer
    qDebug() << etherscan.eth_getBlockByNumber(0x10d4f).block();

    // Handling proxy-level errors
    QtEtherscan::Proxy::BlockResponse blockResponse = etherscan.eth_getBlockByNumber("0x0000011111111111");
    if (blockResponse.noError())
        qDebug() << "We have provided wrong data, so we have an error";
    else
        qDebug() << blockResponse;

    // For simulating etherscan.io-level error - we will set wrong proxy.
    etherscan.setProxy(QNetworkProxy(QNetworkProxy::HttpProxy,"localhost",11111));

    blockResponse = etherscan.eth_getBlockByNumber("0x10d4f");
    switch (etherscan.errorCode()) {
    case QtEtherscan::API::NetworkError:
        qDebug() << "We will see network error, because the proxy is wrong. Is it?";
        qDebug() << "blockResponse.noError() = "<<blockResponse.noError();
        break;
    default:
        qDebug() << "If the proxy was setup incorrectly - we will not see this.";
        break;
    }

    return a.exec();
}
