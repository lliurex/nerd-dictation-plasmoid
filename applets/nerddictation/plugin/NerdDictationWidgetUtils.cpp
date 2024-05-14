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
#include "NerdDictationWidgetUtils.h"

#include <QDebug>
#include <sys/types.h>
#include <thread>

using namespace std;

NerdDictationWidgetUtils::NerdDictationWidgetUtils(QObject *parent)
    : QObject(parent)
       
{
  
}    

bool NerdDictationWidgetUtils::isNerdDictationInstalled(){

    QProcess process;
    QStringList output;
    QString outputInfo;
    bool isInstalled=false;
    QString cmd="apt-cache policy nerd-dictation";
    process.start("/bin/sh",QStringList()<<"-c"<<cmd);
    process.waitForFinished(-1);
    QString stdout=process.readAllStandardOutput();
    QString stderr=process.readAllStandardError();
    output=stdout.split('\n');
    if (output.length()>1){
        outputInfo=output[1].split(":")[1];
        if (!outputInfo.contains("(")){
            isInstalled=true;
        }
    }

    return isInstalled;

}

bool NerdDictationWidgetUtils::isNerdDictationRun(){

    QProcess process;
    QStringList output;
    QString outputInfo;
    bool isRunning=false;
    QString cmd="ps -ef | grep 'nerd-dictation' | grep -v 'grep'";
    process.start("/bin/sh",QStringList()<<"-c"<<cmd);
    process.waitForFinished(-1);
    QString stdout=process.readAllStandardOutput();
    QString stderr=process.readAllStandardError();
    output=stdout.split(" ");
    if (output.length()>1){
        isRunning=true;
        
    }

    return isRunning;


}


