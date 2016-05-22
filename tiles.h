#ifndef TILES_H
#define TILES_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
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
#include <QString>

class tiles : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit tiles(QGraphicsItemGroup *parent = 0);
    tiles(QGraphicsItemGroup *parent, int, int, int);
    tiles(const int &zoomPic, const int &xPic, const int &yPic, const QString &tileServer, const bool cache);
    ~tiles();
    //QPoint pos() const;
    //переопределнные ребята
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //началол загрузки
    void startDownloading();

signals:
    void signalCache(QByteArray &, int &, int &);

private:
    int zoom;
    int x;
    int y;
    bool cacheFromMain;
    QString tileSkin;
    QNetworkAccessManager *netManager;
    QEventLoop *loop;
    QGraphicsPixmapItem *image;
    QPixmap *pixmap;


public slots:
    void replyFinished(QNetworkReply* reply);    
};

#endif // TILES_H
