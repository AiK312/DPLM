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
#include "tiles.h"



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
    ~MainWindow();       

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;    
    QGraphicsItemGroup *pixmapGraph;    
    QTimer *timer;
    int viewWidht;
    int viewHeight;
    int zoomLevel;

public slots:
    void mesh();
    void getViewWidhtAndHeight();


};

#endif // MAINWINDOW_H
