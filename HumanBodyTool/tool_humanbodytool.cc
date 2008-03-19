#include <stdlib.h>
#include <vector>

#include <qpoint.h>

#include <klocale.h>
#include <kiconloader.h>
#include <kcomponentdata.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>
#include <kis_debug.h>
#include <kgenericfactory.h>

#include <kis_global.h>
#include <kis_types.h>
#include <KoToolRegistry.h>

#include "tool_humanbodytool.h"
#include "kis_tool_humanbodytool.h"


typedef KGenericFactory<HumanBodyToolPlugin> HumanBodyToolFactory;
K_EXPORT_COMPONENT_FACTORY( kritatoolhumanbodytool, HumanBodyToolFactory( "krita" ) )


HumanBodyToolPlugin::HumanBodyToolPlugin(QObject *parent, const QStringList &)
    : KParts::Plugin(parent)
{
    kDebug() << "HumanBodyToolPlugin";
    setComponentData(HumanBodyToolFactory::componentData());

    KoToolRegistry * r = KoToolRegistry::instance();
    r->add(new KisToolHumanBodyToolFactory(r, QStringList()));
}

HumanBodyToolPlugin::~HumanBodyToolPlugin()
{
}

#include "tool_humanbodytool.moc"
