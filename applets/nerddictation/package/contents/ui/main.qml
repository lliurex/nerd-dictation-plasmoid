import QtQuick 2.15
import QtQuick.Layouts 1.15

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.1 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.extras 2.0 as PlasmaExtras

import org.kde.plasma.private.nerddictation 1.0
// Item - the most basic plasmoid component, an empty container.
Item {

    id:nerdDictationApplet

    NerdDictationWidget{
        id:nerdDictationWidget
    }

    function populateContextualActions() {
        plasmoid.clearActions()

        plasmoid.setAction("play", i18n("Start dictation"), "media-playback-start")
        plasmoid.action("play").enabled = nerdDictationWidget.canPlay
        plasmoid.action("play").visible = nerdDictationWidget.canPlay
        plasmoid.action("play").priority = Plasmoid.LowPriorityAction

        plasmoid.setAction("pause", i18n("Pause dictation"), "media-playback-pause")
        plasmoid.action("pause").enabled = nerdDictationWidget.canPause
        plasmoid.action("pause").visible = nerdDictationWidget.canPause
        plasmoid.action("pause").priority = Plasmoid.LowPriorityAction

        plasmoid.setAction("resume", i18n("Continue dictation"), "media-playback-start")
        plasmoid.action("resume").enabled = nerdDictationWidget.canResume
        plasmoid.action("resume").visible = nerdDictationWidget.canResume
        plasmoid.action("resume").priority = Plasmoid.LowPriorityAction

        plasmoid.setAction("stop", i18n("Stop dictation"), "media-playback-stop")
        plasmoid.action("stop").enabled = nerdDictationWidget.canStop
        plasmoid.action("stop").visible = nerdDictationWidget.canStop
        plasmoid.action("stop").priority = Plasmoid.LowPriorityAction

        plasmoid.setAction("help", i18n("See help"), "help-contents")

    }

    Plasmoid.status: {
        /* Warn! Enum types are accesed through ClassName not ObjectName */
        switch (nerdDictationWidget.status){
            case NerdDictationWidget.ActiveStatus:
                 return PlasmaCore.Types.ActiveStatus
            case NerdDictationWidget.PassiveStatus:
                return PlasmaCore.Types.PassiveStatus
        }
        
        return  PlasmaCore.Types.ActiveStatus
    }

    Plasmoid.switchWidth: units.gridUnit * 5
    Plasmoid.switchHeight: units.gridUnit * 5

    Plasmoid.icon:nerdDictationWidget.iconName
    Plasmoid.toolTipMainText: nerdDictationWidget.toolTip
    Plasmoid.toolTipSubText: nerdDictationWidget.subToolTip

    Component.onCompleted: {
        plasmoid.removeAction("configure");
        populateContextualActions();
    }

    Plasmoid.compactRepresentation: PlasmaCore.IconItem{
        source:plasmoid.icon
        focus:true
        MouseArea{
            anchors.fill:parent
            hoverEnabled:true
            propagateComposedEvents:true
            onClicked:{
                Plasmoid.expanded = !Plasmoid.expanded
             }
        }
    }

    Plasmoid.fullRepresentation: PlasmaComponents3.Page {
        implicitWidth: PlasmaCore.Units.gridUnit * 12
        implicitHeight: PlasmaCore.Units.gridUnit * 6

        Keys.onReleased:{
            if (event.key === Qt.Key_Space){
                if (!event.isAutoRepeat){
                    if (nerdDictationWidget.canPlay){
                        action_play()
                    }else{
                        if (nerdDictationWidget.canPause){
                            action_pause()
                        }else{
                            if (nerdDictationWidget.canResume){
                                action_resume()
                            }else{
                                event.accepted=false
                            }
                        }
                    }
                }else{
                    event.accepted=false;
                }
            }else{
                event.accepted=false;
            }
        }
        
        PlasmaExtras.PlaceholderMessage {
            id:iconSection
            anchors.centerIn: parent
            width: parent.width - (PlasmaCore.Units.gridUnit * 4)
            iconName: Plasmoid.icon
            text:nerdDictationWidget.placeHolderText
        }

        RowLayout{
            id:btnLayout
            anchors.top:iconSection.bottom
            anchors.horizontalCenter:parent.horizontalCenter
            spacing:15

            PlasmaComponents3.ToolButton{
                id:playBtn
                width:35
                height:35
                visible:nerdDictationWidget.canPlay
                enabled:nerdDictationWidget.canPlay
                icon.name:"media-playback-start.svg"
                focus:true
                PlasmaComponents3.ToolTip{
                    id:playTP
                    text:i18n("Clic to start dictation")
                }
                onClicked:{
                    action_play()
                }
            }

            PlasmaComponents3.ToolButton{
                id:pauseBtn
                width:35
                height:35
                visible:nerdDictationWidget.canPause
                enabled:nerdDictationWidget.canPause
                icon.name:"media-playback-pause.svg"
                focus:true
                PlasmaComponents3.ToolTip{
                    id:pauseTP
                    text:i18n("Clic to pause dictation")
                }
                onClicked:{
                    action_pause()
                }
            }

            PlasmaComponents3.ToolButton{
                id:resumeBtn
                width:35
                height:35
                visible:nerdDictationWidget.canResume
                enabled:nerdDictationWidget.canResume
                icon.name:"media-playback-start.svg"
                focus:true
                PlasmaComponents3.ToolTip{
                    id:resumeTP
                    text:i18n("Clic to continue dictation")
                }
                onClicked:{
                    action_resume()
                }
            }

            PlasmaComponents3.ToolButton{
                id:stopBtn
                width:35
                height:35
                visible:nerdDictationWidget.canStop
                enabled:nerdDictationWidget.canStop
                icon.name:"media-playback-stop.svg"
                focus:false
                PlasmaComponents3.ToolTip{
                    id:stopTP
                    text:i18n("Clic to end dictation")
                }
                onClicked:{
                    action_stop()
                }
            }
        }
          
    }
    
    function action_play() {
        nerdDictationWidget.manage_status("play")
        populateContextualActions();
    }
    function action_pause(){
        nerdDictationWidget.manage_status("pause")
        populateContextualActions();
    }
    function action_resume(){
        nerdDictationWidget.manage_status("resume")
        populateContextualActions();
    }
    function action_stop(){
        nerdDictationWidget.manage_status("stop")
        populateContextualActions();
    }
    function action_help(){
        nerdDictationWidget.open_help()
    }

 }	
