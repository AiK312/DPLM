#ifndef TILES_H
#define TILES_H

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

class tiles : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit tiles(QGraphicsItemGroup *parent = 0);
    ~tiles();


signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QNetworkAccessManager *netManager;
    QEventLoop *loop;
    QGraphicsPixmapItem *image;
    QPixmap *pixmap;


public slots:
    void replyFinished(QNetworkReply* reply);
};

#endif // TILES_H
