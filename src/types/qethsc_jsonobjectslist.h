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

#ifndef QT_ETHERSCAN_JSONOBJECTSLIST_H
#define QT_ETHERSCAN_JSONOBJECTSLIST_H

#include <QList>
#include <QJsonArray>
#include <QJsonValue>

namespace QtEtherscan {

/*! @class JsonObjectsList src/types/qethsc_jsonobjectslist.h
 *  @brief This is nothing more but a QList with some extra constructors.
 *  @details This class is needed to simplify creating collections of objects, which are returned by etherscam.io
 *           in JSON-serialized form. */

template<class C>
class JsonObjectsList : public QList<C>
{
public:
    /*! @brief Construct empty JsonObjectsList object. */
    JsonObjectsList() :
        QList<C>() {}

    /*! @brief Takes QJsonArray as an argument, and populates this JsonObjectsList by JSON-serialized objects stored
     *         in QJsonArray. */
    JsonObjectsList(const QJsonArray& jsonArray) {
        for (const QJsonValue& jsonValue : jsonArray)
            this->append(C(jsonValue));
    }

    /*! @brief Takes QJsonValue as an argument, converts it to QJsonArray and populates this JsonObjectsList by
     *         JSON-serialized objects stored in QJsonArray. If QJsonValue has anything but not QJsonArray - this
     *         constructor will create empty JsonObjectsList. */
    JsonObjectsList(const QJsonValue& jsonValue) :
        JsonObjectsList(jsonValue.toArray()) {}
};

} //namespace QtEtherscan

#endif // QT_ETHERSCAN_JSONOBJECTSLIST_H
