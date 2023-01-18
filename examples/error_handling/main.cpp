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

#include <QCoreApplication>

#include <QDebug>
#include <QTimer>
#include <QThread>

#include "QtEtherscan.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtEtherscan::API etherscan;
    etherscan.setEtheriumNetwork(QtEtherscan::API::Mainnet);
    etherscan.setRequestTimeout(2000);

    //Giving wrong argument
    QtEtherscan::EtherBalance balance = etherscan.getEtherBalance("AAAA0x0x0x0x0x");
    if (etherscan.errorCode() == QtEtherscan::API::NoError) {
        qDebug() << "Continuing making problems";
    } else if (etherscan.errorCode() == QtEtherscan::API::InvalidAddressFormatError ){
        qDebug() << "AAAA0x0x0x0x0x is not etherium address";
    } else if (etherscan.errorCode() == QtEtherscan::API::NetworkError) {
        qDebug() << "Some network error occured...";
    }

    //Otherwise next loop will imidiately fail
    QThread::currentThread()->sleep(5);

    //To many requests per second
    for (int i = 0; i < 100; i++) {
        QtEtherscan::EtherBalance balance = etherscan.getEtherBalance("0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae");
        if (etherscan.errorCode() == QtEtherscan::API::NoError) {
            qDebug() << "Recieved balance: "<<balance;
        } else if (etherscan.errorCode() == QtEtherscan::API::MaxRateError) {
            qDebug() << "Too many requests, time to stop...";
            break;
        } else {
            qDebug() << "Some other error happened...";
        }
    }

    return a.exec();
}
