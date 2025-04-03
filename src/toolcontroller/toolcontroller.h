#ifndef TOOLCONTROLLER_H
#define TOOLCONTROLLER_H

#include <QObject>
#include <QPen>
#include "../smart_ptr.h"
#include "../basetool/basetool.h"

class PenTool;
class BrushTool;
class EraserTool;
class SprayTool;
class Canvas;

class ToolController : public QObject
{
    Q_OBJECT
public:
    explicit ToolController(QObject *parent = nullptr);
    ~ToolController() = default;

    void setCurrentTool(smart_ptr<BaseTool> tool);
    BaseTool* currentTool() const;

    void setPen(const QPen &pen);
    const QPen& pen() const;

    void onMousePress(const QPoint &point, Canvas *canvas);
    void onMouseMove(const QPoint &point, Canvas *canvas);
    void onMouseRelease(const QPoint &point, Canvas *canvas);
    void setBrushStyle(Qt::PenStyle style);

    static smart_ptr<PenTool> createPenTool(QObject* parent);
    static smart_ptr<BrushTool> createBrushTool(QObject* parent);
    static smart_ptr<EraserTool> createEraserTool(QObject* parent);
    static smart_ptr<SprayTool> createSprayTool(QObject* parent);

private:
    void updateCurrentToolPen();

    smart_ptr<BaseTool> m_currentTool;
    QPen m_currentPen;
};

#endif // TOOLCONTROLLER_H
