/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2021-2022 IvanOdinets
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

#include "networking.h"

#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include <QUrlQuery>

Networking::Networking(QObject* parent) :
    QObject(parent),m_timeout(0)
{}

QByteArray Networking::request(const QUrlQuery& query)
{
    QNetworkRequest req;
    QUrl url(m_host);
    url.setQuery(query);
    req.setUrl(url);

    QEventLoop waitLoop;

    if (m_timeout != 0)
        QTimer::singleShot(m_timeout,&waitLoop,&QEventLoop::quit);

    QNetworkReply *reply = m_nam.get(req);
    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);

    waitLoop.exec();
    if (reply->isRunning())
        reply->abort();

    QByteArray result = reply->readAll();

    reply->deleteLater();
    return result;
}
