/*
 **********************************************************************************************************************
 *
 * QtTelegramBot
 * Copyright (C) 2024 Ivan Odinets <i_odinets@protonmail.com>
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

#include "qethsc_etherhistoricalprice.h"

namespace QtEtherscan {

EtherHistoricalPrice::EtherHistoricalPrice() :
    m_timeStamp{InvalidTimestamp},
    m_historicalPrice{InvalidPrice}
{}

EtherHistoricalPrice::EtherHistoricalPrice(const QJsonObject& jsonObject) :
    m_utcDate           {jsonObject.value("UTCDate").toString()                                              },
    m_timeStamp         {jsonObject.value("unixTimeStamp").toString(InvalidTimestampString).toLongLong()     },
    m_historicalPrice   {jsonObject.value("value").toString(InvalidPriceString).toDouble()                   }
{}

} // namespace QtEtherscan
