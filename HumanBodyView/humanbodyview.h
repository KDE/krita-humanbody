#ifndef _HUMANBODYVIEW_H_
#define _HUMANBODYVIEW_H_

#include <kparts/plugin.h>

class KisView2;

/**
 * Template of view plugin
 */
class HumanBodyViewPlugin : public KParts::Plugin
{
    Q_OBJECT
public:
    HumanBodyViewPlugin(QObject *parent, const QStringList &);
    virtual ~HumanBodyViewPlugin();

private:

    KisView2 * m_view;

};

#endif // HumanBodyViewPlugin_H
