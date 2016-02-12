#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), zoomLevel(2), x(0), y(0)
{
    ui->setupUi(this);

    pixmapGraph = new QGraphicsItemGroup();
    gr1 = new QGraphicsPixmapItem(pixmapGraph);
    gr2 = new QGraphicsPixmapItem(pixmapGraph);
    gr3 = new QGraphicsPixmapItem(pixmapGraph);
    gr4 = new QGraphicsPixmapItem(pixmapGraph);

    gr1->setPos(0, 0);
    gr2->setPos(256, 0);
    gr3->setPos(0, 256);
    gr4->setPos(256, 256);
    pixmapGraph->setPos(0, 0);

    gr1->setFlags(QGraphicsItem::ItemIsMovable);
    gr2->setFlags(QGraphicsItem::ItemIsMovable);
    gr3->setFlags(QGraphicsItem::ItemIsMovable);
    gr4->setFlags(QGraphicsItem::ItemIsMovable);
    pixmapGraph->setFlags(QGraphicsItem::ItemIsMovable);

    netManager = new QNetworkAccessManager();
    eventloop = new QEventLoop();

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setCacheMode(QGraphicsView::CacheBackground);
    ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0, 0, 512, 512);

    connect(netManager, SIGNAL(finished(QNetworkReply*)), eventloop, SLOT(quit()));
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    this->setWindowTitle("Main Window: " + QString::number(this->width()) + 'x' + QString::number(this->height()) + " | "
                         + "Scene size: " + QString::number(scene->width()) + 'x' + QString::number(scene->height()) + " | "
                         + "View size: " + QString::number(ui->view->width()) + 'x' + QString::number(ui->view->height()));

    loadFourPictures();
    scene->addItem(pixmapGraph);    

}

MainWindow::~MainWindow()
{
    delete netManager;
    delete eventloop;
    delete ui;
}

void MainWindow::processRequest()
{
    //OpenCycleMap
    /*QUrl url("http://a.tile.opencyclemap.org/cycle/" + QString::number(zoom) + '/' + QString::number(x) + '/' + QString::number(y) + ".png");*/

    //MapQuest
    QUrl url("http://otile4-s.mqcdn.com/tiles/1.0.0/osm/" + QString::number(zoomLevel) + '/' + QString::number(x) + '/' + QString::number(y) + ".png");
    QNetworkRequest request(url);
    netManager->get(request);
    eventloop->exec();
}

void MainWindow::loadFourPictures()
{
    for(int i=0; i<4; i++)
    {
        switch (i) {
        case 0:
            numberPic = 1;
            processRequest();
            break;
        case 1:
            numberPic = 2;
            x = x + 1;
            processRequest();
            x = x - 1;
            break;
        case 2:
            numberPic = 3;
            y = y + 1;
            processRequest();
            y = y - 1;
            break;
        case 3:
            numberPic = 4;
            x = x + 1;
            y = y + 1;
            processRequest();
            x = x - 1;
            y = y - 1;
            break;
        default:
            break;
        }
    }
}

void MainWindow::showCoo()
{
    QMessageBox::information(this, "Move", QString::number(gr4->x()) + 'x' + QString::number(gr4->y()));
}

void MainWindow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    pixmapGraph->setPos(event->pos());   
    //this->setPos(mapToScene(event->pos()));    
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //this->setCursor(QCursor(Qt::ClosedHandCursor));
    pixmapGraph->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
    showCoo();

}

void MainWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pixmapGraph->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);    

}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray *bytes = new QByteArray(reply->readAll());
        QPixmap *pixmap = new QPixmap;
        pixmap->loadFromData(*bytes);
        switch (numberPic) {
        case 1:
            gr1->setPixmap(*pixmap);
            //scene->addItem(gr1);
            delete pixmap;
            delete bytes;
            break;
        case 2:
            gr2->setPixmap(*pixmap);
            //scene->addItem(gr2);
            delete pixmap;
            delete bytes;
            break;
        case 3:
            gr3->setPixmap(*pixmap);
            //scene->addItem(gr3);
            delete pixmap;
            delete bytes;
            break;
        case 4:
            gr4->setPixmap(*pixmap);
            //scene->addItem(gr4);
            delete pixmap;
            delete bytes;
            break;
        default:
            break;
        }

        //pixmapGraph->setPixmap(*pixmap);
        //        pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);
        //        scene->addItem(pixmapGraph);
        //        pixmapGraph->setPos(0, 0);
    }
    else
    {
        QMessageBox::information(0, "Error", reply->errorString());
    }
}
