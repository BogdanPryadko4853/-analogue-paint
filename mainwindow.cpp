#include "mainwindow.h"
#include "toolcontroller.h"
#include "pentool.h"
#include "erasetool.h"
#include "spraytool.h"
#include "brushtool.h"

#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QSpinBox>
#include <QRandomGenerator>
#include <QActionGroup>
#include <QPixmap>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_canvas(new Canvas(this)),
    m_toolController(new ToolController(this))
{


    setWindowTitle("Advanced Paint");
    resize(800, 600);

    m_displayImage = m_canvas->image();

    connect(m_canvas, &Canvas::imageUpdated, this, &MainWindow::onImageUpdated);

    createMenuBar();
    setupTools();
    setupBrushStyles();

    QString menuStyle =
        "QMenuBar {"
        "    background-color: #505050;"
        "    color: white;"
        "    border: 1px solid #404040;"
        "}"
        "QMenuBar::item {"
        "    background: transparent;"
        "    padding: 5px 10px;"
        "}"
        "QMenuBar::item:selected {"
        "    background: #606060;"
        "}"
        "QMenu {"
        "    background-color: #505050;"
        "    color: white;"
        "    border: 1px solid #404040;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #0078d7;"
        "}";

    this->setStyleSheet(menuStyle);

    QString toolBarStyle =
        "QToolBar {"
        "    background-color: #505050;"
        "    border: 1px solid #404040;"
        "    spacing: 5px;"
        "    padding: 3px;"
        "}"
        "QToolButton {"
        "    background-color: #606060;"
        "    color: white;"
        "    border: 1px solid #505050;"
        "    padding: 5px;"
        "    min-width: 30px;"
        "}"
        "QToolButton:hover {"
        "    background-color: #707070;"
        "}"
        "QToolButton:pressed, QToolButton:checked {"
        "    background-color: #0078d7;"
        "}";

    foreach (QToolBar *tb, this->findChildren<QToolBar*>()) {
        tb->setStyleSheet(toolBarStyle);
    }
}


void MainWindow::newFile()
{
    m_canvas->clear();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        if (!m_canvas->load(fileName)) {
            QMessageBox::warning(this, tr("Error"), tr("Could not load image"));
        }
    }
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
                                                    tr("PNG Image (*.png);;JPEG Image (*.jpg *.jpeg);;Bitmap (*.bmp)"));
    if (!fileName.isEmpty()) {
        if (!m_canvas->save(fileName)) {
            QMessageBox::warning(this, tr("Error"), tr("Could not save image"));
        }
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupTools()
{
    QToolBar *mainToolBar = addToolBar("Main Tools");
    mainToolBar->setStyleSheet(
        "QToolBar { background: #f0f0f0; border: none; }"
        "QToolButton { background: #444; color: white; border: 1px solid #555; padding: 5px; }"
        "QToolButton:hover { background: #666; }"
        "QToolButton:pressed { background: #222; }"
        "QToolButton:checked { background: #0078d7; }"
        );

    m_toolGroup = new QActionGroup(this);

    auto createToolAction = [this](const QString &iconPath, const QString &text, BaseTool *tool) {
        QAction *action = new QAction(QIcon(iconPath), text, this);
        action->setCheckable(true);
        m_toolGroup->addAction(action);
        connect(action, &QAction::triggered, [this, tool]() {
            m_toolController->setCurrentTool(tool);
        });
        return action;
    };

    createToolAction(":/icons/pen.png", "Pen", new PenTool(this))->setChecked(true);
    createToolAction(":/icons/brush.png", "Brush", new BrushTool(this));
    createToolAction(":/icons/eraser.png", "Eraser", new EraserTool(this));
    createToolAction(":/icons/spray.png", "Spray", new SprayTool(this));

    QSpinBox *widthSpinBox = new QSpinBox(this);
    widthSpinBox->setRange(1, 50);
    widthSpinBox->setValue(m_toolController->pen().width());
    widthSpinBox->setFixedWidth(60);
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int width) {

                QPen pen = m_toolController->pen();
                pen.setWidth(width);

                m_toolController->setPen(pen);

                if (EraserTool* eraser = qobject_cast<EraserTool*>(
                        m_toolController->currentTool())) {
                    QPen eraserPen = pen;
                    eraserPen.setWidth(width * 2);
                    eraser->setPen(eraserPen);
                    m_toolController->setPen(pen);
                }
            });
    mainToolBar->addWidget(widthSpinBox);

    QAction *colorAction = new QAction(QIcon(":/icons/color.png"), "Color", this);
    connect(colorAction, &QAction::triggered, this, &MainWindow::onColorClicked);
    mainToolBar->addAction(colorAction);

    QAction *clearAction = new QAction(QIcon(":/icons/clear.png"), "Clear", this);
    connect(clearAction, &QAction::triggered, this, &MainWindow::onClearClicked);
    mainToolBar->addAction(clearAction);

    QAction *saveAction = new QAction(QIcon(":/icons/save.png"), "Save", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveClicked);
    mainToolBar->addAction(saveAction);
}


