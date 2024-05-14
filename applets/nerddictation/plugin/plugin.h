
#ifndef NERD_DICTATION_WIDGET_WATCH_PLUGIN_H
#define NERD_DICTATION_WIDGET_WATCH_PLUGIN_H

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class NerdDictationWidgetPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
/*    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")*/
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) Q_DECL_OVERRIDE;
};

#endif // NERD_DICTATION_WIDGET_WATCH_PLUGIN_H
