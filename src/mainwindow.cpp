#include "mainwindow.h"
#include "pentool/pentool.h"
#include "erasetool/erasetool.h"
#include "spraytool/spraytool.h"
#include "brushtool/brushtool.h"
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QSpinBox>
#include <QActionGroup>
#include <QPixmap>
#include <QMenuBar>
#include <QMenu>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_canvas(new Canvas(this)),
    m_toolController(new ToolController(this)),
    m_toolGroup(new QActionGroup(this)),
    m_brushStyleGroup(new QActionGroup(this))
{
    setWindowTitle("Advanced Paint");
    resize(800, 600);

    m_displayImage = m_canvas->image();
     connect(m_canvas.get(), &Canvas::imageUpdated, this, &MainWindow::onImageUpdated);

    setupStyleSheets();
    createMenuBar();
    setupTools();
    setupBrushStyles();
}

void MainWindow::setupStyleSheets()
{
    QString combinedStyle =
        "QMainWindow {"
        "    background-color: #404040;"
        "}"

        "QSpinBox {"
        "    background-color: #606060;"
        "    color: #d0d0d0;"
        "    border: 1px solid #505050;"
        "    border-radius: 3px;"
        "    padding: 2px;"
        "}"
        "QSpinBox::up-button, QSpinBox::down-button {"
        "    subcontrol-origin: border;"
        "    width: 20px;"
        "    border-left: 1px solid #505050;"
        "}"
        "QSpinBox::up-arrow, QSpinBox::down-arrow {"
        "    image: none;"
        "    width: 0;"
        "    height: 0;"
        "}"

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
        "}"

        "QToolBar {"
        "    background-color: #505050;"
        "    border: 1px solid #404040;"
        "    spacing: 5px;"
        "    padding: 3px;"
        "}"
        "QToolBar::separator {"
        "    background: #606060;"
        "    width: 2px;"
        "    margin: 5px 8px;"
        "}"

        "QToolButton {"
        "    background-color: #606060;"
        "    color: white;"
        "    border: 1px solid #505050;"
        "    border-radius: 3px;"
        "    padding: 5px;"
        "    min-width: 30px;"
        "}"
        "QToolButton:hover {"
        "    background-color: #707070;"
        "}"
        "QToolButton:pressed, QToolButton:checked {"
        "    background-color: #0078d7;"
        "}";

    this->setStyleSheet(combinedStyle);
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

void MainWindow::setupTools()
{
    QToolBar *mainToolBar = addToolBar("Main Tools");

    auto addTool = [this, mainToolBar](const QString& icon, const QString& name, BaseTool* tool) {
        QAction* action = new QAction(QIcon(icon), name, this);
        action->setCheckable(true);
        m_toolGroup->addAction(action);
        connect(action, &QAction::triggered, [this, tool] {
            m_toolController->setCurrentTool(std::unique_ptr<BaseTool>(tool));
        });
        mainToolBar->addAction(action);
        return action;
    };



    QSpinBox *widthSpinBox = new QSpinBox(this);

    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onPenWidthChanged);
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

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&New", this, &MainWindow::newFile);
    fileMenu->addAction("&Open...", this, &MainWindow::open);
    fileMenu->addAction("&Save", this, &MainWindow::save);
    fileMenu->addSeparator();
    fileMenu->addAction("&Exit", qApp, &QApplication::quit);

    QMenu *toolsMenu = menuBar->addMenu("&Tools");
    QActionGroup *toolsGroup = new QActionGroup(this);

    auto addToolAction = [toolsMenu, toolsGroup](const QString& icon, const QString& name, int id) {
        QAction* action = toolsMenu->addAction(QIcon(icon), name);
        action->setCheckable(true);
        action->setData(id);
        toolsGroup->addAction(action);
        return action;
    };

    addToolAction(":/icons/pen.png", "&Pen", 1)->setChecked(true);
    addToolAction(":/icons/brush.png", "&Brush", 2);
    addToolAction(":/icons/eraser.png", "&Eraser", 3);
    addToolAction(":/icons/spray.png", "&Spray", 4);

    connect(toolsGroup, &QActionGroup::triggered, this, [this](QAction* action) {
        switch(action->data().toInt()) {
        case 1:
            m_toolController->setCurrentTool(std::make_unique<PenTool>(this));
            break;
        case 2:
            m_toolController->setCurrentTool(std::make_unique<BrushTool>(this));
            break;
        case 3: {
            auto eraser = std::make_unique<EraserTool>(this);
            eraser->setPen(QPen(Qt::white, m_toolController->pen().width()*2,
                                Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            m_toolController->setCurrentTool(std::move(eraser));
            break;
        }
        case 4:
            m_toolController->setCurrentTool(std::make_unique<SprayTool>(this));
            break;
        }
    });
}

void MainWindow::setupBrushStyles()
{
    QToolBar *brushToolBar = addToolBar("Brush Styles");

    auto createStyleAction = [this](const QString& text, Qt::PenStyle style) {
        QAction *action = new QAction(text, this);
        action->setCheckable(true);
        action->setData(static_cast<int>(style));

        QPixmap pixmap(32, 32);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(QPen(Qt::black, 2, style));
        painter.drawLine(5, 16, 27, 16);
        action->setIcon(QIcon(pixmap));

        m_brushStyleGroup->addAction(action);
        return action;
    };

    createStyleAction("Solid", Qt::SolidLine)->setChecked(true);
    createStyleAction("Dash", Qt::DashLine);
    createStyleAction("Dot", Qt::DotLine);
    createStyleAction("Dash Dot", Qt::DashDotLine);
    createStyleAction("Dash Dot Dot", Qt::DashDotDotLine);

    for (auto action : m_brushStyleGroup->actions()) {
        brushToolBar->addAction(action);
    }

    connect(m_brushStyleGroup, &QActionGroup::triggered, this, &MainWindow::onBrushStyleSelected);
}

void MainWindow::onColorClicked()
{
    QColor newColor = QColorDialog::getColor(m_toolController->pen().color(), this, "Select Color");
    if (newColor.isValid()) {
        QPen pen = m_toolController->pen();
        pen.setColor(newColor);
        m_toolController->setPen(pen);
    }
}

void MainWindow::onClearClicked()
{
    m_canvas->clear();
}

void MainWindow::onSaveClicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "",
                                                    "PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    if (!filePath.isEmpty()) {
        if (!m_canvas->save(filePath)) {
            QMessageBox::warning(this, "Error", "Failed to save image");
        }
    }
}

void MainWindow::onPenWidthChanged(int width)
{
    QPen pen = m_toolController->pen();
    pen.setWidth(width);
    m_toolController->setPen(pen);

    if (auto* eraser = qobject_cast<EraserTool*>(m_toolController->currentTool())) {
        QPen eraserPen = pen;
        eraserPen.setWidth(width * 2);
        eraser->setPen(eraserPen);
        m_toolController->setPen(pen);
    }
}

void MainWindow::onImageUpdated(const QImage &image)
{
    m_displayImage = image;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_displayImage);
    QMainWindow::paintEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_canvas->resize(event->size());
    QMainWindow::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_toolController->onMousePress(event->pos(), m_canvas.get());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_toolController->onMouseMove(event->pos(), m_canvas.get());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_toolController->onMouseRelease(event->pos(), m_canvas.get());
    }
}
void MainWindow::onBrushStyleSelected(QAction* action)
{
    Qt::PenStyle style = static_cast<Qt::PenStyle>(action->data().toInt());

    if (!qobject_cast<EraserTool*>(m_toolController->currentTool())) {
        QPen pen = m_toolController->pen();
        pen.setStyle(style);
        m_toolController->setPen(pen);
    }
}

MainWindow::~MainWindow() = default;
