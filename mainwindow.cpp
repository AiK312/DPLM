#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pixmapGraph = new QGraphicsPixmapItem();
    netManager = new QNetworkAccessManager(this);
    scene = new QGraphicsScene(this);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    ui->view->setScene(scene);
    ui->view->setRenderHint(QPainter::Antialiasing);
    ui->view->setCacheMode(QGraphicsView::CacheBackground);
    ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0, 0, 512, 512);

    connect(netManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    this->setWindowTitle("Main Window: " + QString::number(this->width()) + 'x' + QString::number(this->height()) + " | "
                         + "Scene size: " + QString::number(scene->width()) + 'x' + QString::number(scene->height()) + " | "
                         + "View size: " + QString::number(ui->view->width()) + 'x' + QString::number(ui->view->height()));

    processRequest(18, 148369, 86502);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processRequest(int zoom, int x, int y)
{
    //OpenCycleMap
    /*QUrl url("http://a.tile.opencyclemap.org/cycle/" + QString::number(zoom)
             + '/' + QString::number(x)
             + '/' + QString::number(y) + ".png");*/

    //MapQuest
    QUrl url("http://otile4-s.mqcdn.com/tiles/1.0.0/osm/" + QString::number(zoom) + '/'
             + QString::number(x) + '/'
             + QString::number(y) + ".png");

    QNetworkRequest request(url);
    netManager->get(request);
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
        QByteArray bytes = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        pixmapGraph->setPixmap(pixmap);
        pixmapGraph->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(pixmapGraph);
        pixmapGraph->setPos(0, 0);
    }
    else
    {
        QMessageBox::information(0, "Error", reply->errorString());
    }
}
