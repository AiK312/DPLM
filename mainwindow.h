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
#include <QSettings>
#include <math.h>
#include <deque>
#include "tiles.h"
#include "parentpixmapgraph.h"
#include "applicationsettings.h"
#include "database.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool drawnOnElement(int, int);
    inline int setCountTiles(int&);
    void setZoomLevel(int&);
    void show();
    void showingTiles(int startForY, int endForY, int startForX, int endForX, int startX, QString tileServer);
    void showingTilesFromCache();
    void updateBeforeZooming();
    void writeSettings();
    void readSettings();
    void diskCache();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    parentPixmapGraph *pixmapGraph;
    QTimer *timer;
    QPoint *pixmapGraphCoordinates;
    QSettings *settings;
    ApplicationSettings *appset;
    DataBase *db;

    int viewWidht;
    int viewHeight;
    unsigned int zoomLevel;
    unsigned int X;
    unsigned int Y;
    QString tileServer;
    bool cache;
    QPoint topLeft;
//    QPoint topRight;
//    QPoint botLeft;
    QPoint botRight;
    int xCoo;
    int yCoo;
    int col;
    int row;
    int pixX;
    int pixY;


    std::deque<std::deque<tiles*> > matrix;
    QList<QRectF> region;

protected:
    void closeEvent(QCloseEvent *event);



public slots:
    void getViewWidhtAndHeight();
    void exitApp();
    void loadNewTiles();    
    void zoomInMap(QPoint *point);
    void zoomOutMap(QPoint *point);
    void newPixmapGraph();
    void changeSettings(QString tile, bool check);
    void cancelSettings();
    void cacheSlot(QByteArray &inByteArray, int &, int &);



private slots:
    void on_actionSettings_triggered();
};

#endif // MAINWINDOW_H
