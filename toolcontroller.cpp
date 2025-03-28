#include "toolcontroller.h"
#include "pentool.h"
#include "erasetool.h"
#include "spraytool.h"
#include "brushtool.h"

ToolController::ToolController(QObject *parent) : QObject(parent)
{
    m_currentTool = new PenTool(this);
    m_currentPen = QPen(Qt::black, 3, Qt::SolidLine);
}

ToolController::~ToolController()
{
    qDeleteAll(findChildren<BaseTool*>());
}

void ToolController::setCurrentTool(BaseTool *tool)
{
    if (m_currentTool) {
        m_currentTool->deleteLater();
    }

    m_currentTool = tool;

    if (qobject_cast<EraserTool*>(tool)) {
        QPen eraserPen(Qt::white, m_currentPen.width()*2,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        m_currentTool->setPen(eraserPen);
    } else {
        m_currentTool->setPen(m_currentPen);
    }
}

BaseTool* ToolController::currentTool() const
{
    return m_currentTool;
}

void ToolController::setPen(const QPen &pen)
{
    m_currentPen = pen;

    if (m_currentTool) {
        if (qobject_cast<EraserTool*>(m_currentTool)) {
            QPen eraserPen = pen;
            eraserPen.setWidth(pen.width() * 2);
            eraserPen.setColor(Qt::white);
            m_currentTool->setPen(eraserPen);
        } else {
            m_currentTool->setPen(pen);
        }
    }
}

QPen ToolController::pen() const
{
    return m_currentPen;
}

void ToolController::onMousePress(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool) {
        m_currentTool->onMousePress(point, canvas);
    }
}

void ToolController::onMouseMove(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool) {
        m_currentTool->onMouseMove(point, canvas);
    }
}

void ToolController::onMouseRelease(const QPoint &point, Canvas *canvas)
{
    if (m_currentTool) {
        m_currentTool->onMouseRelease(point, canvas);
    }
}

void ToolController::setBrushStyle(Qt::PenStyle style)
{
    BrushTool* brushTool = qobject_cast<BrushTool*>(m_currentTool);
    if (brushTool) {
        brushTool->setBrushStyle(style);
    }
}
