#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas/canvas.h"
#include "toolcontroller/toolcontroller.h"
#include "smart_ptr.h"

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

    smart_ptr<Canvas> m_canvas;
    smart_ptr<ToolController> m_toolController;
    QImage m_displayImage;
    QActionGroup* m_toolGroup;
    QActionGroup* m_brushStyleGroup;
};

#endif // MAINWINDOW_H
