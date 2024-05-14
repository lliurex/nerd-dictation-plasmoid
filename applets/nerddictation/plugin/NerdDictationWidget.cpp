/*
 * Copyright (C) 2023 Juan Ramon Pelegrina <juapesai@hotmail.com>
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
        isNerdDictationRun=false;
        setStatus(ActiveStatus);
        const QString subtooltip(i18n("Clic to start dictation"));
        setToolTip(tooltip);
        setSubToolTip(subtooltip);
        notificationIcon="nerd-dictation-off";
        setIconName(notificationIcon);
     
    }else if (state==2){
        isNerdDictationRun=true;
        setStatus(ActiveStatus);
        const QString subtooltip(i18n("Clic to end dictation"));
        setToolTip(tooltip);
        setSubToolTip(subtooltip);
        notificationIcon="nerd-dictation-on";
        setIconName(notificationIcon);

    }else{
        setStatus(PassiveStatus);
    }
    
}

void NerdDictationWidget::manage_status()
{
    isNerdDictationRun=m_utils->isNerdDictationRun();

    if (!isNerdDictationRun){
        changeTryIconState(2);
        KIO::CommandLauncherJob *job = nullptr;
        QString cmd="nerd-dictation begin";
        job = new KIO::CommandLauncherJob(cmd);
        job->start();
    }else{
        changeTryIconState(0);
        KIO::CommandLauncherJob *job = nullptr;
        QString cmd="nerd-dictation end";
        job = new KIO::CommandLauncherJob(cmd);
        job->start();
    }   
   
}

void NerdDictationWidget::manage_hold()
{
    if (!isNerdDictationRun){
        isHoldMode=true;
        manage_status();
    }
}

void NerdDictationWidget::manage_release()
{
    if (isHoldMode){
        isHoldMode=false;
        manage_status();
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
