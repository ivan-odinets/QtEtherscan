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

#include "./gasoracle.h"

namespace QtEtherscan {

GasOracle::GasOracle() :
    m_lastBlock(InvalidBlockNumber),
    m_safeGasPrice(0),
    m_proposedGasPrice(0),
    m_fastGasPrice(0),
    m_suggestedBaseFee(0)
{}

GasOracle::GasOracle(const QJsonObject& jsonObject) :
    m_lastBlock(jsonObject.value("LastBlock").toString(InvalidBlockNumberString).toLong()),
    m_safeGasPrice(jsonObject.value("SafeGasPrice").toString().toInt()),
    m_proposedGasPrice(jsonObject.value("ProposeGasPrice").toString().toInt()),
    m_fastGasPrice(jsonObject.value("FastGasPrice").toString().toInt()),
    m_suggestedBaseFee(jsonObject.value("suggestBaseFee").toString().toDouble()),
    m_gasUsedRatioString(jsonObject.value("gasUsedRatio").toString())
{}

QList<double> GasOracle::gasUsedRatio() const
{
    QList<double> result;

    foreach (const QString& part, m_gasUsedRatioString.split(","))
        result.append(part.toDouble());

    return result;
}

} //namespace QtEtherscan
