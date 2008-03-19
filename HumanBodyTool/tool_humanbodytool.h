#ifndef _HUMANBODYTOOL_H_
#define _HUMANBODYTOOL_H_

#include <kparts/plugin.h>

class KisView;

class HumanBodyToolPlugin : public KParts::Plugin
{
    Q_OBJECT
public:
    HumanBodyToolPlugin(QObject *parent, const QStringList &);
    virtual ~HumanBodyToolPlugin();

private:

    KisView * m_view;

};

#endif
