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

#ifndef GASORACLE_H
#define GASORACLE_H

#include <QDebug>
#include <QJsonObject>

#include "./constants.h"

namespace QtEtherscan {

/*! @class GasOracle src/types/gasoracle.h
 *  @brief Object of this class is returned by API::getGasOracle method.
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-gas-oracle */

class GasOracle
{
public:
    GasOracle();
    GasOracle(const QJsonObject& jsonObject);
    GasOracle(const QJsonValue& jsonValue) :
        GasOracle(jsonValue.toObject()) {}

    /*! @brief Returns true if this GasOracle object is valid and contains reasonable information. GasOracle object is considered
     *         to be valid if lastBlock() contains anything but not -1. */
    bool           isValid() const               { return m_lastBlock != InvalidBlockNumber; }

    qint32         lastBlock() const             { return m_lastBlock; }
    qint16         safeGasPrice() const          { return m_safeGasPrice; }
    qint16         proposedGasPrice() const      { return m_proposedGasPrice; };
    qint16         fastGasPrice() const          { return m_fastGasPrice; }
    double         suggestedBaseFee() const      { return m_suggestedBaseFee; };

    QString        gasUsedRatioString() const    { return m_gasUsedRatioString; }
    QList<double>  gasUsedRatio() const;

private:
    qint32  m_lastBlock;
    qint16  m_safeGasPrice;
    qint16  m_proposedGasPrice;
    qint16  m_fastGasPrice;
    double  m_suggestedBaseFee;

    QString m_gasUsedRatioString;
};

inline QDebug operator<< (QDebug dbg, const GasOracle& gasOracle)
{
    dbg.nospace() << qUtf8Printable(QString("GasOracle(lastBlock=%1; safeGasPrice=%2; proposedGasPrice=%3; fastGasPrice=%4; suggestedBaseFee=%5)")
                                    .arg(gasOracle.lastBlock())
                                    .arg(gasOracle.safeGasPrice())
                                    .arg(gasOracle.proposedGasPrice())
                                    .arg(gasOracle.fastGasPrice())
                                    .arg(gasOracle.suggestedBaseFee()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // GASORACLE_H
