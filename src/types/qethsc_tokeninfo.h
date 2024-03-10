/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_TOKENINFO_H
#define QT_ETHERSCAN_TOKENINFO_H

#include <QDebug>
#include <QJsonObject>

namespace QtEtherscan {

/*! @class TokenInfo src/types/qethsc_tokeninfo.h
 *  @brief Object of this class is returned by API::getTokenInfo
 *
 * @see https://docs.etherscan.io/api-endpoints/tokens#get-token-info-by-contractaddress */

class TokenInfo
{
public:
    /*! @brief Default constructor. Constructs invalid TokenInfo object. */
    TokenInfo();
    TokenInfo(const QJsonObject& jsonObject);
    TokenInfo(const QJsonValue& jsonValue) :
        TokenInfo(jsonValue.toObject()) {}

    /*! @brief Returns true if this TokenInfo object is valid and contains reasonable information. TokenInfo object is
     *         considered to be valid if contractAddress() contains non empty string. */
    bool           isValid() const          { return !m_contractAddress.isEmpty(); }

    /*! @brief Returns "contractAddress" field from etherscan.io response. */
    QString contractAddress() const         { return m_contractAddress; }

    /*! @brief Returns "contractAddress" field from etherscan.io response. */
    QString tokenName() const               { return m_tokenName; }

    /*! @brief Returns "symbol" field from etherscan.io response. */
    QString symbol() const                  { return m_symbol; }

    /*! @brief Returns "divisor" field from etherscan.io response in form of QString. */
    QString divisorString() const           { return m_divisorString; }

    /*! @brief Returns "tokenType" field from etherscan.io response in form of QString. */
    QString tokenTypeString() const         { return m_tokenTypeString; }

    /*! @brief Returns "totalSupply" field from etherscan.io response. */
    QString totalSupply() const             { return m_totalSupply; }

    /*! @brief Returns "blueCheckmark" field from etherscan.io response. */
    QString blueCheckmarkString() const     { return m_blueCheckmark; }

    /*! @brief Returns "description" field from etherscan.io response. */
    QString description() const             { return m_description; }

    /*! @brief Returns "website" field from etherscan.io response. */
    QString website() const                 { return m_website; }

    /*! @brief Returns "email" field from etherscan.io response. */
    QString email() const                   { return m_email; }

    /*! @brief Returns "blog" field from etherscan.io response. */
    QString blog() const                    { return m_blog; }

    /*! @brief Returns "reddit" field from etherscan.io response. */
    QString reddit() const                  { return m_reddit; }

    /*! @brief Returns "slack" field from etherscan.io response. */
    QString slack() const                   { return m_slack; }

    /*! @brief Returns "facebook" field from etherscan.io response. */
    QString facebook() const                { return m_facebook; }

    /*! @brief Returns "twitter" field from etherscan.io response. */
    QString twitter() const                 { return m_twitter; }

    /*! @brief Returns "bitcointalk" field from etherscan.io response. */
    QString bitcointalk() const             { return m_bitcointalk; }

    /*! @brief Returns "bitcointalk" field from etherscan.io response. */
    QString github() const                  { return m_github; };

    /*! @brief Returns "telegram" field from etherscan.io response. */
    QString telegram() const                { return m_telegram; }

    /*! @brief Returns "wechat" field from etherscan.io response. */
    QString wechat() const                  { return m_wechat; }

    /*! @brief Returns "linkedin" field from etherscan.io response. */
    QString linkedin() const                { return m_linkedin; }

    /*! @brief Returns "discord" field from etherscan.io response. */
    QString discord() const                 { return m_discord; }

    /*! @brief Returns "whitepaper" field from etherscan.io response. */
    QString whitepaper() const              { return m_whitepaper; }

    /*! @brief Returns "tokenPriceUSD" field from etherscan.io response in form of QString. */
    QString tokenPriceUSDString() const     { return m_tokenPriceUSDString; }

private:
    QString m_contractAddress;
    QString m_tokenName;
    QString m_symbol;
    QString m_divisorString;
    QString m_tokenTypeString;
    QString m_totalSupply;
    QString m_blueCheckmark;
    QString m_description;
    QString m_website;
    QString m_email;
    QString m_blog;
    QString m_reddit;
    QString m_slack;
    QString m_facebook;
    QString m_twitter;
    QString m_bitcointalk;
    QString m_github;
    QString m_telegram;
    QString m_wechat;
    QString m_linkedin;
    QString m_discord;
    QString m_whitepaper;
    QString m_tokenPriceUSDString;
};

} // namespace QtEtherscan

#endif // TOKENINFO_H
