/*
 **********************************************************************************************************************
 *
 * QtEtherscan
 * Copyright (C) 2023 Ivan Odinets
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

#ifndef ESTIMATEDBLOCKCOUNTDOWN_H
#define ESTIMATEDBLOCKCOUNTDOWN_H

#include "./global.h"

namespace QtEtherscan {

class EstimatedBlockCountdown
{
public:
    EstimatedBlockCountdown();
    EstimatedBlockCountdown(const QJsonObject& jsonObject);
    EstimatedBlockCountdown(const QJsonValue& jsonValue) :
        EstimatedBlockCountdown(jsonValue.toObject()) {}

    bool      isValid() const               { return m_currentBlock != InvalidBlockNumber; }

    qint32    currentBlock() const          { return m_currentBlock; }
    qint32    countdownBlock() const        { return m_countdownBlock; }
    qint32    remainingBlock() const        { return m_remainingBlock; }
    quint64   estimateTimeInSec() const     { return m_estimateTimeInSec; }

private:
    qint32    m_currentBlock;
    qint32    m_countdownBlock;
    qint32    m_remainingBlock;
    quint64   m_estimateTimeInSec;
};

inline QDebug operator<< (QDebug dbg, const EstimatedBlockCountdown& countdown)
{
    dbg.nospace() << qUtf8Printable(QString("EstimatedBlockCountdown(currentBlock=%1; countdownBlock=%2; remainingBlock=%3; estimateTimeInSec=%4)")
                                    .arg(countdown.currentBlock())
                                    .arg(countdown.countdownBlock())
                                    .arg(countdown.remainingBlock())
                                    .arg(countdown.estimateTimeInSec()));

    return dbg.maybeSpace();
}

} //namespace QtEtherscan

#endif // ESTIMATEDBLOCKCOUNTDOWN_H
