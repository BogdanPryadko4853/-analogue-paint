#include "brushtool.h"
#include "canvas.h"

BrushTool::BrushTool(QObject *parent) : BaseTool(parent),
    m_brushStyle(Qt::SolidLine)
{
    QPen brushPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(brushPen);
}

void BrushTool::setBrushStyle(Qt::PenStyle style)
{
    m_brushStyle = style;
    QPen p = pen();
    p.setStyle(style);
    setPen(p);
}

void BrushTool::onMousePress(const QPoint &point, Canvas *canvas)
{
    m_lastPoint = point;
    if (canvas) {
        QPen p = pen();
        p.setStyle(m_brushStyle);
        canvas->drawLine(point, point, p);
    }
}

void BrushTool::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (canvas) {
        QPen p = pen();
        p.setStyle(m_brushStyle);
        canvas->drawLine(m_lastPoint, point, p);
        m_lastPoint = point;
    }
}

void BrushTool::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    if (canvas) {
        QPen p = pen();
        p.setStyle(m_brushStyle);
        canvas->drawLine(m_lastPoint, point, p);
    }
}
