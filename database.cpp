#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/example/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/example/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
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

/* Метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_TILE ", "
                  TABLE_PIC " ) "
                            "VALUES (:Tile, :Pic)");

    query.bindValue(":Tile",        data[0].toString());
    query.bindValue(":Pic",         data[1].toByteArray());

    // После чего выполняется запросом методом exec()
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



/* Второй метод для вставки записи в базу данных
 * */
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
