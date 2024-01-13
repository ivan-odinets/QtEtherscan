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

#ifndef CONTRACTCREATOR_H
#define CONTRACTCREATOR_H

#include <QDebug>
#include <QJsonObject>

#include "./jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ContractCreator src/types/contractcreator.h
 *  @brief A list of such objects is returned by API::getContractCreatorList method.
 *
 * @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-creator-and-creation-tx-hash */

class ContractCreator
{
public:
    ContractCreator();
    ContractCreator(const QJsonObject& jsonObject);
    ContractCreator(const QJsonValue& jsonValue) :
        ContractCreator(jsonValue.toObject()) {}

    QString contractAddress() const { return m_contractAddress; }
    QString contractCreator() const { return m_contractCreator; }
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

/*! @typedef ContractCreatorList src/types/contractcreator.h
 *  @brief This is a list of ContractCreator objects. It is returned by API::getContractCreatorList method. Nothing more
 *         than a QList with some extra constructors (JsonObjectList).
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

#endif // CONTRACTCREATOR_H
