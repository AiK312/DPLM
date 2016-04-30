#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QThread>
#include <QMessageBox>
#include <QGeoServiceProvider>
#include <QGeoCoordinate>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QCursor>
#include <QFileDialog>
#include <windows.h>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <math.h>
#include <deque>
#include "tiles.h"
#include "parentpixmapgraph.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    inline int setCountTiles(int&);
    void setZoomLevel(int&);
    void show();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    parentPixmapGraph *pixmapGraph;
    QTimer *timer;
    QPoint *pixmapGraphCoordinates;

    int viewWidht;
    int viewHeight;
    int zoomLevel;
    int col;
    int row;
    int X;
    int Y;
    int pixX;
    int pixY;
    std::deque<std::deque<tiles*> > matrix;
    QList<QRectF> region;




public slots:
    void mesh(const QList<QRectF> &);
    void getViewWidhtAndHeight();
    void exitApp();
    void loadNewTiles();
    void showingTiles(int i, int startForX, int endForX, int &x, int &y);

signals:
    void exit();


};

#endif // MAINWINDOW_H
