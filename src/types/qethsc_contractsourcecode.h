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

#ifndef QT_ETHERSCAN_CONTRACTSOURCECODE_H
#define QT_ETHERSCAN_CONTRACTSOURCECODE_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace QtEtherscan {

/*! @class ContractSourceCode src/types/qethsc_contractsourcecode.h
 *  @brief Object of this type is returned by API::getContractSourceCode method.
 *
 * @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-source-code-for-verified-contract-source-codes */

class ContractSourceCode
{
public:
    /*! @brief Default constructor. Constructs invalid ContractSourceCode object. */
    ContractSourceCode();

    /*! @brief Constructs ContractSourceCode object from provided QJsonArray using its first element.
     *  @see https://docs.etherscan.io/api-endpoints/contracts#get-contract-source-code-for-verified-contract-source-codes
     *  @see https://api.etherscan.io/api?module=contract&action=getsourcecode&address=0xBB9bc244D798123fDe783fCc1C72d3Bb8C189413&apikey=YourApiKeyToken */
    ContractSourceCode(const QJsonArray& jsonArray);
    ContractSourceCode(const QJsonValue& jsonValue) :
        ContractSourceCode(jsonValue.toArray()) {}

    /*! @brief Returns true if this ContractSourceCode object is valid and contains reasonable information.
     *         ContractSourceCode object is considered to be valid if sourceCode() field contains non empty QString. */
    bool           isValid() const               { return !m_sourceCode.isEmpty(); }

    /*! @brief Returns "SourceCode" field from etherscan.io response. */
    QString        sourceCode() const            { return m_sourceCode; }

    /*! @brief Returns "ABI" field from etherscan.io response in form of QJsonValue. */
    QJsonValue     abi() const                   { return m_abi; }

    /*! @brief Returns "ContractName" field from etherscan.io response. */
    QString        contractName() const          { return m_contractName; }

    /*! @brief Returns "CompilerVersion" field from etherscan.io response. */
    QString        compilerVersion() const       { return m_compilerVersion; }

    /*! @brief Returns "OptimizationUsed" field from etherscan.io response. */
    QString        optimizationUsed() const      { return m_optimizationUsed; }

    /*! @brief Returns "Runs" field from etherscan.io response. */
    QString        runs() const                  { return m_runs; }

    /*! @brief Returns "ConstructorArguments" field from etherscan.io response. */
    QString        constructorArguments() const  { return m_constructorArguments; }

    /*! @brief Returns "EVMVersion" field from etherscan.io response. */
    QString        evmVersion() const            { return m_evmVersion; }

    /*! @brief Returns "Library" field from etherscan.io response. */
    QString        library() const               { return m_library; }

    /*! @brief Returns "LicenseType" field from etherscan.io response. */
    QString        licenseType() const           { return m_licenseType; }

    /*! @brief Returns "Proxy" field from etherscan.io response. */
    QString        proxy() const                 { return m_proxy; }

    /*! @brief Returns "Implementation" field from etherscan.io response. */
    QString        implementation() const        { return m_implementation; }

    /*! @brief Returns "SwarmSource" field from etherscan.io response. */
    QString        swarmSource() const           { return m_swarmSource; }

private:
    ContractSourceCode(const QJsonObject& jsonObject);
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

#endif // QT_ETHERSCAN_CONTRACTSOURCECODE_H
