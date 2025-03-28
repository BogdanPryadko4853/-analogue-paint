#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "basetool.h"

class EraserTool : public BaseTool
{
    Q_OBJECT
public:
    explicit EraserTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

private:
    QPoint m_lastPoint;
    bool m_drawing;
};

#endif
