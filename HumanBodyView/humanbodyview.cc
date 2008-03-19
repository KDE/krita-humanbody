#include "humanbodyview.h"

#include <stdlib.h>

#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kis_debug.h>
#include <kgenericfactory.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include "kis_canvas2.h"
#include "kis_config.h"
#include "kis_cursor.h"
#include "kis_global.h"
#include "kis_types.h"
#include "kis_view2.h"

#include "HumanBodyDecoration.h"

typedef KGenericFactory<HumanBodyViewPlugin> HumanBodyViewPluginFactory;
K_EXPORT_COMPONENT_FACTORY( kritahumanbodyview, HumanBodyViewPluginFactory( "krita" ) )


HumanBodyViewPlugin::HumanBodyViewPlugin(QObject *parent, const QStringList &)
    : KParts::Plugin(parent)
{
    if ( parent->inherits("KisView2") )
    {
        m_view = (KisView2*) parent;

        setComponentData(HumanBodyViewPluginFactory::componentData());

        setXMLFile(KStandardDirs::locate("data","kritaplugins/humanbodyview.rc"), true);

        KAction *action  = new KAction(i18n("&Show human body"), this);
        actionCollection()->addAction("ShowHumanBody", action );
        
        HumanBodyDecoration* hbd = new HumanBodyDecoration( m_view );
        m_view->canvasBase()->addDecoration( hbd );
        
        connect(action, SIGNAL(triggered()), hbd, SLOT(toggleVisibility()));
    }
}

HumanBodyViewPlugin::~HumanBodyViewPlugin()
{
    m_view = 0;
}

#include "humanbodyview.moc"
