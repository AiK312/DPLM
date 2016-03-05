#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Main Constructor Start";
    ui->setupUi(this);
    this->showMaximized();

    //Сценка. Нужна для картиночек и их перетаскивания.
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //Тащемта сам виевер отображает содержимое сцены.
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setCacheMode(QGraphicsView::CacheBackground);
    ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //Пиксмап - родитель для картиночек. Нужен для одновременного перетаскивания нескольких(!) пикч.
    pixmapGraph = new QGraphicsItemGroup;
    pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(pixmapGraph);

    //tiles *item = new tiles(pixmapGraph, 2, 2, 2);
    //item->setFlags(QGraphicsItem::ItemIsMovable);
    //item->setPos(256, 0);
    //scene->addItem(pixmapGraph);

    connect(scene, &QGraphicsScene::changed, this, &MainWindow::mesh);
    //"одним выстрелом" определили высоту и ширину виера
    QTimer::singleShot(50, this, SLOT(getViewWidhtAndHeight()));

    //timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::getViewWidhtAndHeight);
    //timer->start(50);


}

int MainWindow::setCountTiles(int *ptrInt)
{
    return ceil(static_cast<double>(*ptrInt)/256);
}

void MainWindow::setZoomLevel(int* val)
{
    if(*val == 2)
    {
        zoomLevel = 1;
        return;
    }
    if(*val > 2 && *val <= 4)
    {
        *val = 4;
        zoomLevel = 2;
        return;
    }
    if(*val > 4 && *val <= 8)
    {
        *val = 8;
        zoomLevel = 3;
        return;
    }
    if(*val > 8 && *val <= 16)
    {
        *val = 16;
        zoomLevel = 4;
        return;
    }
    if(*val > 16 && *val <= 32)
    {
        *val = 32;
        zoomLevel = 5;
        return;
    }

}


void MainWindow::getViewWidhtAndHeight()
{
    viewWidht = ui->view->width();
    viewHeight = ui->view->height();
    scene->setSceneRect(0,0,viewWidht,viewHeight);
    int *ptrViewWidght = &viewWidht;
    int z = setCountTiles(ptrViewWidght);
    int *ptrz = &z;
    setZoomLevel(ptrz);
    qDebug() << z;
    qDebug() << viewWidht << 'x' << viewHeight;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mesh()
{
    //qDebug() << item->scenePos();
}

