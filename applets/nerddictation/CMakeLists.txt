
#######################################################################################
# Package
plasma_install_package(package org.kde.plasma.nerddictation)


#######################################################################################
# Notes Library
set(PLUGIN_TARGET "nerddictationplugin")
add_definitions(-DTRANSLATION_DOMAIN="plasma_applet_org.kde.plasma.nerddictation")
ecm_add_qml_module(${PLUGIN_TARGET} URI org.kde.plasma.private.nerddictation)

target_sources(${PLUGIN_TARGET} PRIVATE
    plugin/plugin.cpp
    plugin/NerdDictationWidget.cpp
    plugin/NerdDictationWidgetUtils.cpp
    plugin/plugin.h
    plugin/NerdDictationWidget.h
    plugin/NerdDictationWidgetUtils.h
)


target_link_libraries(${PLUGIN_TARGET} PRIVATE
                      Qt6::Quick
                      Qt6::Core
                      Qt6::Widgets
                      KF6::CoreAddons
                      KF6::I18n
                      KF6::Notifications
                      KF6::KIOWidgets
                      )
target_include_directories(${PLUGIN_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/plugin)                      
ecm_finalize_qml_module(${PLUGIN_TARGET})

install(TARGETS ${PLUGIN_TARGET} DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/nerddictation)

install(FILES "icons/nerd-dictation-on.svg"
        DESTINATION ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-off.svg"
        DESTINATION ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps/)
install(FILES "icons/nerd-dictation-pause.svg"
        DESTINATION ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps/)


