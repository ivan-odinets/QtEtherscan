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

#include "qethsc_tokeninfo.h"

namespace QtEtherscan {

TokenInfo::TokenInfo()
{}

TokenInfo::TokenInfo(const QJsonObject& jsonObject) :
    m_contractAddress        {jsonObject.value("contractAddress").toString()   },
    m_tokenName              {jsonObject.value("tokenName").toString()         },
    m_symbol                 {jsonObject.value("symbol").toString()            },
    m_divisorString          {jsonObject.value("divisor").toString()           },
    m_tokenTypeString        {jsonObject.value("tokenType").toString()         },
    m_totalSupply            {jsonObject.value("totalSupply").toString()       },
    m_blueCheckmark          {jsonObject.value("blueCheckmark").toString()     },
    m_description            {jsonObject.value("description").toString()       },
    m_website                {jsonObject.value("website").toString()           },
    m_email                  {jsonObject.value("email").toString()             },
    m_blog                   {jsonObject.value("blog").toString()              },
    m_reddit                 {jsonObject.value("reddit").toString()            },
    m_slack                  {jsonObject.value("slack").toString()             },
    m_facebook               {jsonObject.value("facebook").toString()          },
    m_twitter                {jsonObject.value("twitter").toString()           },
    m_bitcointalk            {jsonObject.value("bitcointalk").toString()       },
    m_github                 {jsonObject.value("github").toString()            },
    m_telegram               {jsonObject.value("telegram").toString()          },
    m_wechat                 {jsonObject.value("wechat").toString()            },
    m_linkedin               {jsonObject.value("linkedin").toString()          },
    m_discord                {jsonObject.value("discord").toString()           },
    m_whitepaper             {jsonObject.value("whitepaper").toString()        },
    m_tokenPriceUSDString    {jsonObject.value("tokenPriceUSD").toString()     }
{}

} // namespace QtEtherscan
