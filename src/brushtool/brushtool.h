#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "../basetool/basetool.h"

class BrushTool : public BaseTool
{
    Q_OBJECT
public:
    explicit BrushTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

    void setBrushStyle(Qt::PenStyle style);

private:
    Qt::PenStyle m_brushStyle;
};

#endif
