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

#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>

#include <QNetworkProxy>
#include <QNetworkAccessManager>

namespace QtEtherscan {

/*!
 * @class Networking networking.h
 * @brief This class a bit simplifies communication with Etherscan API servers.
 *        For internal use only
 */

class Networking : public QObject
{
    Q_OBJECT
protected:
    friend class API;

    explicit Networking(QObject* parent = nullptr);
    ~Networking() {}

    void           setApiHost(const QString& host)         { m_host = host; }

    QByteArray     request(const QUrlQuery& params);

    void           setProxy(const QNetworkProxy& newProxy) { m_nam.setProxy(newProxy); }
    QNetworkProxy  proxy() const                           { return m_nam.proxy(); }

    quint32        requestTimeout() const                  { return m_timeout; };
    void           setRequestTimeout(quint32 newTimeout)   { m_timeout = newTimeout; };

private:
    QNetworkAccessManager    m_nam;
    QString                  m_host;
    quint32                  m_timeout;
};

} //namespace QtEtherscan

#endif // NETWORKING_H
