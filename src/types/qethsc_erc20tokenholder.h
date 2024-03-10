/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_ERC20TOKENHOLDER_H
#define QT_ETHERSCAN_ERC20TOKENHOLDER_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC20TokenHolder src/types/qethsc_erc20tokenholder.h
 *  @brief A list of such objects is returned by API::getERC20TokenHolders method.
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-token-holder-list-by-contract-address */

class ERC20TokenHolder
{
public:
    /*! @brief Default constructor. Constructs invalid ERC20TokenHolder object. */
    ERC20TokenHolder();
    ERC20TokenHolder(const QJsonObject& jsonObject);
    ERC20TokenHolder(const QJsonValue& jsonValue) :
        ERC20TokenHolder(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC20TokenHolder object is valid and contains reasonable information.
     *         ERC20TokenHolder object is considered to be valid if both of its fields are containing non-empty QString */
    bool      isValid() const     { return !(m_tokenHolderAddress.isEmpty() || m_tokenHolderAddress.isEmpty()); }

    /*! @brief Returns "TokenHolderAddress" field from etherscan.io reply. */
    QString tokenHolderAddress() const           { return m_tokenHolderAddress; }

    /*! @brief Returns "TokenHolderQuantity" field from etherscan.io reply. */
    QString tokenHolderQuantityString() const    { return m_tokenHolderQuantityString; }

private:
    QString m_tokenHolderAddress;
    QString m_tokenHolderQuantityString;
};

inline QDebug operator<< (QDebug dbg, const ERC20TokenHolder& tokenTransferEvent)
{
    dbg.nospace() << qUtf8Printable(QString("ERC20TokenHolder(tokenHolderAddress=%1; tokenHolderQuantityString=%2)")
                                    .arg(tokenTransferEvent.tokenHolderAddress())
                                    .arg(tokenTransferEvent.tokenHolderQuantityString()));

    return dbg.maybeSpace();
}

/*! @typedef ERC20TokenHolderList
 *  @brief This is a list of ERC20TokenHolder objects. It is returned by API::getERC20TokenHolders method.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-token-holder-list-by-contract-address */

typedef JsonObjectsList<ERC20TokenHolder> ERC20TokenHolderList;

inline QDebug operator<<(QDebug dbg, const ERC20TokenHolderList& erc20TokenHolderList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC20TokenHolderList(count=%1)")
                                    .arg(erc20TokenHolderList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QETHSC_ERC20TOKENHOLDER_H
