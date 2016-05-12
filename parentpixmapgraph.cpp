#include "parentpixmapgraph.h"

parentPixmapGraph::parentPixmapGraph() : startX(0), startY(0)
{

}

QRectF parentPixmapGraph::boundingRect() const
{
    return QRectF(pos(), QSizeF(10000.0, 10000.0));
}

void parentPixmapGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->drawLine(QPointF(0,0), pos());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void parentPixmapGraph::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    int deltaX = this->startX - event->pos().x();
//    int deltaY = this->startY - event->pos().y();
//    qDebug() << event->pos().x() << ' ' << event->pos().y();
//    qDebug() << "!!!" << deltaX << ' ' << deltaY;
//    int mX = this->pos().x() - deltaX;
//    int mY = this->pos().y() - deltaY;
//    this->setPos(mX, mY);
//    this->startX = event->pos().x();
//    this->startY = event->pos().y();

}

void parentPixmapGraph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    pressX = event->pos().x();
    pressY = event->pos().y();
    //qDebug() << "pressX = " << pressX << ' ' << "pressY = " << pressY;
    Q_UNUSED(event);
}

void parentPixmapGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    releaseX = event->pos().x();
    releaseY = event->pos().y();
    //qDebug() << "releaseX = " << releaseX << ' ' << "releaseY" << releaseY;
    int deltaX = pressX - releaseX;
    int deltaY = pressY - releaseY;
    //qDebug() << "deltaX = " << deltaX << ' ' << "deltaY = " << deltaY;

    if (deltaX == 0 && deltaY == 0)
        return;

    this->setPos(startX-deltaX, startY-deltaY);
    startX -= deltaX;
    startY -= deltaY;
    //qDebug() << "startX = " << startX << ' ' << "startY = " << startY;
    Q_UNUSED(event);
    emit movingTiles();
}

void parentPixmapGraph::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
        emit zoomIn();
    else
        emit zoomOut();

}

QPoint *parentPixmapGraph::getStartCoordinates(QPoint *coordinates)
{
    coordinates->setX(startX);
    coordinates->setY(startY);
    return coordinates;
}

