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

#ifndef CONTRACTEXECUTIONSTATUS_H
#define CONTRACTEXECUTIONSTATUS_H

#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

class ContractExecutionStatus
{
public:
    ContractExecutionStatus();
    ContractExecutionStatus(const QJsonObject& jsonObject);
    ContractExecutionStatus(const QJsonValue& jsonValue) :
        ContractExecutionStatus(jsonValue.toObject()) {}

    bool      isValid() const          { return !m_errDescription.isEmpty(); }

    bool      isError() const          { return m_isError; }
    QString   errDescription() const   { return m_errDescription; }

private:
    bool      m_isError;
    QString   m_errDescription;
};

inline QDebug operator<< (QDebug dbg, const ContractExecutionStatus& contractExecutionStatus)
{
    dbg.nospace() << qUtf8Printable(QString("ContractExecutionStatus(isError=%1; errDescription=%2)")
                                    .arg(contractExecutionStatus.isError())
                                    .arg(contractExecutionStatus.errDescription()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // CONTRACTEXECUTIONSTATUS_H
