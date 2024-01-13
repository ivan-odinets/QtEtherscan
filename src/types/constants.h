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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace QtEtherscan {

static qint32 constexpr      InvalidBlockNumber       = -1;
static QLatin1String const   InvalidBlockNumberString = QLatin1String("-1");

static qint32 constexpr      InvalidBlockSize         = -1;
static QLatin1String const   InvalidBlockSizeString   = QLatin1String("-1");

static qint32 constexpr      InvalidTransactionCount  = -1;
static QLatin1String const   InvalidTransactionCountString = QLatin1String("-1");

static double constexpr      InvalidPrice = -1;

static quint32 constexpr     InvalidNodeCount = 0;

} //namespace QtEtherscan

#endif // CONSTANTS_H
