#include "pentool.h"
#include "canvas.h"

PenTool::PenTool(QObject *parent) : BaseTool(parent)
{
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
