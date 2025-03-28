#include "basetool.h"
#include "canvas.h"

BaseTool::BaseTool(QObject *parent) : QObject(parent)
{
    m_pen = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void BaseTool::setPen(const QPen &pen)
{
    m_pen = pen;
}

const QPen& BaseTool::pen() const
{
    return m_pen;
}
