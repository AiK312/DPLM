#ifndef TILESCACHE_H
#define TILESCACHE_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QPainter>

class TilesCache : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit TilesCache(QByteArray byte);
    ~TilesCache();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

private:
    QPixmap *pix;

public slots:
};

#endif // TILESCACHE_H
