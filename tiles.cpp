#include "tiles.h"

tiles::tiles(QGraphicsItemGroup *parent) : QGraphicsItemGroup(parent)
{

}

tiles::tiles(QGraphicsItemGroup *parent, int zoomPic, int xPic, int yPic) : QGraphicsItemGroup(parent), zoom(zoomPic), x(xPic), y(yPic)
{
    netManager = new QNetworkAccessManager;
    image = new QGraphicsPixmapItem;
    pixmap = new QPixmap;
    loop = new QEventLoop;
    connect(netManager, &QNetworkAccessManager::finished,
            this, &tiles::replyFinished);
    connect(netManager, &QNetworkAccessManager::finished,
            loop, &QEventLoop::quit);

    QUrl url("http://otile4-s.mqcdn.com/tiles/1.0.0/osm/" + QString::number(zoom) + '/' + QString::number(x) + '/' + QString::number(y) + ".png");
    QNetworkRequest request(url);
    netManager->get(request);
    loop->exec();
}

tiles::~tiles()
{

}

QRectF tiles::boundingRect() const
{
    return QRectF(0,0,256,256);
}

void tiles::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //qDebug() << "paint start";

    painter->drawPixmap(0, 0, *pixmap);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/*void tiles::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToParent(event->pos()));
}

void tiles::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void tiles::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}*/

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
        pixmap->loadFromData(*bytes);
    }
}

