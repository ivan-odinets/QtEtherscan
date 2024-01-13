/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2023-2024 Ivan Odinets
 *
 * This file is part of QtEtherscan
 *
 * QtTelegramBot is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QtTelegramBot  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QtTelegramBot; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "./ether2supply.h"

namespace QtEtherscan {

Ether2Supply::Ether2Supply(const QJsonObject& jsonObject) :
    m_ethSupply(jsonObject.value("EthSupply").toString()),
    m_eth2Staking(jsonObject.value("Eth2Staking").toString()),
    m_burntFees(jsonObject.value("BurntFees").toString()),
    m_withdrawnTotal(jsonObject.value("WithdrawnTotal").toString())
{}

} //namespace QtEtherscan
