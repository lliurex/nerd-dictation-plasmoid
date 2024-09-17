import QtQuick
import QtQuick.Layouts

import org.kde.plasma.plasmoid
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.components as PlasmaComponents3
import org.kde.plasma.extras as PlasmaExtras
import org.kde.kirigami as Kirigami

import org.kde.plasma.private.nerddictation 1.0
// Item - the most basic plasmoid component, an empty container.
PlasmoidItem {

	id:nerdDictationApplet
	
	NerdDictationWidget{
		id:nerdDictationWidget
	}
	 
	Plasmoid.contextualActions: [
		PlasmaCore.Action {
			 text: i18n("Start dictation")
			 icon.name:"media-playback-start"
			 visible:nerdDictationWidget.canPlay
			 enabled:nerdDictationWidget.canPlay
			 priority:Plasmoid.LowPriorityAction
			 onTriggered:action_play()
		},
		PlasmaCore.Action{
			 text: i18n("Pause dictation")
			 icon.name:"media-playback-pause"
			 visible:nerdDictationWidget.canPause
			 enabled:nerdDictationWidget.canPause
			 priority:Plasmoid.LowPriorityAction
			 onTriggered:action_pause()
		},
		PlasmaCore.Action{
			 text: i18n("Continue dictation")
			 icon.name:"media-playback-start"
			 visible:nerdDictationWidget.canResume
			 enabled:nerdDictationWidget.canResume
			 priority:Plasmoid.LowPriorityAction
			 onTriggered:action_resume()
		},
		PlasmaCore.Action{
			 text: i18n("Stop dictation")
			 icon.name:"media-playback-stop"
			 visible:nerdDictationWidget.canStop
			 enabled:nerdDictationWidget.canStop
			 priority:Plasmoid.LowPriorityAction
			 onTriggered:action_stop()
		}
		
	]
	
	PlasmaCore.Action {
		id: configureAction
		text: i18n("Help")
		icon.name:"help-contents"
		onTriggered:action_help()
	}
	
	Plasmoid.status: {
		switch (nerdDictationWidget.status){
			case NerdDictationWidget.ActiveStatus:
				return PlasmaCore.Types.ActiveStatus
			case NerdDictationWidget.PassiveStatus:
				return PlasmaCore.Types.PassiveStatus
		}
		
		return  PlasmaCore.Types.ActiveStatus
	}
	
	switchWidth: Kirigami.Units.gridUnit * 5
	switchHeight: Kirigami.Units.gridUnit * 5
	
	Plasmoid.icon:nerdDictationWidget.iconName
	
	toolTipMainText: nerdDictationWidget.toolTip
	toolTipSubText: nerdDictationWidget.subToolTip
	
	Component.onCompleted: {
		Plasmoid.setInternalAction("configure", configureAction)
	}
	
	compactRepresentation:MouseArea{
		anchors.fill:parent
		hoverEnabled:true
		
		onClicked:{
			console.log("CLICK")
			nerdDictationApplet.expanded = !nerdDictationApplet.expanded
		}
		
		Kirigami.Icon {
			source: plasmoid.icon
			anchors.fill: parent
			active: parent.containsMouse
		}
	}
	
	fullRepresentation: PlasmaComponents3.Page {
		implicitWidth: Kirigami.Units.gridUnit * 12
		implicitHeight: Kirigami.Units.gridUnit * 6
		
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
			width: parent.width - (Kirigami.Units.gridUnit * 4)
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
	}
	
	function action_pause(){
		nerdDictationWidget.manage_status("pause")
	}
	
	function action_resume(){
		nerdDictationWidget.manage_status("resume")
	}
	
	function action_stop(){
		nerdDictationWidget.manage_status("stop")
	}
	
	function action_help(){
		nerdDictationWidget.open_help()
	}
 }	
