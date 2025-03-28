#include "erasetool.h".h"
#include "canvas.h"
#include <QPainter>

EraserTool::EraserTool(QObject *parent) : BaseTool(parent), m_drawing(false)
{
    QPen eraserPen(Qt::white, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(eraserPen);
}

void EraserTool::onMousePress(const QPoint &point, Canvas *canvas)
{
    if (!canvas) return;

    m_drawing = true;
    m_lastPoint = point;

    QImage &image = canvas->mutableImage();
    QPainter painter(&image);

    painter.setPen(pen());
    painter.drawEllipse(point, pen().width()/2, pen().width()/2);

    emit canvas->imageUpdated(image);
}

void EraserTool::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (!m_drawing || !canvas) return;

    QImage &image = canvas->mutableImage();
    QPainter painter(&image);
    painter.setPen(pen());

    painter.drawLine(m_lastPoint, point);
    m_lastPoint = point;

    emit canvas->imageUpdated(image);
}

void EraserTool::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    if (!m_drawing || !canvas) return;

    m_drawing = false;

    QImage &image = canvas->mutableImage();
    QPainter painter(&image);
    painter.setPen(pen());
    painter.drawLine(m_lastPoint, point);

    emit canvas->imageUpdated(image);
}
