/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets
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

#include "qethsc_erc20tokenholding.h"

namespace QtEtherscan {

ERC20TokenHolding::ERC20TokenHolding()
{}

ERC20TokenHolding::ERC20TokenHolding(const QJsonObject& jsonObject) :
    m_tokenAddress           {jsonObject.value("TokenAddress").toString()},
    m_tokenName              {jsonObject.value("TokenName").toString()},
    m_tokenSymbol            {jsonObject.value("TokenSymbol").toString()},
    m_tokenQuantityString    {jsonObject.value("TokenQuantity").toString()},
    m_tokenDivisorString     {jsonObject.value("TokenDivisor").toString()}
{}

} // namespace QtEtherscan
