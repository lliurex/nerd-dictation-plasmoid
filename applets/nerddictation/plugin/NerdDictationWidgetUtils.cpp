/*
 * Copyright (C) 2024 Juan Ramon Pelegrina <juapesai@hotmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "NerdDictationWidgetUtils.h"

#include <QDebug>
#include <sys/types.h>
#include <thread>

using namespace std;

NerdDictationWidgetUtils::NerdDictationWidgetUtils(QObject *parent)
    : QObject(parent)
       
{

    TARGET_FILE.setFileName("/usr/bin/nerd-dictation");
  
}    

bool NerdDictationWidgetUtils::isNerdDictationInstalled(){

    bool isInstalled=false;
    
    if (NerdDictationWidgetUtils::TARGET_FILE.exists()) {
        isInstalled=true;
    }

    return isInstalled;

}

void NerdDictationWidgetUtils::isNerdDictationRun(){

    if (m_process) {
        return; 
    }

    m_process = new QProcess(this);

    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, [this](int exitCode, QProcess::ExitStatus exitStatus) {       
        if (!m_process) return;

        QString output = QString::fromUtf8(m_process->readAllStandardOutput()).trimmed();
        bool isRunning = !output.isEmpty();

        emit isNerdDictationRunFinished(isRunning);

        m_process->deleteLater();
        m_process = nullptr;
    });

    m_process->start("pgrep", {"nerd-dictation"});
}


