#include "plugin.h"
#include "NerdDictationWidget.h"
#include <QtQml>

void NerdDictationWidgetPlugin::registerTypes (const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.plasma.private.nerddictation"));
    qmlRegisterType<NerdDictationWidget>(uri, 1, 0, "NerdDictationWidget");
    qmlRegisterType<NerdDictationWidgetUtils>(uri, 1, 0, "NerDictationWidgetUtils");

}
