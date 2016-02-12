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
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QFileDialog>
#include <windows.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    void processRequest();
    void loadFourPictures();
    void showCoo();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QNetworkAccessManager *netManager;
    QGraphicsItemGroup *pixmapGraph;
    QGraphicsPixmapItem *gr1;
    QGraphicsPixmapItem *gr2;
    QGraphicsPixmapItem *gr3;
    QGraphicsPixmapItem *gr4;
    QEventLoop *eventloop;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int numberThread;
    int numberPic;
    int zoomLevel;
    int x;
    int y;


public slots:
    void replyFinished(QNetworkReply* reply);

};

#endif // MAINWINDOW_H
