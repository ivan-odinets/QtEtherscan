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

#include "eth_transaction.h"

namespace QtEtherscan {

namespace Proxy {

Transaction::Transaction() :
    m_blockNumber(InvalidBlockNumber),
    m_gas(0)
{}

Transaction::Transaction(const QJsonObject& jsonObject) :
    m_blockHash         {jsonObject.value("blockHash").toString()                                            },
    m_blockNumber       {jsonObject.value("blockNumber").toString(InvalidBlockNumberString).toInt(nullptr,0) },
    m_from              {jsonObject.value("from").toString()                                                 },
    m_gas               {jsonObject.value("gas").toString().toULongLong(nullptr,0)                           },
    m_gasPrice          {jsonObject.value("gasPrice").toString()                                             },
    m_hash              {jsonObject.value("hash").toString()                                                 },
    m_input             {jsonObject.value("input").toString()                                                },
    m_nonce             {jsonObject.value("nonce").toString()                                                },
    m_to                {jsonObject.value("to").toString()                                                   },
    m_transactionIndex  {jsonObject.value("transactionIndex").toString()                                     },
    m_value             {jsonObject.value("value").toString()                                                },
    m_v                 {jsonObject.value("v").toString()                                                    },
    m_r                 {jsonObject.value("r").toString()                                                    },
    m_s                 {jsonObject.value("s").toString()                                                    }
{}

} // namespace Proxy

} // namespace QtEtherscan
