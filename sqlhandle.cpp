#include "sqlhandle.h"
#include <QDebug>

SqlHandle::SqlHandle()
{

}

bool SqlHandle::createConnection()  //创建一个连接
{
        db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
        if(!db.database("sqlite1").isOpen())
        db.setDatabaseName(".//area.db");
        if( !db.open())
        {
            qDebug() << "无法建立数据库连接";
            return false;
        }
        return true;
}

bool SqlHandle::createTable()       //创建数据库表
{
        db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        bool success = query.exec("create table automobil(id int primary key,attribute varchar,"
                                  "type varchar,kind varchar,nation int,carnumber int,elevaltor int,"
                                  "distance int,oil int,temperature int)");
        if(success)
        {
            qDebug() << QObject::tr("数据库表创建成功！\n");
            return true;
        }
        else
        {
            qDebug() << QObject::tr("数据库表创建失败！\n");
            return false;
        }
}


//向数据库中插入记录
bool SqlHandle::insert()
{
    db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into automobil values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    long records = 10;
    for(int i=0; i<records; i++)
    {
        query.bindValue(0, i);
        query.bindValue(1, "四轮");
        query.bindValue(2, "轿车");
        query.bindValue(3, "富康");
        query.bindValue(4, rand()%100);
        query.bindValue(5, rand()%10000);
        query.bindValue(6, rand()%300);
        query.bindValue(7, rand()%200000);
        query.bindValue(8, rand()%52);
        query.bindValue(9, rand()%100);

        bool success=query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
            return false;
        }
    }
    return true;
}
