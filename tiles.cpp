#include "tiles.h"

tiles::tiles(QGraphicsItemGroup *parent) : QGraphicsItemGroup(parent)
{

}

tiles::tiles(QGraphicsItemGroup *parent, int zoomPic, int xPic, int yPic) : QGraphicsItemGroup(parent), zoom(zoomPic), x(xPic), y(yPic)
{
    //    netManager = new QNetworkAccessManager;
    //    image = new QGraphicsPixmapItem;
    //    pixmap = new QPixmap;
    //    loop = new QEventLoop;
    //    connect(netManager, &QNetworkAccessManager::finished,
    //            this, &tiles::replyFinished);
    //    connect(netManager, &QNetworkAccessManager::finished,
    //            loop, &QEventLoop::quit);

    //    QUrl url("http://otile4-s.mqcdn.com/tiles/1.0.0/osm/" + QString::number(zoom) + '/' + QString::number(x) + '/' + QString::number(y) + ".png");
    //    QNetworkRequest request(url);
    //    netManager->get(request);
    //    loop->exec();
}

tiles::tiles(const int &zoomPic, const int &xPic, const int &yPic, const QString &tileServer, const bool cache) : zoom(zoomPic),
    x(xPic), y(yPic), cacheFromMain(cache), tileSkin(tileServer)
{
    netManager = new QNetworkAccessManager;
    image = new QGraphicsPixmapItem;
    pixmap = new QPixmap;
    loop = new QEventLoop;
    connect(netManager, &QNetworkAccessManager::finished,
            this, &tiles::replyFinished);
    connect(netManager, &QNetworkAccessManager::finished,
            loop, &QEventLoop::quit);


}

tiles::~tiles()
{

}

//QPoint tiles::pos() const
//{
//    QPoint p(x, y);
//    return p;
//}

QRectF tiles::boundingRect() const
{
    return QRectF(0,0,256,256);
}

void tiles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   
    painter->drawPixmap(0, 0, *pixmap);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void tiles::replyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        //QByteArray *bytes = new QByteArray(reply->readAll());
        //QPixmap *pixmap = new QPixmap;
        //pixmap->loadFromData(*bytes);
        //image->setPixmap(*pixmap);
        //delete pixmap;
        //delete bytes;
        QByteArray *bytes = new QByteArray(reply->readAll());
        if(cacheFromMain)
        {
            pixmap->loadFromData(*bytes);
            emit signalCache(*bytes, x, y);
        }
        else
        {
            pixmap->loadFromData(*bytes);
        }

    }
}

void tiles::startDownloading()
{
    QUrl url(tileSkin + QString::number(zoom) + '/' + QString::number(x) + '/' + QString::number(y) + ".png");
    QNetworkRequest request(url);
    netManager->get(request);
    loop->exec();
}

