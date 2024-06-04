
#######################################################################################
# Package
plasma_install_package(package org.kde.plasma.nerddictation)


#######################################################################################
# Notes Library
add_definitions(-DTRANSLATION_DOMAIN="plasma_applet_org.kde.plasma.nerddictation")

set(llxnerddictationwidget_SRCS
    plugin/plugin.cpp
    plugin/NerdDictationWidget.cpp
    plugin/NerdDictationWidgetUtils.cpp
   
)

add_library(nerddictationplugin SHARED ${llxnerddictationwidget_SRCS})

target_link_libraries(nerddictationplugin
                      Qt5::Quick
                      Qt5::Core
                      Qt5::Widgets
                      KF5::CoreAddons
                      KF5::I18n
                      KF5::Notifications
                      KF5::KIOWidgets
                      )

install(FILES plugin/qmldir DESTINATION ${QML_INSTALL_DIR}/org/kde/plasma/private/nerddictation)
install(TARGETS nerddictationplugin DESTINATION ${QML_INSTALL_DIR}/org/kde/plasma/private/nerddictation)

install(FILES "icons/nerd-dictation-on.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-off.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-pause.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)
#install(FILES "knotifications5/llxonedrive.notifyrc"
#        DESTINATION ${DATAROOTDIR}/usr/share/knotifications5/)
