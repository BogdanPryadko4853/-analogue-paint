#ifndef SPRAYTOOL_H
#define SPRAYTOOL_H

#include "../basetool/basetool.h"

class SprayTool : public BaseTool
{
    Q_OBJECT
public:
    explicit SprayTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

private:
    void drawExplosiveSpray(const QPoint &center, Canvas *canvas);
    QPoint m_lastPoint;
};

#endif // SPRAYTOOL_H
