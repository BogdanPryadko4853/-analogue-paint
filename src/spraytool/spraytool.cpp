#include "spraytool.h"
#include "../canvas/canvas.h"
#include <QPainter>
#include <QRandomGenerator>
#include <cmath>

SprayTool::SprayTool(QObject *parent) : BaseTool(parent)
{
    QPen sprayPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(sprayPen);
}

void SprayTool::onMousePress(const QPoint &point, Canvas *canvas)
{
    if (canvas) {
        drawExplosiveSpray(point, canvas);
        m_lastPoint = point;
    }
}

void SprayTool::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (canvas && (point - m_lastPoint).manhattanLength() > 5) {
        drawExplosiveSpray(point, canvas);
        m_lastPoint = point;
    }
}

void SprayTool::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    Q_UNUSED(point);
    Q_UNUSED(canvas);
}

void SprayTool::drawExplosiveSpray(const QPoint &center, Canvas *canvas)
{
    QImage &image = canvas->mutableImage();
    QPainter painter(&image);
    painter.setPen(pen());

    int radius = pen().width() * 3;
    int density = 50 + pen().width() * 15;

    auto& rng = *QRandomGenerator::global();
    for (int i = 0; i < density; ++i) {
        double distance = rng.bounded(radius) * rng.bounded(1.0);
        double angle = rng.bounded(2 * M_PI);

        int x = center.x() + std::lround(distance * std::cos(angle));
        int y = center.y() + std::lround(distance * std::sin(angle));

        painter.drawPoint(x, y);
    }

    emit canvas->imageUpdated(canvas->image());
}
