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
#include "tilescache.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    inline int setCountTiles(int&);
    void showingTiles(int startForY, int endForY, int startForX, int endForX, int startX);
    void showingTilesFromCache();
    void updateBeforeZooming();
    void writeSettings();
    void readSettings();
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
    int xCoo;
    int yCoo;
    int col;
    int row;
    int pixX;
    int pixY;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void exit();

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
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
