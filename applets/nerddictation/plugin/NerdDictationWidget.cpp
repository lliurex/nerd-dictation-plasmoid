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
    
    plasmoidMode();
}    


void NerdDictationWidget::plasmoidMode(){

    bool isNerdDictationInstalled=m_utils->isNerdDictationInstalled();

    if (isNerdDictationInstalled){
        changeTryIconState(0);
    }else{
        changeTryIconState(1);
    }
      
}

NerdDictationWidget::TrayStatus NerdDictationWidget::status() const
{
    return m_status;
}

void NerdDictationWidget::changeTryIconState(int state){

    const QString tooltip(i18n("Nerd-Dictation"));
    QString notificationIcon;

    if (state==0){
        setStatus(ActiveStatus);
        const QString subtooltip(i18n("Clic to start dictation"));
        setToolTip(tooltip);
        setSubToolTip(subtooltip);
        notificationIcon="nerd-dictation-off";
        setIconName(notificationIcon);
        setCanPlay(true);
        setCanPause(false);
        setCanResume(false);
        setCanStop(false);
     
    }else if (state==2){
        setStatus(ActiveStatus);
        const QString subtooltip(i18n("Clic to end dictation"));
        setToolTip(tooltip);
        setSubToolTip(subtooltip);
        notificationIcon="nerd-dictation-on";
        setIconName(notificationIcon);
        setCanPlay(false);
        setCanPause(true);
        setCanResume(false);
        setCanStop(true);

    }else if (state==3){
        setStatus(ActiveStatus);
        const QString subtooltip(i18n("Clic to restart dictation"));
        setToolTip(tooltip);
        setSubToolTip(subtooltip);
        notificationIcon="nerd-dictation-pause";
        setIconName(notificationIcon);
        setCanPlay(false);
        setCanPause(false);
        setCanResume(true);
        setCanStop(true);

    }else{
        setCanPlay(true);
        setCanPause(false);
        setCanResume(false);
        setCanStop(false);
        setStatus(PassiveStatus);
    }
    
}

void NerdDictationWidget::manage_status(const QString &action)
{
    isNerdDictationRun=m_utils->isNerdDictationRun();

    if (!isNerdDictationRun){
        if (action=="play"){
            changeTryIconState(2);
            KIO::CommandLauncherJob *job = nullptr;
            QString cmd="nerd-dictation begin";
            job = new KIO::CommandLauncherJob(cmd);
            job->start();
        }
    }else{
        if (action=="pause"){
            changeTryIconState(3);
            KIO::CommandLauncherJob *job = nullptr;
            QString cmd="nerd-dictation suspend";
            job = new KIO::CommandLauncherJob(cmd);
            job->start();
        }else if (action=="resume"){
            changeTryIconState(2);
            KIO::CommandLauncherJob *job = nullptr;
            QString cmd="nerd-dictation resume";
            job = new KIO::CommandLauncherJob(cmd);
            job->start();
        }else if (action=="stop"){
            changeTryIconState(0);
            isHoldMode=false;
            KIO::CommandLauncherJob *job = nullptr;
            QString cmd="nerd-dictation end";
            job = new KIO::CommandLauncherJob(cmd);
            job->start();

        }
   
     }   
   
}

void NerdDictationWidget::manage_hold()
{
    isNerdDictationRun=m_utils->isNerdDictationRun();

    if (!isNerdDictationRun){
        isHoldMode=true;
        /*manage_status();*/
    }
}

void NerdDictationWidget::manage_release()
{
    if (isHoldMode){
        isHoldMode=false;
        /*manage_status();*/
    }
   
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
