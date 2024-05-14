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
    }

    Plasmoid.preferredRepresentation: Plasmoid.compactRepresentation
   
    Plasmoid.compactRepresentation: PlasmaCore.IconItem{
        source:plasmoid.icon
        focus:true
        MouseArea{
            anchors.fill:parent
            hoverEnabled:true
            propagateComposedEvents:true
            onClicked:action_clic()
            onPressAndHold:action_hold()
            onReleased:action_release()
        }
    }

 
    function action_clic() {
        nerdDictationWidget.manage_status()
    }
    function action_hold() {
        nerdDictationWidget.manage_hold()
    }
    function action_release() {
        nerdDictationWidget.manage_release()
    }

 }	
