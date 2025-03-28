#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QImage>
#include <memory>

class Canvas : public QObject
{
    Q_OBJECT
public:
    using Ptr = std::unique_ptr<Canvas>;

    explicit Canvas(QObject *parent = nullptr);

    static Ptr create(QObject *parent = nullptr) {
        return Ptr(new Canvas(parent));
    }

    const QImage& image() const;
    void resize(const QSize &newSize);
    void clear();
    bool save(const QString &filePath);
    bool load(const QString &filePath);

    void drawLine(const QPoint &from, const QPoint &to, const QPen &pen);
    void drawSpray(const QPoint &center, int radius, int pointCount, const QColor &color);
    QImage& mutableImage() { return m_image; }

signals:
    void imageUpdated(const QImage &image);

private:
    QImage m_image;
};

#endif // CANVAS_H
