#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), pixX(0), pixY(0)
{        
    ui->setupUi(this);

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

    //    tiles *item = new tiles(pixmapGraph, zoomLevel, 2, 2);
    //    item->setFlags(QGraphicsItem::ItemIsMovable);
    //    item->setPos(256, 0);
    //    scene->addItem(pixmapGraph);

    //    int x = 0;
    //    int y = 0;
    //    for(int i=0; i<row; ++i)
    //    {
    //        std::deque<tiles*> temp;
    //        for(int j=0; j<col; ++j)
    //        {
    //            tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
    //            item->setFlags(QGraphicsItem::ItemIsMovable);
    //            item->setPos(x, y);
    //            temp.push_back(item);
    //            x += 256;
    //        }
    //        x = 0;
    //        y += 256;
    //        matrix.push_back(temp);
    //    }

    int x = 0;
    int y = 0;

    zoomLevel = 16;
    X = 37089;
    Y = 21624;

        for(int i=Y; i<Y+row; ++i)
        {
            showingTiles(i, X, X+col, x, y);
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
    emit exit();
}

void MainWindow::loadNewTiles()
{    
    pixmapGraphCoordinates = pixmapGraph->getStartCoordinates(pixmapGraphCoordinates);
    qDebug() << "Main class. X = " << pixmapGraphCoordinates->x() << " Y = " << pixmapGraphCoordinates->y();

    //RIGHT&DOWN
    if(pixmapGraphCoordinates->x() > pixX && pixmapGraphCoordinates->y() > pixY)
    {
        int deltaX = pixmapGraphCoordinates->x() - pixX;
        int deltaY = pixmapGraphCoordinates->y() - pixY;
        int countX = setCountTiles(deltaX);
        int countY = setCountTiles(deltaY);
        qDebug() << countX << ' ' << countY;


        int x = 256*countX*(-1);
        int y = 256*countY*(-1);
        int countRow = 0;
        int temp = 0;
        int count = 0;

        for(int i=(Y-countY); i < (Y-countY+row); ++i)
        {
            if(countRow >= countY)
            {

            }
            else
            {
//                for(int j=(X-countX); j<(X-countX+col); ++j)
//                {
//                    if(j > (pow(2, zoomLevel)-1) )
//                    {
//                        temp = j;
//                        j = count;
//                        tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
//                        item->setFlags(QGraphicsItem::ItemIsMovable);
//                        item->setPos(x, y);
//                        count++;
//                        j = temp;
//                        temp = 0;
//                        x += 256;

//                    }
//                    else
//                    {
//                        tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
//                        item->setFlags(QGraphicsItem::ItemIsMovable);
//                        item->setPos(x, y);
//                        x += 256;
//                    }

//                }
//                count = 0;
//                x = 0;
//                y += 256;
                showingTiles(i, X-countX, X-countX+col, x, y);
                countRow++;
            }

        }


    }



}

void MainWindow::showingTiles(int i, int startForX, int endForX, int &x, int &y)
{
    int temp = 0;
    int count = 0;
//    zoomLevel = 16;
//    X = 37089;
//    Y = 21624;

    for(int j=startForX; j<endForX; ++j)
    {
        if(j > (pow(2, zoomLevel)-1) )
        {
            temp = j;
            j = count;
            tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
            item->setFlags(QGraphicsItem::ItemIsMovable);
            item->setPos(x, y);
            count++;
            j = temp;
            temp = 0;
            x += 256;

        }
        else
        {
            tiles *item = new tiles(pixmapGraph, zoomLevel, j, i);
            item->setFlags(QGraphicsItem::ItemIsMovable);
            item->setPos(x, y);
            x += 256;
        }
    }
    count = 0;
    x = 0;
    y += 256;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mesh(const QList<QRectF> &region)
{
    qDebug() << region << "END";
}

