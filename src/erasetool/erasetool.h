#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include <memory>
#include "../basetool/basetool.h"

class EraserTool : public BaseTool
{
    Q_OBJECT
public:
    explicit EraserTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

    static std::unique_ptr<EraserTool> create(QObject *parent = nullptr) {
        return std::unique_ptr<EraserTool>(new EraserTool(parent));
    }

private:
    QPoint m_lastPoint;
    bool m_drawing;
};

#endif // ERASERTOOL_H
