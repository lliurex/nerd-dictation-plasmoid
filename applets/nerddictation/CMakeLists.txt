
#######################################################################################
# Package
plasma_install_package(package org.kde.plasma.nerddictation)


#######################################################################################
# Notes Library
add_definitions(-DTRANSLATION_DOMAIN="plasma_applet_org.kde.plasma.nerddictation")
ecm_add_qml_module(nerddictationplugin URI org.kde.plasma.private.nerddictation)

target_sources(nerddictationplugin PRIVATE
    plugin/plugin.cpp
    plugin/NerdDictationWidget.cpp
    plugin/NerdDictationWidgetUtils.cpp
)


target_link_libraries(nerddictationplugin PRIVATE
                      Qt6::Quick
                      Qt6::Core
                      Qt6::Widgets
                      KF6::CoreAddons
                      KF6::I18n
                      KF6::Notifications
                      KF6::KIOWidgets
                      )
ecm_finalize_qml_module(nerddictationplugin)

install(FILES "icons/nerd-dictation-on.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-off.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-pause.svg"
        DESTINATION ${DATAROOTDIR}/usr/share/icons/hicolor/scalable/apps/)


