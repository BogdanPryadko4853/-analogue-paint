#ifndef PENTOOL_H
#define PENTOOL_H

#include <memory>
#include "../basetool/basetool.h"

class PenTool : public BaseTool
{
    Q_OBJECT
public:
    explicit PenTool(QObject *parent = nullptr);

    void onMousePress(const QPoint &point, Canvas *canvas) override;
    void onMouseMove(const QPoint &point, Canvas *canvas) override;
    void onMouseRelease(const QPoint &point, Canvas *canvas) override;

    static std::unique_ptr<PenTool> create(QObject *parent = nullptr) {
        return std::unique_ptr<PenTool>(new PenTool(parent));
    }
};

#endif // PENTOOL_H
