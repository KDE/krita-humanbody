#ifndef _KIS_TOOL_HUMANBODYTOOL_H_
#define _KIS_TOOL_HUMANBODYTOOL_H_

#include <kis_tool.h>
#include <KoToolFactory.h>

class HumanBodyDecoration;
class HumanBodyNode;
class KisCanvas2;

class KisToolHumanBodyTool : public KisTool {
    Q_OBJECT
    enum Mode {
        MODE_NOTHING,
        MODE_NODEDRAGING
    };
public:
    KisToolHumanBodyTool(KoCanvasBase * canvas);
    virtual ~KisToolHumanBodyTool();

    virtual quint32 priority() { return 3; }
    virtual void mousePressEvent(KoPointerEvent *event);
    virtual void mouseMoveEvent(KoPointerEvent *event);
    virtual void mouseReleaseEvent(KoPointerEvent *event);

// Uncomment if you have a configuration widget
//     QWidget* createOptionWidget();
//     virtual QWidget* optionWidget();

public slots:
    virtual void activate(bool temp = false);
    void deactivate();

protected:
    
    virtual void paint(QPainter& gc, const KoViewConverter &converter);

protected:
    QPointF m_dragStart;
    QPointF m_dragEnd;
    KisCanvas2* m_canvas;
    HumanBodyDecoration* m_humanBodyDecoration;
    Mode m_mode;
    HumanBodyNode* m_selectedNode;
};


class KisToolHumanBodyToolFactory : public KoToolFactory {
public:
    KisToolHumanBodyToolFactory(QObject *parent, const QStringList&)
        : KoToolFactory(parent, "KisToolHumanBodyTool", i18n( "Human body" ))
        {
            setToolTip( i18n( "Human body editor tool" ) );
            setToolType( TOOL_TYPE_VIEW );
            setIcon( "tool_humanbodytool" );
            setPriority( 0 );
        };


    virtual ~KisToolHumanBodyToolFactory() {}

    virtual KoTool * createTool(KoCanvasBase * canvas) {
        return new KisToolHumanBodyTool(canvas);
    }

};


#endif

