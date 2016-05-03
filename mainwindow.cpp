#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), pixX(0), pixY(0), xCoo(0), yCoo(0)
{        
    ui->setupUi(this);

    settings = new QSettings("MySoft", "Star Runner");

    //    Coordinates UpLeft;
    //    Coordinates UpRight;
    //    Coordinates BotLeft;
    //    Coordinates BotRight;

    pixmapGraphCoordinates = new QPoint;
    pixmapGraphCoordinates->setX(pixX);
    pixmapGraphCoordinates->setY(pixY);

    //Сценка. Нужна для картиночек и их перетаскивания.
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    //Тащемта сам виевер отображает содержимое сцены.
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setCacheMode(QGraphicsView::CacheBackground);
    ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //Пиксмап - родитель для картиночек. Нужен для одновременного перетаскивания нескольких тайлов.
    pixmapGraph = new parentPixmapGraph();
    //pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(pixmapGraph);

    //connect(scene, &QGraphicsScene::changed, this, &MainWindow::mesh);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);

    connect(pixmapGraph, &parentPixmapGraph::movingTiles, this, &MainWindow::loadNewTiles);

    //"одним выстрелом" определили высоту и ширину виера
    QTimer::singleShot(100, this, SLOT(getViewWidhtAndHeight()));


    //    timer = new QTimer(this);
    //    connect(timer, &QTimer::timeout, this, &MainWindow::getViewWidhtAndHeight);
    //    timer->start(50);


}

int MainWindow::setCountTiles(int &ptrInt)
{
    return ceil(static_cast<double>(ptrInt)/256);
}

void MainWindow::setZoomLevel(int &val)
{
    if(val == 2)
    {
        zoomLevel = 1;
        return;
    }
    if(val > 2 && val <= 4)
    {
        zoomLevel = 2;
        return;
    }
    if(val > 4 && val <= 8)
    {
        zoomLevel = 3;
        return;
    }
    if(val > 8 && val <= 16)
    {
        zoomLevel = 4;
        return;
    }
    if(val > 16 && val <= 32)
    {
        zoomLevel = 5;
        return;
    }

}

void MainWindow::show()
{    

    X = settings->value("mainwindow/X").toInt();
    Y = settings->value("mainwindow/Y").toInt();
    zoomLevel = settings->value("mainwindow/zoomLevel").toInt();


    for(int i=Y; i<Y+row; ++i)
    {
        showingTiles(i, X, X+col, 0);
    }



}


void MainWindow::getViewWidhtAndHeight()
{
    viewWidht = ui->view->width();
    viewHeight = ui->view->height();
    scene->setSceneRect(0, 0, viewWidht, viewHeight);
    col = setCountTiles(viewWidht);
    row = setCountTiles(viewHeight);
    setZoomLevel(col);
    qDebug() << "ZoomLevel:\t" << zoomLevel;
    qDebug() << "Widght:\t" << col;
    qDebug() << "Height:\t" << row;
    qDebug() << "Resolution:\t" << viewWidht << 'x' << viewHeight;
    show();
}

void MainWindow::exitApp()
{
    settings->setValue("mainwindow/X", X);
    settings->setValue("mainwindow/Y", Y);
    settings->setValue("mainwindow/zoomLevel", zoomLevel);
    settings->sync();
    emit exit();
}

void MainWindow::loadNewTiles()
{    
    pixmapGraphCoordinates = pixmapGraph->getStartCoordinates(pixmapGraphCoordinates);
    qDebug() << "Main class. X = " << pixmapGraphCoordinates->x() << " Y = " << pixmapGraphCoordinates->y();

    //    if((pixmapGraphCoordinates->x() > pixX) && (pixmapGraphCoordinates->y() > pixY))
    //    {
    int deltaX = pixmapGraphCoordinates->x() - pixX;
    int deltaY = pixmapGraphCoordinates->y() - pixY;
    int countX = setCountTiles(deltaX);
    int countY = setCountTiles(deltaY);
    qDebug() << countX << ' ' << countY;

    xCoo = 256*countX*(-1);
    yCoo = 256*countY*(-1);
    int tempy;

    for(int i=(Y-countY), tempy=0; tempy < viewHeight+256;  tempy += 256, ++i)
    {
        showingTiles(i, X-countX, X-countX+col, xCoo);
    }
    //  }



}

void MainWindow::showingTiles(int i, int startForX, int endForX, int startX)
{
    int temp = 0;
    int count = 0;

    int tempx;
    for(int j=startForX, tempx = 0; tempx < viewWidht+256; tempx += 256, ++j)
    {

        if(j > (pow(2, zoomLevel)-1) )
        {
            temp = j;
            j = count;
            tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
            item->setFlags(QGraphicsItem::ItemIsMovable);
            item->setPos(xCoo, yCoo);
            count++;
            j = temp;
            temp = 0;
            xCoo += 256;

        }
        else
        {
            tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
            item->setFlags(QGraphicsItem::ItemIsMovable);
            item->setPos(xCoo, yCoo);
            xCoo += 256;
        }



    }
    count = 0;
    xCoo = startX;
    yCoo += 256;

}

MainWindow::~MainWindow()
{       
    delete ui;
}


void MainWindow::mesh(const QList<QRectF> &region)
{
    qDebug() << region << "END";
}

