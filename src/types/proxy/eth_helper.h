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

#ifndef ETH_HELPER_H
#define ETH_HELPER_H

#include <QString>
#include <QDebug>

namespace QtEtherscan {

/*! @namespace QtEtherscan::Proxy Proxy
 *  @brief Namespace containing all classes, enums, etc. used methods implementing etherscan API from proxy module. */

namespace Proxy {

/*! @class Helper src/types/proxy/eth_helper.h
 *  @brief This class has several static members, for converting inegers to QString in eth format and other way. */

class Helper {
public:
    template<typename I>
    static QString intToEthString(I integer)
    {
        return QLatin1String("0x") + QString::number(integer,16);
    }

    static qint32 ethStringToInt32(QString ethString)
    {
        if (!ethString.startsWith("0x"))
            return -1;

        ethString.remove("0x");

        bool ok = false;
        int result = ethString.toInt(&ok,16);
        if (!ok)
            return -1;

        return result;
    }

    static qint64 ethStringToInt64(QString ethString)
    {
        if (!ethString.startsWith("0x"))
            return -1;

        ethString.remove("0x");

        bool ok = false;
        int result = ethString.toLongLong(&ok,16);
        if (!ok)
            return -1;

        return result;
    }
};

} // namespace Proxy

} // namespace QtEtherscan

#endif // ETH_HELPER_H
