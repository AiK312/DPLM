#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QDialog>
#include <QString>

namespace Ui {
class ApplicationSettings;
}

class ApplicationSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationSettings(QString serverTiles, bool checkCache, QWidget *parent = 0);
    ~ApplicationSettings();
    void setSettings(QString tileServer, bool check);

private slots:
    void on_ok_clicked();

    void on_cansel_clicked();

private:
    Ui::ApplicationSettings *ui;
    QString tile;
    bool checkbox;

signals:
    void changeSettings(QString, bool);
    void cancel();

};

#endif // APPLICATIONSETTINGS_H
