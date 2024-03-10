/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2023-2024 Ivan Odinets <i_odinets@protonmail.com>
 *
 * This file is part of QtEtherscan
 *
 * QtTelegramBot is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * QtTelegramBot  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QtTelegramBot; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "./qethsc_etherprice.h"

namespace QtEtherscan {

EtherPrice::EtherPrice() :
    m_ethBtc{InvalidPrice},
    m_ethBtcTimeStamp{InvalidTimestamp},
    m_ethUsd{InvalidPrice},
    m_ethUsdTimeStamp{InvalidTimestamp}
{}

EtherPrice::EtherPrice(const QJsonObject& jsonObject) :
    m_ethBtc            {jsonObject.value("ethbtc").toString(InvalidPriceString).toDouble()                  },
    m_ethBtcTimeStamp   {jsonObject.value("ethbtc_timestamp").toString(InvalidTimestampString).toLongLong()  },
    m_ethUsd            {jsonObject.value("ethusd").toString(InvalidPriceString).toDouble()                  },
    m_ethUsdTimeStamp   {jsonObject.value("ethusd_timestamp").toString(InvalidTimestampString).toLongLong()  }
{}

} //namespace QtEtherscan
