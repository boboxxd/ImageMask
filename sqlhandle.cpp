#include "sqlhandle.h"
#include <QDebug>
SqlHandle::SqlHandle()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
}

bool SqlHandle::connect(const QString& databasename,const QString& host,int port,const QString& username,const QString& passward)
{
    database.setDatabaseName(databasename);
    database.setHostName(host);
    database.setPort(port),
    database.setUserName(username);
    database.setPassword(passward);

    if(database.open())
    {
        qDebug()<<QString("connect database:%1 successed!").arg(databasename);
        return true;
    }else
    {
        qDebug()<<QString("connect database failed!");
        return false;
    }
}

//create
bool SqlHandle::CreateTable(const QString &cmd)
 {
     QString create_sql = cmd;//"create table student (id int primary key, name varchar(30), age int)";
     sql_query.prepare(create_sql);
     if(!sql_query.exec())
     {
        return false;
     }
     else
     {
         qDebug()<<"Table created!";
        return true;
     }
 }

//insert
bool SqlHandle::Insert(const QString &cmd)
{
    QString insert_sql = "insert into student values (?, ?, ?)";
    sql_query.prepare(insert_sql);

}

//change
bool SqlHandle::Modify(const QString &cmd)
{
    QString update_sql = cmd;//"update student set name = :name where id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name", "Qt");
    sql_query.bindValue(":id", 1);
    if(!sql_query.exec())
    {

    }
    else
    {
        qDebug()<<"updated!";
    }
}

//delete
bool SqlHandle::Drop(const QString &cmd)
{

}

//query
bool SqlHandle::Querry(const QString &cmd)
{
    QString select_sql = "select id, name from student";
    sql_query.prepare(select_sql);
    if(!sql_query.exec())
    {
       return false;
    }
    else
    {
        qDebug()<<"Table Querried!";
       return true;
    }
}



