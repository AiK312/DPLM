#include "tiles.h"

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
    qDebug() << "~tiles";
}

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
