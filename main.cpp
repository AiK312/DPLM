#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();    
    w->showMaximized();

    QObject::connect(w, &MainWindow::exit,
                     &a, &QApplication::quit);

    return a.exec();
}
