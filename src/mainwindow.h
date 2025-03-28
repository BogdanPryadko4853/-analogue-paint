#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "canvas/canvas.h"
#include "toolcontroller/toolcontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onColorClicked();
    void onClearClicked();
    void onSaveClicked();
    void onPenWidthChanged(int width);
    void onBrushStyleSelected(QAction* action);
    void onImageUpdated(const QImage &image);
    void newFile();
    void open();
    void save();

private:
    void createMenuBar();
    void setupTools();
    void setupBrushStyles();
    void setupStyleSheets();
    void initializeCanvas();
    void initializeToolController();

    std::unique_ptr<Canvas> m_canvas;
    std::unique_ptr<ToolController> m_toolController;
    QImage m_displayImage;
    QActionGroup* m_toolGroup;
    QActionGroup* m_brushStyleGroup;
};

#endif // MAINWINDOW_H
