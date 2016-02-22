#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Main Constructor Start";
    ui->setupUi(this);
    pixmapGraph = new QGraphicsItemGroup;
    pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->view->resize(600, 600);
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setCacheMode(QGraphicsView::CacheBackground);
    ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,0,500,500);

    tiles *item = new tiles(pixmapGraph);
    item->setFlags(QGraphicsItem::ItemIsMovable);
    item->setPos(256, 0);

    scene->addItem(pixmapGraph);


}

MainWindow::~MainWindow()
{
    delete ui;
}

