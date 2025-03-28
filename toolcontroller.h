#ifndef TOOLCONTROLLER_H
#define TOOLCONTROLLER_H

#include <QObject>
#include <QPen>
#include "basetool.h"

class Canvas;

class ToolController : public QObject
{
    Q_OBJECT
public:
    explicit ToolController(QObject *parent = nullptr);
    ~ToolController();

    void setCurrentTool(BaseTool *tool);
    BaseTool* currentTool() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void onMousePress(const QPoint &point, Canvas *canvas);
    void onMouseMove(const QPoint &point, Canvas *canvas);
    void onMouseRelease(const QPoint &point, Canvas *canvas);
    void setBrushStyle(Qt::PenStyle style);

private:
    BaseTool *m_currentTool;
    QPen m_currentPen;
};

#endif // TOOLCONTROLLER_H
