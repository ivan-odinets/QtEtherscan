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

#ifndef QT_ETHERSCAN_ERC721TOKENINVENTORY_H
#define QT_ETHERSCAN_ERC721TOKENINVENTORY_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC721TokenInventory src/types/qethsc_erc721tokeninventory.h
 *  @brief A list of such objects is returned by API::getERC721TokenInventory method.
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-inventory-by-contract-address */

class ERC721TokenInventory
{
public:
    /*! @brief Default constructor. Constructs invalid ERC721TokenInventory object. */
    ERC721TokenInventory();
    ERC721TokenInventory(const QJsonObject& jsonObject);
    ERC721TokenInventory(const QJsonValue& jsonValue) :
        ERC721TokenInventory(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC721TokenInventory object is valid and contains reasonable information.
     *         ERC721TokenInventory object is considered to be valid if tokenAddress() contains non empty string. */
    bool      isValid() const          { return !m_tokenAddress.isEmpty(); }

    /*! @brief Returns "TokenAddress" field from etherscan.io reply. */
    QString   tokenAddress() const     { return m_tokenAddress; }

    /*! @brief Returns "TokenId" field from etherscan.io reply. */
    QString   tokenId() const          { return m_tokenId; }

private:
    QString m_tokenAddress;
    QString m_tokenId;
};

inline QDebug operator<< (QDebug dbg, const ERC721TokenInventory& erc721TokenInventory)
{
    dbg.nospace() << qUtf8Printable(QString("ERC721TokenInventory(tokenAddress=%1; tokenId=%2)")
                                    .arg(erc721TokenInventory.tokenAddress())
                                    .arg(erc721TokenInventory.tokenId()));

    return dbg.maybeSpace();
}

/*! @typedef ERC721TokenInventoryList
 *  @brief This is a list of ERC721TokenInventory objects. It is returned by API::getERC721TokenInventory method.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-inventory-by-contract-address */

typedef JsonObjectsList<ERC721TokenInventory> ERC721TokenInventoryList;

inline QDebug operator<<(QDebug dbg, const ERC721TokenInventoryList& erc721TokenInventoryList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC721TokenInventoryList(count=%1)")
                                    .arg(erc721TokenInventoryList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ERC721TOKENINVENTORY_H
