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
#include "tiles.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();       

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;    
    QGraphicsItemGroup *pixmapGraph;





public slots:


};

#endif // MAINWINDOW_H
