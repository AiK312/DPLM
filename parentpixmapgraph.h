#ifndef PARENTPIXMAPGRAPH_H
#define PARENTPIXMAPGRAPH_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QUrl>

class parentPixmapGraph : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    parentPixmapGraph();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);    

    QPoint* getStartCoordinates(QPoint*);

private:
    int startX;
    int startY;
    int pressX;
    int pressY;
    int releaseX;
    int releaseY;

signals:
    void movingTiles();

};

#endif // PARENTPIXMAPGRAPH_H