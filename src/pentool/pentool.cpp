#include "pentool.h"
#include "../canvas/canvas.h"

PenTool::PenTool(QObject *parent) : BaseTool(parent)
{
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
}

void PenTool::onMousePress(const QPoint &point, Canvas *canvas)
{
    m_lastPoint = point;
}

void PenTool::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (canvas) {
        canvas->drawLine(m_lastPoint, point, m_pen);
        m_lastPoint = point;
    }
}

void PenTool::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    if (canvas) {
        canvas->drawLine(m_lastPoint, point, m_pen);
    }
}
