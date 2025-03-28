#include "canvas.h"
#include <QPainter>
#include <QPen>
#include <QRandomGenerator>
#include <cmath>

Canvas::Canvas(QObject *parent) : QObject(parent)
{
    m_image = QImage(800, 600, QImage::Format_ARGB32);
    m_image.fill(Qt::white);
}

const QImage& Canvas::image() const
{
    return m_image;
}

void Canvas::resize(const QSize &newSize)
{
    if (m_image.size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), m_image);
    m_image = newImage;

    emit imageUpdated(m_image);
}

bool Canvas::load(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    m_image = loadedImage.convertToFormat(QImage::Format_ARGB32);
    emit imageUpdated(m_image);
    return true;
}

void Canvas::clear()
{
    m_image.fill(Qt::white);
    emit imageUpdated(m_image);
}

bool Canvas::save(const QString &filePath)
{
    return m_image.save(filePath);
}

void Canvas::drawLine(const QPoint &from, const QPoint &to, const QPen &pen)
{
    QPainter painter(&m_image);
    painter.setPen(pen);
    painter.drawLine(from, to);
    emit imageUpdated(m_image);
}

void Canvas::drawSpray(const QPoint &center, int radius, int pointCount, const QColor &color)
{
    QPainter painter(&m_image);
    painter.setPen(QPen(color, 1));

    for (int i = 0; i < pointCount; ++i) {
        int angle = QRandomGenerator::global()->bounded(360);
        int distance = QRandomGenerator::global()->bounded(radius);

        int x = center.x() + distance * cos(angle * M_PI / 180);
        int y = center.y() + distance * sin(angle * M_PI / 180);

        painter.drawPoint(x, y);
    }

    emit imageUpdated(m_image);
}
