#include <kis_tool_humanbodytool.h>

#include <qpainter.h>

#include <kis_debug.h>
#include <klocale.h>

#include <KoViewConverter.h>
#include <KoPointerEvent.h>

#include <kis_canvas2.h>
#include <kis_cursor.h>
#include <kis_view2.h>

#include "HumanBody.h"
#include "HumanBodyDecoration.h"
#include "HumanBodyNode.h"

KisToolHumanBodyTool::KisToolHumanBodyTool(KoCanvasBase * canvas)
    : KisTool(canvas, KisCursor::arrowCursor()), m_canvas( dynamic_cast<KisCanvas2*>(canvas) ), m_selectedNode(0)
{
    Q_ASSERT(m_canvas);
    setObjectName("tool_humanbodytool");
    m_mode = MODE_NOTHING;
}

KisToolHumanBodyTool::~KisToolHumanBodyTool()
{
}

void KisToolHumanBodyTool::activate(bool )
{
    // Add code here to initialize your tool when it got activated
    KisTool::activate();
    m_humanBodyDecoration = dynamic_cast<HumanBodyDecoration*>(m_canvas->decoration("humanBody"));
    kDebug() << m_humanBodyDecoration << m_canvas->decoration("humanBody");
    Q_ASSERT(m_humanBodyDecoration);
    m_humanBodyDecoration->setVisible( true);
}

void KisToolHumanBodyTool::deactivate()
{
    // Add code here to initialize your tool when it got deactivated
    KisTool::deactivate();
}

void KisToolHumanBodyTool::mousePressEvent(KoPointerEvent *event)
{
    m_selectedNode = m_humanBodyDecoration->humanBody()->nodeAt( m_canvas->viewConverter()->viewToDocument( event->pos()) );
    if(m_selectedNode)
    {
        m_mode = MODE_NODEDRAGING;
    }
}


void KisToolHumanBodyTool::mouseMoveEvent(KoPointerEvent *event)
{
    event->ignore();
    if( m_mode == MODE_NODEDRAGING)
    {
        Q_ASSERT(m_selectedNode);
        m_selectedNode->setPosition( m_canvas->viewConverter()->viewToDocument( event->pos() ) );
        m_canvas->updateCanvas(); // TODO update only the relevant part of the canvas
    }
}

void KisToolHumanBodyTool::mouseReleaseEvent(KoPointerEvent *event)
{
    Q_UNUSED(event);
    if( m_mode == MODE_NODEDRAGING)
    {
        m_selectedNode = 0;
        m_mode = MODE_NOTHING;
    }
}

void KisToolHumanBodyTool::paint(QPainter& gc, const KoViewConverter &converter)
{
    Q_UNUSED(gc);
    Q_UNUSED(converter);
}

// Uncomment if you have a configuration widget
// QWidget* KisToolHumanBodyTool::createOptionWidget()
// {
//     return 0;
// }
//
// QWidget* KisToolHumanBodyTool::optionWidget()
// {
//         return 0;
// }


#include "kis_tool_humanbodytool.moc"
