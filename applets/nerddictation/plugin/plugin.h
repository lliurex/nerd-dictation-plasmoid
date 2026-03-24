
#ifndef NERD_DICTATION_WIDGET_WATCH_PLUGIN_H
#define NERD_DICTATION_WIDGET_WATCH_PLUGIN_H

#include <QQmlEngineExtensionPlugin>

class NerdDictationWidgetPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

public:
    using QQmlEngineExtensionPlugin::QQmlEngineExtensionPlugin;
};

#endif // NERD_DICTATION_WIDGET_WATCH_PLUGIN_H
