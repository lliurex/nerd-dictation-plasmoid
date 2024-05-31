import QtQuick 2.15
import QtQuick.Layouts 1.15

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.1 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3
import org.kde.plasma.extras 2.0 as PlasmaExtras

import org.kde.plasma.private.nerddictation 1.0
// Item - the most basic plasmoid component, an empty container.
Item {

    id:nerddictationApplet

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

    Plasmoid.preferredRepresentation: Plasmoid.compactRepresentation
   
    Plasmoid.compactRepresentation: PlasmaCore.IconItem{
        source:plasmoid.icon
        focus:true
        MouseArea{
            anchors.fill:parent
            hoverEnabled:true
            propagateComposedEvents:true
            onClicked:{
                if (nerdDictationWidget.canPlay){
                    action_play()
                }else{
                    if (nerdDictationWidget.canResume){
                        action_resume()
                    }else{
                        action_stop()
                    }
                }
            }
           /* onPressAndHold:action_hold()
            onReleased:action_release()*/
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

 }	
