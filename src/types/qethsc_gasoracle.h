/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_GASORACLE_H
#define QT_ETHERSCAN_GASORACLE_H

#include <QDebug>
#include <QJsonObject>

#include "qethsc_constants.h"

namespace QtEtherscan {

/*! @class GasOracle src/types/qethsc_gasoracle.h
 *  @brief Object of this class is returned by API::getGasOracle method.
 *
 * @see https://docs.etherscan.io/api-endpoints/gas-tracker#get-gas-oracle */

class GasOracle
{
public:
    /*! @brief Default constructor. Consturcts invalid GasOracle object. */
    GasOracle();
    GasOracle(const QJsonObject& jsonObject);
    GasOracle(const QJsonValue& jsonValue) :
        GasOracle(jsonValue.toObject()) {}

    /*! @brief Returns true if this GasOracle object is valid and contains reasonable information. GasOracle object is considered
     *         to be valid if lastBlock() contains anything but not -1. */
    bool           isValid() const               { return m_lastBlock != InvalidBlockNumber; }

    /*! @brief Returns "LastBlock" field from reply from etherscan.io. */
    qint32         lastBlock() const             { return m_lastBlock; }

    /*! @brief Returns "SafeGasPrice" field from reply from etherscan.io. */
    qint16         safeGasPrice() const          { return m_safeGasPrice; }

    /*! @brief Returns "ProposeGasPrice" field from reply from etherscan.io. */
    qint16         proposedGasPrice() const      { return m_proposedGasPrice; };

    /*! @brief Returns "FastGasPrice" field from reply from etherscan.io. */
    qint16         fastGasPrice() const          { return m_fastGasPrice; }

    /*! @brief Returns "suggestBaseFee" field from reply from etherscan.io. */
    double         suggestedBaseFee() const      { return m_suggestedBaseFee; };

    /*! @brief Returns "gasUsedRatio" field from reply from etherscan.io in form of QString. */
    QString        gasUsedRatioString() const    { return m_gasUsedRatioString; }

    /*! @brief Returns "gasUsedRatio" field from reply from etherscan.io in form of QList<double>. */
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

#endif // QT_ETHERSCAN_GASORACLE_H
