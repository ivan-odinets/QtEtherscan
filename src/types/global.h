/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2023 Ivan Odinets
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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

namespace QtEtherscan {

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

static QString tagToString(Tag tag)
{
    switch (tag) {
    case Latest:
        return QLatin1String("latest");
    case Pending:
        return QLatin1String("pending");
    case Earliest:
        return QLatin1String("earliest");
    }
    Q_ASSERT(false);
    return QString();
}

static qint32 constexpr      InvalidBlockNumber       = -1;
static QLatin1String const   InvalidBlockNumberString = QLatin1String("-1");

template<class C>
class JsonObjectsList : public QList<C>
{
public:
    JsonObjectsList() : QList<C>() {}
    JsonObjectsList(const QJsonArray& jsonArray) {
        foreach (const QJsonValue& jsonValue, jsonArray)
            this->append(C(jsonValue));
    }
    JsonObjectsList(const QJsonValue& jsonValue) :
        JsonObjectsList(jsonValue.toArray()) {}
};

}

#endif // GLOBAL_H
