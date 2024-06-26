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
#ifndef PLASMA_NERD_DICTATION_WIDGET_H
#define PLASMA_NERD_DICTATION_WIDGET_H

#include <QObject>
#include <QProcess>
#include <QPointer>
#include <QThread>

#include "NerdDictationWidgetUtils.h"

class NerdDictationWidget : public QObject
{
    Q_OBJECT


    Q_PROPERTY(TrayStatus status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString toolTip READ toolTip NOTIFY toolTipChanged)
    Q_PROPERTY(QString subToolTip READ subToolTip NOTIFY subToolTipChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY iconNameChanged)
    Q_PROPERTY(bool canPlay READ canPlay NOTIFY canPlayChanged)
    Q_PROPERTY(bool canPause READ canPause NOTIFY canPauseChanged)
    Q_PROPERTY(bool canResume READ canResume NOTIFY canResumeChanged)
    Q_PROPERTY(bool canStop READ canStop NOTIFY canStopChanged)
    Q_PROPERTY(QString placeHolderText READ placeHolderText NOTIFY placeHolderTextChanged)


    Q_ENUMS(TrayStatus)

public:
    /**
     * System tray icon states.
     */
    enum TrayStatus {
        ActiveStatus = 0,
        PassiveStatus,
    };

    NerdDictationWidget(QObject *parent = nullptr);

    TrayStatus status() const;
    void changeTryIconState (int state);
    void setStatus(TrayStatus status);

    QString toolTip() const;
    void setToolTip(const QString &toolTip);

    QString subToolTip() const;
    void setSubToolTip(const QString &subToolTip);

    QString iconName() const;
    void setIconName(const QString &name);

    bool canPlay();
    void setCanPlay(bool);

    bool canPause();
    void setCanPause(bool);

    bool canResume();
    void setCanResume(bool);

    bool canStop();
    void setCanStop(bool);

    QString placeHolderText() const;
    void setPlaceHolderText(const QString &name);

public slots:
    
    void manage_status(const QString &action);
    void open_help();

signals:
   
    void statusChanged();
    void toolTipChanged();
    void subToolTipChanged();
    void iconNameChanged();
    void canPlayChanged();
    void canPauseChanged();
    void canResumeChanged();
    void canStopChanged();
    void placeHolderTextChanged();

private:

    void plasmoidMode();
    TrayStatus m_status = PassiveStatus;
    QString m_iconName = QStringLiteral("nerd-dictation-off");
    QString m_toolTip;
    QString m_subToolTip;
    bool m_canPlay=true;
    bool m_canPause=false;
    bool m_canResume=false;
    bool m_canStop=false;
    QString m_placeHolderText;
    
    bool isNerdDictationRun=false;

    NerdDictationWidgetUtils* m_utils;
};

#endif // PLASMA_NERD_DICTATION_WIDGET_H
