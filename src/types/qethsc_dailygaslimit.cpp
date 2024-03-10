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

#include "qethsc_dailygaslimit.h"

namespace QtEtherscan {

DailyGasLimit::DailyGasLimit() :
    m_timeStamp{InvalidTimestamp},
    m_gasLimit{0}
{}

DailyGasLimit::DailyGasLimit(const QJsonObject& jsonObject) :
    m_utcDate      {jsonObject.value("UTCDate").toString()                                              },
    m_timeStamp    {jsonObject.value("unixTimeStamp").toString(InvalidTimestampString).toLongLong()     },
    m_gasLimit     {jsonObject.value("gasLimit").toString().toLongLong()                                }
{}

} // namespace QtEtherscan
