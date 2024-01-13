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

#ifndef CONTRACTSOURCECODE_H
#define CONTRACTSOURCECODE_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

/*! @class ContractSourceCode src/types/contractsourcecode.h
 *  @brief Object of this type is returned by API::getContractSourceCode method.
 *
 * @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-source-code-for-verified-contract-source-codes */

class ContractSourceCode
{
public:
    ContractSourceCode();
    ContractSourceCode(const QJsonObject& jsonObject);
    ContractSourceCode(const QJsonArray& jsonArray);
    ContractSourceCode(const QJsonValue& jsonValue) :
        ContractSourceCode(jsonValue.toArray()) {}

    QString sourceCode() const              { return m_sourceCode; }
    QJsonValue abi() const                  { return m_abi; }
    QString contractName() const            { return m_contractName; }
    QString compilerVersion() const         { return m_compilerVersion; }
    QString optimizationUsed() const        { return m_optimizationUsed; }
    QString runs() const                    { return m_runs; }
    QString constructorArguments() const    { return m_constructorArguments; }
    QString evmVersion() const              { return m_evmVersion; }
    QString library() const                 { return m_library; }
    QString licenseType() const             { return m_licenseType; }
    QString proxy() const                   { return m_proxy; }
    QString implementation() const          { return m_implementation; }
    QString swarmSource() const             { return m_swarmSource; }

private:
    QString        m_sourceCode;
    QJsonValue     m_abi;
    QString        m_contractName;
    QString        m_compilerVersion;
    QString        m_optimizationUsed;
    QString        m_runs;
    QString        m_constructorArguments;
    QString        m_evmVersion;
    QString        m_library;
    QString        m_licenseType;
    QString        m_proxy;
    QString        m_implementation;
    QString        m_swarmSource;
};

inline QDebug operator<< (QDebug dbg, const ContractSourceCode& contractSourceCode)
{
    dbg.nospace() << qUtf8Printable(QString("ContractSourceCode(contractName=%1)")
                                    .arg(contractSourceCode.contractName()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // CONTRACTSOURCECODE_H
