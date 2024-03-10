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

#ifndef QT_ETHERSCAN_CONTRACTCREATOR_H
#define QT_ETHERSCAN_CONTRACTCREATOR_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ContractCreator src/types/qethsc_contractcreator.h
 *  @brief A list of such objects is returned by API::getContractCreatorList method.
 *
 * @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-creator-and-creation-tx-hash */

class ContractCreator
{
public:
    /*! @brief Default constructor. Constructs invalid ContractCreator object. */
    ContractCreator();
    ContractCreator(const QJsonObject& jsonObject);
    ContractCreator(const QJsonValue& jsonValue) :
        ContractCreator(jsonValue.toObject()) {}

    /*! @brief Returns true if this ContractCreator object is valid and contains reasonable information.
     *         ContractCreator object is considered to be valid if contractCreator() contains non empty QString. */
    bool      isValid() const       { return !m_contractCreator.isEmpty(); }

    /*! @brief Returns "contractAddress" field from etherscan.io response. */
    QString contractAddress() const { return m_contractAddress; }

    /*! @brief Returns "contractCreator" field from etherscan.io response. */
    QString contractCreator() const { return m_contractCreator; }

    /*! @brief Returns "txHash" field from etherscan.io response. */
    QString txHash() const          { return m_txHash; }

private:
    QString m_contractAddress;
    QString m_contractCreator;
    QString m_txHash;
};

inline QDebug operator<< (QDebug dbg, const ContractCreator& contractCreator)
{
    dbg.nospace() << qUtf8Printable(QString("ContractCreator(contractAddress=%1; contractCreator=%2; txHash=%3)")
                                    .arg(contractCreator.contractAddress())
                                    .arg(contractCreator.contractCreator())
                                    .arg(contractCreator.txHash()));

    return dbg.maybeSpace();
}

/*! @typedef ContractCreatorList
 *  @brief This is a list of ContractCreator objects. It is returned by API::getContractCreatorList method. Nothing more
 *         than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-creator-and-creation-tx-hash */

typedef JsonObjectsList<ContractCreator> ContractCreatorList;

inline QDebug operator<<(QDebug dbg, const ContractCreatorList& contractCreatorList)
{
    dbg.nospace() << qUtf8Printable(QString("ContractCreatorList(count=%1)")
                                    .arg(contractCreatorList.count()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_CONTRACTCREATOR_H
