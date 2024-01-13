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

/*! @file examples/balance_monitor/main.cpp
 *  @brief In this file basic usage of QtEtherscan is shown. */

#include <QCoreApplication>
#include <QDebug>
#include <QUrlQuery>

#include "QtEtherscan.h"

#define TOKEN "YOUR TOKEN HERE"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtEtherscan::API etherscan;

    etherscan.setApiKey(TOKEN);
    etherscan.setEtheriumNetwork(QtEtherscan::API::Mainnet);

    // For calling etherscan.io API methods you cen either simply invoke propper method from QtEtherscan::API class.
    QtEtherscan::EtherBalance balance = etherscan.getEtherBalance("0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae");
    qDebug() << balance;

    // Or alternatively you can use QtEherscan::API::call method
    QJsonObject result = etherscan.call({
        { QLatin1String("module"),     QLatin1String("account") },
        { QLatin1String("action"),     QLatin1String("balance") },
        { QLatin1String("tag"),        QLatin1String("latest") },
        { QLatin1String("address"),    "0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae" }
    });

    // And than accessing propper data using QJsonObject methods
    qDebug() << "wei="<<result.value("result").toString();

    // Or like this
    qDebug() << QtEtherscan::EtherBalance(result.value("result").toString());

    return a.exec();
}
