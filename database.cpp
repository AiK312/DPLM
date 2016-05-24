#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

void DataBase::connectToDataBase()
{    
    if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{    
    if(this->openDataBase()){        
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{    
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{   
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "                    
                    TABLE_TILE     " VARCHAR(255)    NOT NULL,"
                    TABLE_PIC      " BLOB            NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBase::insertIntoTable(const QVariantList &data)
{

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_TILE ", "
                  TABLE_PIC " ) "
                            "VALUES (:Tile, :Pic)");

    query.bindValue(":Tile",        data[0].toString());
    query.bindValue(":Pic",         data[1].toByteArray());


    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

QByteArray DataBase::selectFromTable(QString tile)
{
    QByteArray byte;
    QSqlQuery query;
    query.prepare("SELECT * FROM " TABLE " WHERE " TABLE_TILE " = :nTile");
    query.bindValue(":nTile", tile);

    if(!query.exec())
    {
        qDebug() << query.lastError().text();
        return byte;
    }
    else
    {
        while(query.next())
        {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            byte = query.value(2).toByteArray();
        }

    }
    return byte;


}

bool DataBase::insertIntoTable(QString tile, const QByteArray &pic)
{
    QVariantList data;
    data.append(tile);
    data.append(pic);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}
