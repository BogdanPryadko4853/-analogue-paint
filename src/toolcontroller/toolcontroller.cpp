#include "toolcontroller.h"
#include "../pentool/pentool.h"
#include "../erasetool/erasetool.h"
#include "../spraytool/spraytool.h"
#include "../brushtool/brushtool.h"

ToolController::ToolController(QObject *parent)
    : QObject(parent),
    m_currentTool(smart_ptr<BaseTool>::make_derived<PenTool>(parent)),
    m_currentPen(Qt::black, 3, Qt::SolidLine)
{
}

void ToolController::setCurrentTool(smart_ptr<BaseTool> tool)
{
    if (!tool) return;

    if (auto* eraser = dynamic_cast<EraserTool*>(tool.get())) {
        QPen eraserPen(Qt::white, m_currentPen.width() * 2,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        tool->setPen(eraserPen);
    } else {
        tool->setPen(m_currentPen);
    }

    m_currentTool = std::move(tool);
}

BaseTool* ToolController::currentTool() const
{
    return m_currentTool.get();
}

void ToolController::setPen(const QPen &pen)
{
    if (m_currentPen == pen) return;

    m_currentPen = pen;
    updateCurrentToolPen();
}

const QPen& ToolController::pen() const
{
    return m_currentPen;
}

void ToolController::updateCurrentToolPen()
{
    if (!m_currentTool) return;

    if (auto eraser = dynamic_cast<EraserTool*>(m_currentTool.get())) {
        QPen eraserPen = m_currentPen;
        eraserPen.setWidth(m_currentPen.width() * 2);
        eraserPen.setColor(Qt::white);
        eraser->setPen(eraserPen);
    } else {
        m_currentTool->setPen(m_currentPen);
    }
}

void ToolController::onMousePress(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool && canvas) {
        m_currentTool->onMousePress(point, canvas);
    }
}

void ToolController::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool && canvas) {
        m_currentTool->onMouseMove(point, canvas);
    }
}

void ToolController::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool && canvas) {
        m_currentTool->onMouseRelease(point, canvas);
    }
}

void ToolController::setBrushStyle(Qt::PenStyle style)
{
    if (auto brushTool = dynamic_cast<BrushTool*>(m_currentTool.get())) {
        brushTool->setBrushStyle(style);
    }
}


smart_ptr<PenTool> ToolController::createPenTool(QObject* parent) {
    return smart_ptr<PenTool>(new PenTool(parent));
}

smart_ptr<BrushTool> ToolController::createBrushTool(QObject* parent) {
    return smart_ptr<BrushTool>(new BrushTool(parent));
}

smart_ptr<EraserTool> ToolController::createEraserTool(QObject* parent) {
    return smart_ptr<EraserTool>(new EraserTool(parent));
}

smart_ptr<SprayTool> ToolController::createSprayTool(QObject* parent) {
    return smart_ptr<SprayTool>(new SprayTool(parent));
}
