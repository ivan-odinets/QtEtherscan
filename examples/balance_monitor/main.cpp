/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2015 Moritz Sternemann
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

#include <QCoreApplication>
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

#include <QDebug>

#include "QtEtherscan.h"

#define TOKEN "YOUR TOKEN HERE"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QtEtherscan etherscan;

    etherscan.setApiKey(TOKEN);
    etherscan.setEtheriumNetwork(QtEtherscan::Mainnet);
    EtherBalance balance = etherscan.getEtherBalance("0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae");
    qDebug() << balance;

    qDebug() << "Multimple accounts:";
    AccountBalanceList accounts = etherscan.getEtherBalance(
        { "0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae","0x63a9975ba31b0b9626b34300f7f627147df1f526"});

    foreach (AccountBalance balance, accounts)
        qDebug() << balance;

    return a.exec();
}
