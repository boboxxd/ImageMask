#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class SqlHandle:public QObject
{
    Q_OBJECT

public:
    SqlHandle();
    ~SqlHandle()=default;
    bool createConnection();  //创建一个连接
    bool createTable();       //创建数据库表
    bool insert();
public slots:

signals:

private:

   QString connecttionname;
   QSqlDatabase db;
   QSqlQuery sql_query;
};

#endif // SQLHANDLE_H
