#ifndef SPRAYTOOL_H
#define SPRAYTOOL_H

#include <memory>
#include "../basetool/basetool.h"

class SprayTool : public BaseTool
{
    Q_OBJECT
public:
    explicit SprayTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

    static std::unique_ptr<SprayTool> create(QObject *parent = nullptr) {
        return std::unique_ptr<SprayTool>(new SprayTool(parent));
    }

private:
    void drawExplosiveSpray(const QPoint &center, Canvas *canvas);
    QPoint m_lastPoint;
};

#endif // SPRAYTOOL_H
