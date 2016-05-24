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

void parentPixmapGraph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    pressX = event->pos().x();
    pressY = event->pos().y();    
    Q_UNUSED(event);
}

void parentPixmapGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    releaseX = event->pos().x();
    releaseY = event->pos().y();   
    int deltaX = pressX - releaseX;
    int deltaY = pressY - releaseY;    

    if (deltaX == 0 && deltaY == 0)
        return;

    this->setPos(startX-deltaX, startY-deltaY);
    startX -= deltaX;
    startY -= deltaY;    
    Q_UNUSED(event);
    emit movingTiles();
}

void parentPixmapGraph::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QPoint *p = new QPoint(event->pos().toPoint());

    if(event->delta() > 0)
        emit zoomIn(p);
    else
        emit zoomOut(p);

}

QPoint *parentPixmapGraph::getStartCoordinates(QPoint *coordinates)
{
    coordinates->setX(startX);
    coordinates->setY(startY);
    return coordinates;
}
