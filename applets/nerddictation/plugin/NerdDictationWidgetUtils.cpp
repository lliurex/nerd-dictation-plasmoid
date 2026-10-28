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

#include <KLocalizedString>
#include <KFormat>

#include <QProcess>
#include <QDebug>
#include <sys/types.h>
#include <thread>

using namespace std;

NerdDictationWidgetUtils::NerdDictationWidgetUtils()
    : QObject(nullptr)
    ,m_waitForRun(false)
       
{
    connect(this,&NerdDictationWidgetUtils::isNerdDictationRunFinished,this,&NerdDictationWidgetUtils::handleIsNerdDictationRunFinished);
    TARGET_FILE.setFileName("/usr/bin/nerd-dictation");
  
}    

bool NerdDictationWidgetUtils::isNerdDictationInstalled(){

    bool isInstalled=false;
    
    if (NerdDictationWidgetUtils::TARGET_FILE.exists()) {
        isInstalled=true;
    }

    return isInstalled;

}

void NerdDictationWidgetUtils::manageStatus(const QString &action){

    if (!m_waitForRun){
        m_waitForRun=true;
        m_actionToRun=action;
        isNerdDictationRun();
    }

}

void NerdDictationWidgetUtils::isNerdDictationRun(){

    if (m_checkProcess) {
        return; 
    }

    m_checkProcess = new QProcess(this);

    connect(m_checkProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, [this](int exitCode, QProcess::ExitStatus exitStatus) {       
        if (!m_checkProcess) return;

        QString output = QString::fromUtf8(m_checkProcess->readAllStandardOutput()).trimmed();
        bool isRunning = !output.isEmpty();

        emit isNerdDictationRunFinished(isRunning);

        m_checkProcess->deleteLater();
        m_checkProcess = nullptr;
    });

    m_checkProcess->start("pgrep", {"nerd-dictation"});
}

void NerdDictationWidgetUtils::handleIsNerdDictationRunFinished(bool isRunning)
{
    

    QString errorText = i18n("An error was detected during execution");
    
    QProcess *currentProcess = new QProcess(this);

    connect(currentProcess, &QProcess::errorOccurred, this, [this, currentProcess,errorText](QProcess::ProcessError error) {
        qDebug() << "[NERD-DICTATION CRITICAL-ERROR:]" << error;
        emit dictationError(errorText);
        emit statusChanged(0,true);
        m_waitForRun=false;
        currentProcess->deleteLater();
    });

    connect(currentProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), 
        this, [this,currentProcess,errorText](int exitCode, QProcess::ExitStatus exitStatus) {
        
        if (exitStatus == QProcess::CrashExit || exitCode != 0) {
            qDebug() << "[NERD-DICTATION ERROR:]" << currentProcess->readAllStandardError();
            emit dictationError(errorText);
            emit statusChanged(0,true);
        }
        m_waitForRun=false;
        currentProcess->deleteLater();
    });

    QStringList args;
    int targetState=0;

    if (!isRunning) {
        args << "begin";
        targetState = 2;
    } else {
        if (m_actionToRun == "pause") {
            args << "suspend";
            targetState = 3;
        } else if (m_actionToRun == "resume") {
            args <<"resume";
            targetState = 2;
        } else if (m_actionToRun == "stop") {
            args << "end";
            targetState = 0;
        }
    }
    
    currentProcess->start("nerd-dictation", args);
    emit statusChanged(targetState,false);
    m_waitForRun=false;

}



