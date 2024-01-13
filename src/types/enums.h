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

#ifndef ENUMS_H
#define ENUMS_H

/*! @file src/types/global.h
 *  @brief This file contains all enums, global constants, etc which are used in QtEtherscan library.
 *
 * @todo Separate constants to file. */

#include <QString>

namespace QtEtherscan {

/*! @namespace QtEtherscan
 *  @brief Namespace containing everything used by QtEtherscan library. */

enum BlockType {
    BlocksType,
    UnclesType
};

enum ClientType {
    Geth,
    Parity,
};

enum Closest {
    Before,
    After
};

enum Sort {
    Asc,
    Desc
};

enum Syncmode {
    Archive,
    Default
};

enum Tag {
    Earliest,
    Pending,
    Latest
};

}

#endif // ENUMS_H
