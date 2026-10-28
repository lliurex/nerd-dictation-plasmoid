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
#ifndef PLASMA_NERD_DICTATION_WIDGET_UTILS_H
#define PLASMA_NERD_DICTATION_WIDGET_UTILS_H

#include <QObject>
#include <QProcess>
#include <QFile>

class NerdDictationWidgetUtils : public QObject
{
    Q_OBJECT


public:

    static NerdDictationWidgetUtils& instance(){
        static NerdDictationWidgetUtils _instance;
        return _instance;
    }

    NerdDictationWidgetUtils(const NerdDictationWidgetUtils&)=delete;
    NerdDictationWidgetUtils& operator=(const NerdDictationWidgetUtils&) =delete;
   
    bool isNerdDictationInstalled();
    void manageStatus(const QString &action);
    void isNerdDictationRun();

signals:

    void isNerdDictationRunFinished(bool isRunning);
    void statusChanged(int targetState, bool isError);
    void dictationError(const QString &errorText);

private slots:

    void handleIsNerdDictationRunFinished(bool isRunning);


private: 

    explicit NerdDictationWidgetUtils();

    QFile TARGET_FILE;
    QProcess *m_checkProcess = nullptr;

    QString m_actionToRun;
    bool m_waitForRun=false;
      
};

#endif // PLASMA_NERD_DICTATION_WIDGET_UTILS_H
