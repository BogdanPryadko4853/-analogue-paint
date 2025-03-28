#ifndef TOOLCONTROLLER_H
#define TOOLCONTROLLER_H

#include <QObject>
#include <QPen>
#include <memory>
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

    void setCurrentTool(std::unique_ptr<BaseTool> tool);
    BaseTool* currentTool() const;

    void setPen(const QPen &pen);
    const QPen& pen() const;

    void onMousePress(const QPoint &point, Canvas *canvas);
    void onMouseMove(const QPoint &point, Canvas *canvas);
    void onMouseRelease(const QPoint &point, Canvas *canvas);
    void setBrushStyle(Qt::PenStyle style);

    static std::unique_ptr<PenTool> createPenTool(QObject* parent);
    static std::unique_ptr<BrushTool> createBrushTool(QObject* parent);
    static std::unique_ptr<EraserTool> createEraserTool(QObject* parent);
    static std::unique_ptr<SprayTool> createSprayTool(QObject* parent);

private:
    void updateCurrentToolPen();

    std::unique_ptr<BaseTool> m_currentTool;
    QPen m_currentPen;
};

#endif // TOOLCONTROLLER_H
