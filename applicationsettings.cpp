#include "applicationsettings.h"
#include "ui_applicationsettings.h"

ApplicationSettings::ApplicationSettings(QString serverTiles, bool checkCache, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicationSettings)
{
    ui->setupUi(this);

    if(serverTiles == "http://a.tile.opencyclemap.org/cycle/")
        ui->comboBox->setCurrentIndex(0);
    else if(serverTiles == "http://a.tile2.opencyclemap.org/transport/")
        ui->comboBox->setCurrentIndex(1);
    else if(serverTiles == "http://otile4.mqcdn.com/tiles/1.0.0/osm/")
        ui->comboBox->setCurrentIndex(2);

    if(checkCache)
        ui->cache->setChecked(true);
    else
        ui->cache->setChecked(false);
}

ApplicationSettings::~ApplicationSettings()
{
    delete ui;
}

void ApplicationSettings::setSettings(QString tileServer, bool check)
{
    tile = tileServer;
    checkbox = check;
}

void ApplicationSettings::on_ok_clicked()
{
    int n = ui->comboBox->currentIndex();
    switch (n) {
    case 0:
        tile = "http://a.tile.opencyclemap.org/cycle/";
        break;
    case 1:
        tile = "http://a.tile2.opencyclemap.org/transport/";
        break;
    case 2:
        tile = "http://otile4.mqcdn.com/tiles/1.0.0/osm/";
        break;
    default:
        break;
    }

    if(ui->cache->isChecked())
        checkbox = true;
    else
        checkbox = false;

    this->hide();
    emit changeSettings(tile, checkbox);
}

void ApplicationSettings::on_cansel_clicked()
{
    emit cancel();
    this->hide();
}
