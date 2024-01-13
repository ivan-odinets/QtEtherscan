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

#include "contractsourcecode.h"

namespace QtEtherscan {

ContractSourceCode::ContractSourceCode()
{}

ContractSourceCode::ContractSourceCode(const QJsonObject& jsonObject) :
    m_sourceCode(jsonObject.value("SourceCode").toString()),
    m_abi(jsonObject.value("ABI")),
    m_contractName(jsonObject.value("ContractName").toString()),
    m_compilerVersion(jsonObject.value("CompilerVersion").toString()),
    m_optimizationUsed(jsonObject.value("OptimizationUsed").toString()),
    m_runs(jsonObject.value("Runs").toString()),
    m_constructorArguments(jsonObject.value("ConstructorArguments").toString()),
    m_evmVersion(jsonObject.value("EVMVersion").toString()),
    m_library(jsonObject.value("Library").toString()),
    m_licenseType(jsonObject.value("LicenseType").toString()),
    m_proxy(jsonObject.value("Proxy").toString()),
    m_implementation(jsonObject.value("Implementation").toString()),
    m_swarmSource(jsonObject.value("SwarmSource").toString())
{

}

ContractSourceCode::ContractSourceCode(const QJsonArray& jsonArray) :
    ContractSourceCode(jsonArray.isEmpty() ? QJsonObject() : jsonArray.first().toObject())
{}

} //namespace QtEtherscan
