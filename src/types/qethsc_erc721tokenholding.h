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

#ifndef QT_ETHERSCAN_ERC721TOKENHOLDING_H
#define QT_ETHERSCAN_ERC721TOKENHOLDING_H

#include <QDebug>
#include <QJsonObject>

#include "./qethsc_jsonobjectslist.h"

namespace QtEtherscan {

/*! @class ERC721TokenHolding src/types/qethsc_erc721tokenholding.h
 *  @brief A list of such objects is returned by API::getERC721TokenHolding method.
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-holding */

class ERC721TokenHolding
{
public:
    /*! @brief Default constructor. Constructs invalid ERC721TokenHolding object. */
    ERC721TokenHolding();
    ERC721TokenHolding(const QJsonObject& jsonObject);
    ERC721TokenHolding(const QJsonValue& jsonValue) :
        ERC721TokenHolding(jsonValue.toObject()) {}

    /*! @brief Returns true if this ERC721TokenHolding object is valid and contains reasonable information.
     *         ERC721TokenHolding object is considered to be valid if tokenAddress() field is containing non-empty string. */
    bool isValid() const                    { return !m_tokenAddress.isEmpty(); }

    /*! @brief Returns "TokenAddress" field from etherscan.io reply. */
    QString tokenAddress() const            { return m_tokenAddress; }

    /*! @brief Returns "TokenName" field from etherscan.io reply. */
    QString tokenName() const               { return m_tokenName; }

    /*! @brief Returns "TokenSymbol" field from etherscan.io reply. */
    QString tokenSymbol() const             { return m_tokenSymbol; }

    /*! @brief Returns "TokenQuantity" field from etherscan.io reply. */
    QString tokenQuantityString() const     { return m_tokenQuantityString; }

private:
    QString m_tokenAddress;
    QString m_tokenName;
    QString m_tokenSymbol;
    QString m_tokenQuantityString;
};

/*! @typedef ERC721TokenHoldingList
 *  @brief This is a list of ERC721TokenHolding objects. It is returned by API::getERC721TokenHolding method.
 *         Nothing more than a QList with some extra constructors (JsonObjectsList).
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-address-erc721-token-holding */

typedef JsonObjectsList<ERC721TokenHolding> ERC721TokenHoldingList;

inline QDebug operator<<(QDebug dbg, const ERC721TokenHoldingList& erc721TokenHoldingList)
{
    dbg.nospace() << qUtf8Printable(QString("ERC721TokenHoldingList(count=%1)")
                                    .arg(erc721TokenHoldingList.count()));

    return dbg.maybeSpace();
}

} // namespace QtEtherscan

#endif // QT_ETHERSCAN_ERC721TOKENHOLDING_H
