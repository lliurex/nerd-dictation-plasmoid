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
#include "NerdDictationWidget.h"
#include "NerdDictationWidgetUtils.h"

#include <KLocalizedString>
#include <KFormat>
#include <KIO/CommandLauncherJob>
#include <QTimer>
#include <QStandardPaths>
#include <QDebug>
#include <QThread>
#include <QTime>


NerdDictationWidget::NerdDictationWidget(QObject *parent)
    : QObject(parent)
    ,m_utils(new NerdDictationWidgetUtils(this))

    
{
    connect(m_utils,&NerdDictationWidgetUtils::isNerdDictationRunFinished,this,&NerdDictationWidget::handleIsNerdDictationRunFinished);

    plasmoidMode();
}    


void NerdDictationWidget::plasmoidMode(){

    bool isNerdDictationInstalled=m_utils->isNerdDictationInstalled();

    if (isNerdDictationInstalled){
        changeTryIconState(0,false);
    }else{
        setStatus(HiddenStatus);
    }
      
}

NerdDictationWidget::TrayStatus NerdDictationWidget::status() const
{
    return m_status;
}

void NerdDictationWidget::changeTryIconState(int state, bool isError){

    const QString tooltip(i18n("Nerd-Dictation"));
    QString notificationIcon;
    bool canPlay=false;
    bool canStop=false;
    bool canPause=false;
    bool canResume=false;
    bool activeStatus=true;
    bool changeActions=true;
    QString holderText;
    QString subtooltip;

    if (!isError){
        if (previousState!=state){
            previousState=state;
            if (state==0){
                subtooltip=i18n("Clic to start dictation");
                canPlay=true;
                notificationIcon="nerd-dictation-off";
                holderText=i18n("No dictation running");
     
            }else if (state==2){
                subtooltip=i18n("Clic to pause/end dictation");
                notificationIcon="nerd-dictation-on";
                canPause=true;
                canStop=true;
                holderText=i18n("The dictation is running");

            }else if (state==3){
                subtooltip=i18n("Clic to restart/end dictation");
                notificationIcon="nerd-dictation-pause";
                canResume=true;
                canStop=true;
                holderText=i18n("The dictation is paused");
            }else{
                subtooltip=i18n("Clic to start dictation");
                canPlay=true;
                holderText="";
                activeStatus=false;
            }
        }else{
            changeActions=false;
            holderText=i18n("Failed to run action. Try again");
        }
    }else{;
        subtooltip=i18n("Clic to start dictation");
        notificationIcon="nerd-dictation-off";
        canPlay=true;
   }

    setWaitForRun(true);
    if (activeStatus){
        setStatus(ActiveStatus);
    }else{
        setStatus(PassiveStatus);
    }
    if (changeActions){
        setSubToolTip(subtooltip);
        setCanPlay(canPlay);
        setCanPause(canPause);
        setCanResume(canResume);
        setCanStop(canStop);
        setToolTip(tooltip);
        setIconName(notificationIcon);
    }
    if (!isError){
        setPlaceHolderText(holderText);
    }
    setWaitForRun(false);
}

void NerdDictationWidget::manage_status(const QString &action)
{
    
    if (!m_waitForRun){
        setWaitForRun(true);
        actionToRun=action;
        m_utils->isNerdDictationRun();
    }
}

void NerdDictationWidget::handleIsNerdDictationRunFinished(bool isRunning)
{
    
    QString errorText = i18n("An error was detected during execution");
    QString holderText = m_placeHolderText.contains("An error") ? 
                         m_placeHolderText : (m_placeHolderText + "\n" + errorText);

    QProcess *process = new QProcess(this);
    QStringList args;
    int targetState = 0;

    if (!isRunning) {
        args << "begin";
        targetState = 2;
    } else {
        if (actionToRun == "pause") {
            args << "suspend";
            targetState = 3;
        } else if (actionToRun == "resume") {
            args <<"resume";
            targetState = 2;
        } else if (actionToRun == "stop") {
            args << "end";
            targetState = 0;
        }
    }

    connect(process, &QProcess::errorOccurred, this, [this, holderText](QProcess::ProcessError error) {
        qDebug() << "[NERD-DICTATION CRITICAL-ERROR:]" << error;
        this->setPlaceHolderText(holderText);
        this->changeTryIconState(0,true);
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), 
            this, [this, process, holderText](int exitCode, QProcess::ExitStatus exitStatus) {
        
        if (exitStatus == QProcess::CrashExit || exitCode != 0) {
            qDebug() << "[NERD-DICTATION ERROR:]" << process->readAllStandardError();
            this->setPlaceHolderText(holderText);
            this->changeTryIconState(0,true);
        }
        process->deleteLater();
    });

    process->start("nerd-dictation", args);
    changeTryIconState(targetState,false);

}

void NerdDictationWidget::open_help()
{
    KIO::CommandLauncherJob *job = nullptr;
    QString cmd="xdg-open https://wiki.edu.gva.es/lliurex/tiki-index.php?page=Nerd-Dictation";
    job = new KIO::CommandLauncherJob(cmd);
    job->start();
}

void NerdDictationWidget::setStatus(NerdDictationWidget::TrayStatus status)
{
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}

QString NerdDictationWidget::iconName() const
{
    return m_iconName;
}

void NerdDictationWidget::setIconName(const QString &name)
{
    if (m_iconName != name) {
        m_iconName = name;
        emit iconNameChanged();
    }
}

QString NerdDictationWidget::toolTip() const
{
    return m_toolTip;
}

void NerdDictationWidget::setToolTip(const QString &toolTip)
{
    if (m_toolTip != toolTip) {
        m_toolTip = toolTip;
        emit toolTipChanged();
    }
}

QString NerdDictationWidget::subToolTip() const
{
    return m_subToolTip;
}

void NerdDictationWidget::setSubToolTip(const QString &subToolTip)
{
    if (m_subToolTip != subToolTip) {
        m_subToolTip = subToolTip;
        emit subToolTipChanged();
    }
}

bool NerdDictationWidget::canPlay()
{
    return m_canPlay;

} 

void NerdDictationWidget::setCanPlay(bool canPlay){

    if (m_canPlay != canPlay){
        m_canPlay = canPlay;
        emit canPlayChanged();
    }
}

bool NerdDictationWidget::canPause()
{
    return m_canPause;

} 

void NerdDictationWidget::setCanPause(bool canPause){

    if (m_canPause != canPause){
        m_canPause = canPause;
        emit canPauseChanged();
    }
}

bool NerdDictationWidget::canResume()
{
    return m_canResume;

} 

void NerdDictationWidget::setCanResume(bool canResume){

    if (m_canResume != canResume){
        m_canResume = canResume;
        emit canResumeChanged();
    }
}

bool NerdDictationWidget::canStop()
{
    return m_canStop;

} 

void NerdDictationWidget::setCanStop(bool canStop){

    if (m_canStop != canStop){
        m_canStop = canStop;
        emit canStopChanged();
    }
}


QString NerdDictationWidget::placeHolderText() const
{
    return m_placeHolderText;
}

void NerdDictationWidget::setPlaceHolderText(const QString &placeHolderText)
{
    if (m_placeHolderText != placeHolderText) {
        m_placeHolderText = placeHolderText;
        emit placeHolderTextChanged();
    }
}

bool NerdDictationWidget::waitForRun(){

    return m_waitForRun;

}

void NerdDictationWidget::setWaitForRun(bool waitForRun){

    if (m_waitForRun!=waitForRun){
        m_waitForRun=waitForRun;
        emit waitForRunChanged();

    }
}
