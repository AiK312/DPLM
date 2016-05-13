#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), pixX(0), pixY(0), xCoo(0), yCoo(0)
{        
    ui->setupUi(this);    

    settings = new QSettings("MySoft", "Star Runner");

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
    newPixmapGraph();
    //pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);


    //"одним выстрелом" определили высоту и ширину виера
    QTimer::singleShot(100, this, SLOT(getViewWidhtAndHeight()));


    //    timer = new QTimer(this);
    //    connect(timer, &QTimer::timeout, this, &MainWindow::getViewWidhtAndHeight);
    //    timer->start(50);


}

bool MainWindow::drawnOnElement(int countWidht, int countHeight)
{

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

    //    X = settings->value("mainwindow/X").toInt();
    //    Y = settings->value("mainwindow/Y").toInt();
    //    zoomLevel = settings->value("mainwindow/zoomLevel").toInt();
    X = 37089;
    Y = 21624;
    zoomLevel = 16;
    showingTiles(Y, Y+row, X, X+col, 0);
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

    int deltaX = pixmapGraphCoordinates->x() - pixX;
    int deltaY = pixmapGraphCoordinates->y() - pixY;
    int countX = setCountTiles(deltaX);
    int countY = setCountTiles(deltaY);
    qDebug() << countX << ' ' << countY;

    xCoo = 256*countX*(-1);
    yCoo = 256*countY*(-1);
    showingTiles(Y-countY, Y-countY+row, X-countX, X-countX+col, xCoo);

}

void MainWindow::showingTiles(int startForY, int endForY, int startForX, int endForX, int startX)
{
    int temp = 0;
    int count = 0;
//    int countWidht;
//    int countHeight;
    QPoint p;

    for(int i=startForY, countHeight=0; countHeight < ui->view->height() +256;  countHeight += 256, ++i)
    {
        for(int j=startForX, countWidht = 0; countWidht < ui->view->width()+256; countWidht += 256, ++j)
        {
            p.setX(xCoo);
            p.setY(yCoo);

            if(j > (pow(2, zoomLevel)-1) )
            {
                temp = j;
                j = count;
                tiles *item = new tiles(zoomLevel, j, i);
                pixmapGraph->addToGroup(item);
                item->setFlags(QGraphicsItem::ItemIsMovable);
                item->setPos(xCoo, yCoo);
                count++;
                j = temp;
                temp = 0;
                xCoo += 256;

            }
            else
            {
                tiles *item = new tiles(zoomLevel, j, i);
                pixmapGraph->addToGroup(item);
                item->setFlags(QGraphicsItem::ItemIsMovable);
                item->setPos(xCoo, yCoo);
                xCoo += 256;
            }


        }
        yCoo += 256;
        xCoo = startX;
    }
    count = 0;


}

void MainWindow::zoomInMap(QPoint *point)
{
    updateBeforeZooming();
    newPixmapGraph();

    int x = point->x();
    int y = point->y();
    x = setCountTiles(x);
    y = setCountTiles(y);

    QPoint centerView(ui->view->width()/2, ui->view->height()/2);
    int xc = centerView.x();
    int yc = centerView.y();

    xc = setCountTiles(xc);
    yc = setCountTiles(yc);

    qDebug() << centerView;
    qDebug() << "Point x: " << x << "\tPoint y: " << y;
    qDebug() << "Center x: " << xc << "\t Cenetr y: " << yc;

    int deltax = x-xc;
    int deltay = y-yc;

    X = X+deltax;
    Y = Y+deltay;

    X *= 2;
    Y *= 2;

    X = X + col/2;
    Y = Y + row/2;


    zoomLevel++;
    xCoo = 0;
    yCoo = 0;
    qDebug() << zoomLevel;

    showingTiles(Y, Y+row, X, X+col, 0);
}

void MainWindow::zoomOutMap(QPoint *point)
{    

    updateBeforeZooming();
    newPixmapGraph();
    zoomLevel--;

    X = (X - 3) / 2;
    Y = (Y - 2) / 2;

    xCoo = 0;
    yCoo = 0;
    showingTiles(Y, Y+row, X, X+col, 0);

}

void MainWindow::newPixmapGraph()
{
    pixmapGraph = new parentPixmapGraph;
    scene->addItem(pixmapGraph);
    connect(pixmapGraph, &parentPixmapGraph::zoomIn, this, &MainWindow::zoomInMap);
    connect(pixmapGraph, &parentPixmapGraph::zoomOut, this, &MainWindow::zoomOutMap);
    connect(pixmapGraph, &parentPixmapGraph::movingTiles, this, &MainWindow::loadNewTiles);
}

void MainWindow::updateBeforeZooming()
{
    scene->destroyItemGroup(pixmapGraph);
    scene->clear();
    ui->view->viewport()->update();
}

MainWindow::~MainWindow()
{       
    delete ui;
}


