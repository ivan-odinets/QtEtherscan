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

#ifndef ETHER2SUPPLY_H
#define ETHER2SUPPLY_H

#include "./ether.h"

namespace QtEtherscan {

/*! @class Ether2Supply src/types/ether2supply.h
 *  @brief Object of this class is returned by API::getTotalSupplyOfEther2 method.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats-1#get-total-supply-of-ether-2 */

class Ether2Supply
{
public:
    Ether2Supply() {}
    Ether2Supply(const QJsonObject& jsonObject);
    Ether2Supply(const QJsonValue& jsonValue) :
        Ether2Supply(jsonValue.toObject()) {}

    /*! @brief Returns true if this Ether2Supply object is valid and contains reasonable information. Ether2Supply object
     *         is considered to be valid if ethSupply().isValid() returns true. Check Ether::isValid() method. */
    bool      isValid() const     { return m_ethSupply.isValid(); }

    Ether     ethSupply() const        { return m_ethSupply; }
    Ether     eth2Staking() const      { return m_eth2Staking; }
    Ether     burntFees() const        { return m_burntFees; }
    Ether     withdrawnTotal() const   { return m_withdrawnTotal; }

private:
    Ether     m_ethSupply;
    Ether     m_eth2Staking;
    Ether     m_burntFees;
    Ether     m_withdrawnTotal;
};

inline QDebug operator<< (QDebug dbg, const Ether2Supply& ether2Supply)
{
    dbg.nospace() << qUtf8Printable(QString("Ether2Supply(ethSupply=%1 ETH; eth2Staking=%2 ETH; burntFees=%3 ETH)")
                                    .arg(ether2Supply.ethSupply().eth())
                                    .arg(ether2Supply.eth2Staking().eth())
                                    .arg(ether2Supply.burntFees().eth()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ETHER2SUPPLY_H
