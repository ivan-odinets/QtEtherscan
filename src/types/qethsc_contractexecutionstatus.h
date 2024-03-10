/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2022-2024 Ivan Odinets <i_odinets@protonmail.com>
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

#ifndef QT_ETHERSCAN_CONTRACTEXECUTIONSTATUS_H
#define QT_ETHERSCAN_CONTRACTEXECUTIONSTATUS_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

/*! @class ContractExecutionStatus src/types/qethsc_contractexecutionstatus.h
 *  @brief Object of this type is returned by API::checkContractExecutionStatus method.
 *
 * @see https://docs.etherscan.io/api-endpoints/stats#check-contract-execution-status */

class ContractExecutionStatus
{
public:
    /*! @brief Default constructor. Constructs invalid ContractExecutionStatus object with empty errDescription field
     *         and isError == true. */
    ContractExecutionStatus();
    ContractExecutionStatus(const QJsonObject& jsonObject);
    ContractExecutionStatus(const QJsonValue& jsonValue) :
        ContractExecutionStatus(jsonValue.toObject()) {}

    /*! @brief Returns true if this ContractExecutionStatus object is valid and contains reasonable information.
     *         ContractExecutionStatus object is considered to be valid if it was constucted using QJsonObject which
     *         is containing field "isError". */
    bool      isValid() const          { return m_isValidObject; }

    /*! @brief Returns true if "isError" field of etherscan.io reply is containing "1". */
    bool      isError() const          { return m_isError; }

    /*! @brief Returns "errDescription" field of etherscan.io reply. */
    QString   errDescription() const   { return m_errDescription; }

private:
    bool      m_isValidObject;
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

#endif // QT_ETHERSCAN_CONTRACTEXECUTIONSTATUS_H
