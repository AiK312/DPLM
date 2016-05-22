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
                    TABLE_Zoom     " INTEGER         NOT NULL,"
                    TABLE_xCoo     " INTEGER         NOT NULL,"
                    TABLE_yCoo     " INTEGER         NOT NULL,"
                    TABLE_X        " INTEGER         NOT NULL,"
                    TABLE_Y        " INTEGER         NOT NULL,"
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
    query.prepare("INSERT INTO " TABLE " ( " TABLE_Zoom ", "
                  TABLE_xCoo ", "
                  TABLE_yCoo ", "
                  TABLE_X ", "
                  TABLE_Y ", "
                  TABLE_PIC " ) "
                            "VALUES (:Zoom, :xCoo, :yCoo, :X, :Y, :Pic)");

    query.bindValue(":Zoom",        data[0].toInt());
    query.bindValue(":xCoo",        data[1].toInt());
    query.bindValue(":yCoo",        data[2].toInt());
    query.bindValue(":X",           data[3].toInt());
    query.bindValue(":Y",           data[4].toInt());
    query.bindValue(":Pic",         data[5].toByteArray());

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

bool DataBase::selectFromTable(const int &zoom)
{
//    QSqlQuery query;
//    query.exec("SELECT * FROM " TABLE " WHERE " TABLE_Zoom " = " + QString::number(zoom));

}



/* Второй метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const int &Zoom, const int &xCoo, const int &yCoo, const int &X, const int &Y, const QByteArray &pic)
{
    QVariantList data;
    data.append(Zoom);
    data.append(xCoo);
    data.append(yCoo);
    data.append(X);
    data.append(Y);
    data.append(pic);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}
