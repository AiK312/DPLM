#include "tilescache.h"

TilesCache::TilesCache(QByteArray byte)
{
    pix = new QPixmap;
    pix->loadFromData(byte);
}

TilesCache::~TilesCache()
{

}

QRectF TilesCache::boundingRect() const
{
    return QRectF(0,0,256,256);
}

void TilesCache::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *pix);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
